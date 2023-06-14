/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_pipas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:08:20 by psegura-          #+#    #+#             */
/*   Updated: 2023/06/14 20:06:49 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SYNTAX_ERROR "syntax error near unexpected token '%s'\n"

int	token_is_symbol(char *token)
{
	int			i;
	const char	*symbols[] = {"<<", "<", ">", ">>", "|", NULL};

	i = -1;
	if (!token)
		return (-1);
	while (symbols[++i])
		if (ft_strcmp(token, symbols[i]) == 0)
			return (i);
	return (-1);
}

int	ft_aux(int type, int *pipe_found, int *redirection_found, char *token)
{
	if (type >= 0)
	{
		if (type == 4)
		{
			if (*pipe_found || *redirection_found)
				return (printf(SYNTAX_ERROR, token), 1);
			*pipe_found = 1;
			*redirection_found = 0;
		}
		else if (type >= 0 && type < 4)
		{
			if (*redirection_found)
				return (printf(SYNTAX_ERROR, token), 1);
			if (*pipe_found)
				return (0);
			*pipe_found = 0;
			*redirection_found = 1;
		}
	}
	else
	{
		*pipe_found = 0;
		*redirection_found = 0;
	}
	return (0);
}

int	double_symbols(char **tokens)
{
	int	i;
	int	type;
	int	pipe_found;
	int	redirection_found;

	if (token_is_symbol(tokens[0]) == 4)
		return (printf(SYNTAX_ERROR, tokens[0]), 1);
	i = 0;
	type = -1;
	pipe_found = 0;
	redirection_found = 0;
	while (tokens[i])
	{
		type = token_is_symbol(tokens[i]);
		if (ft_aux(type, &pipe_found, &redirection_found, tokens[i]) == 1)
			return (1);
		i++;
	}
	i--;
	if (token_is_symbol(tokens[i]) >= 0)
		return (printf(SYNTAX_ERROR, tokens[i]), 1);
	return (0);
}
