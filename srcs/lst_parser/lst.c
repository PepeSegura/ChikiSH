/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 01:57:55 by pepe              #+#    #+#             */
/*   Updated: 2023/05/05 22:22:39 by pepe             ###   ########.fr       */
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

void	populate_cmd_lst(t_info_cmd **info, char *input)
{
	t_info_cmd	*new_node;
	char		*out;
	int			id_re;
	int			i;

	g_c.tokens = malloc(sizeof(char *) * (count_tokens(input) + 1));
	if (!g_c.tokens)
		return ;
	store_tokens(input, g_c.tokens);
	i = 0;
	new_node = lst_new_cmd(NULL, NULL);
	while (g_c.tokens[i])
	{
		id_re = token_is_symbol(g_c.tokens[i]);
		if (id_re >= 0 && g_c.tokens[i + 1])
		{
			out = ft_strdup(g_c.tokens[i + 1]);
			lst_create_redirect(&(new_node->re), lst_new_redirect(id_re, out));
			g_c.tokens = ft_delete_row_matrix(g_c.tokens, i + 1);
			g_c.tokens = ft_delete_row_matrix(g_c.tokens, i);
		}
		else if (g_c.tokens[i])
			i++;
	}
	if (g_c.tokens[0])
		new_node->cmd = ft_strdup(g_c.tokens[0]);
	new_node->cmd_args = ft_cpy_matrix(g_c.tokens);
	// ft_free_matrix(matrix);
	lst_addback_cmd(info, new_node);
}

t_info_cmd	*process_input(char **input)
{
	t_info_cmd	*info;
	int			i;
	char		**aux;

	info = NULL;
	i = 0;
	aux = ft_get_env(input);
	while (aux[i] != NULL)
	{
		// aux[i] = expan_token(aux[i], g_c.env);
		populate_cmd_lst(&info, aux[i]);
		i++;
	}
	return (info);
}

// int	main(int argc, char **argv, char **env)
// {
// 	(void)argc, (void)argv;
//     t_info_cmd	*info;
// 	char		*input[] = {"echo pepe", "ls -la", "cat -e > pepe", NULL};
// 	int			i = -1;

// 	info = NULL;
// 	while (input[++i])
// 		populate_cmd_lst(&info, input[i], env);
// 	print_lst(info);
// 	free_lst(info);
// 	return (0);
// }
