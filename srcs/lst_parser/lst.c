/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 01:57:55 by pepe              #+#    #+#             */
/*   Updated: 2023/05/03 01:12:21 by pepe             ###   ########.fr       */
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
	char		**matrix;
	int			id_re;
	int			i;

	matrix = ft_split(input, ' ');
	if (!matrix)
		return ;
	i = 0;
	new_node = lst_new_cmd(NULL, NULL);
	while (matrix[i])
	{
		id_re = token_is_symbol(matrix[i]);
		if (id_re >= 0 && matrix[i + 1])
		{
			out = ft_strdup(matrix[i + 1]);
			lst_create_redirect(&(new_node->re), lst_new_redirect(id_re, out));
			matrix = ft_delete_row_matrix(matrix, i + 1);
			matrix = ft_delete_row_matrix(matrix, i);
		}
		else if (matrix[i])
			i++;
	}
	if (matrix[0])
		new_node->cmd = ft_strdup(matrix[0]);
	new_node->cmd_args = ft_cpy_matrix(matrix);
	// ft_free_matrix(matrix);
	lst_addback_cmd(info, new_node);
}

t_info_cmd	*process_input(char **input)
{
	t_info_cmd	*info;
	int			i;

	info = NULL;
	i = 0;
	while (input[i] != NULL)
	{
		populate_cmd_lst(&info, input[i]);
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
