/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 01:58:05 by pepe              #+#    #+#             */
/*   Updated: 2023/05/02 01:18:37 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_re(t_redirect *re)
{
	if (re == NULL)
		return ;
	free_re(re->next);
	free(re->file);
	free(re);
}

void	free_lst(t_info_cmd *list)
{
	if (list == NULL)
		return ;
	free_re(list->re);
	list->re = NULL;
	free_lst(list->next);
	free(list->cmd);
	ft_free_matrix(list->cmd_args);
	free(list);
}
