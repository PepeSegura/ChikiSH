/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 01:58:00 by pepe              #+#    #+#             */
/*   Updated: 2023/05/01 03:11:18 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_create_cmd(t_info_cmd **cmd, t_info_cmd *new)
{
	t_info_cmd	*aux;

	if (cmd == NULL)
		return ;
	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	aux = *cmd;
	while (aux->next)
	{
		aux = aux->next;
	}
	aux->next = new;
}

t_info_cmd	*lst_new_cmd(char *cmd, t_redirect *redir)
{
	t_info_cmd	*new;

	new = malloc(sizeof(t_info_cmd));
	if (!new)
		return (NULL);
	new->re = redir;
	new->cmd = cmd;
	new->next = NULL;
	return (new);
}
