/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 01:58:13 by pepe              #+#    #+#             */
/*   Updated: 2023/05/20 12:51:02 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_create_redirect(t_redirect **args, t_redirect *new)
{
	t_redirect	*aux;

	if (args == NULL)
	{
		free(new);
		return ;
	}
	if (*args == NULL)
	{
		*args = new;
		return ;
	}
	aux = *args;
	while (aux && aux->next)
	{
		aux = aux->next;
	}
	aux->next = new;
}

t_redirect	*lst_new_redirect(int type, char *file)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->type = type;
	new->file = file;
	new->next = NULL;
	return (new);
}
