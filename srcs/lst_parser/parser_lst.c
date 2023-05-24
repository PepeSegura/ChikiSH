/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 01:57:55 by pepe              #+#    #+#             */
/*   Updated: 2023/05/24 13:43:11 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_addback_cmd(t_info_cmd **lst, t_info_cmd *new_node)
{
	t_info_cmd	*tmp;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

static int	handle_token(t_info_cmd *new_node, char ***input, int *i)
{
	t_redirect	*aux;
	int			id_re;
	char		*out;

	id_re = token_is_symbol((*input)[*i]);
	if (id_re == 4)
		return (id_re);
	if (id_re >= 0 && (*input)[*i + 1])
	{
		out = ft_strdup((*input)[*i + 1]);
		aux = lst_new_redirect(id_re, out);
		lst_create_redirect(&(new_node->re), aux);
		*input = ft_delete_row_matrix((*input), *i + 1);
		*input = ft_delete_row_matrix((*input), *i);
	}
	else if ((*input)[*i])
		(*i)++;
	return (id_re);
}

static int	populate_cmd_lst(t_info_cmd **info, char ***input, int *i)
{
	t_info_cmd	*new_node;
	int			id_re;
	int			start;

	start = *i;
	new_node = lst_new_cmd(NULL, NULL);
	while ((*input)[*i])
	{
		id_re = handle_token(new_node, input, i);
		if (id_re == 4)
			break ;
	}
	if ((*input)[start])
		new_node->cmd = ft_strdup((*input)[start]);
	new_node->cmd_args = ft_slice_matrix(*input, start, *i - 1);
	lst_addback_cmd(info, new_node);
	if (id_re == 4)
		(*i)++;
	if ((*input)[*i] == NULL)
		return (0);
	return (1);
}

void	process_here_doc(t_info_cmd **info)
{
	t_info_cmd	*cmd;
	t_redirect	*re;
	char		*filename;
	int			fd;

	cmd = *info;
	while (cmd)
	{
		re = cmd->re;
		while (re)
		{
			if (re->type == H_DOC_F)
			{
				signal_heredoc();
				filename = create_filename();
				fd = open_files(TRUNC_F, filename);
				here_doc(re->file, fd);
				close(fd);
				free(re->file);
				re->file = filename;
			}
			re = re->next;
		}
		cmd = cmd->next;
	}
}

t_info_cmd	*process_input(char **input)
{
	t_info_cmd	*info;
	int			i;
	char		**aux;

	info = NULL;
	i = 0;
	aux = ft_cpy_matrix(input);
	while (populate_cmd_lst(&info, &aux, &i))
		;
	ft_free_matrix(aux);
	g_c.tok_count = ft_lstsize_info(info);
	process_here_doc(&info);
	return (info);
}
