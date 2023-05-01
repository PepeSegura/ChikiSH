/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 01:58:10 by pepe              #+#    #+#             */
/*   Updated: 2023/05/01 03:11:44 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_info_cmd *list)
{
	t_redirect	*re;
	int			i;

	i = -1;
	while (list != NULL)
	{
		printf("Cmd_%d: \n\t[%s]", ++i, list->cmd);
		printf("\nArgs: \n");
		ft_print_matrix(list->cmd_args, "\t");
		re = list->re;
		if (re != NULL)
			printf("\nRedirects: \n");
		while (re != NULL)
		{
			printf("\tType: [%d], File: [%s]\n", re->type, re->file);
			re = re->next;
		}
		printf("\n");
		list = list->next;
	}
}
