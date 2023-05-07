/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_pipas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:08:20 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/07 03:48:59 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	double_symbols(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (token_is_symbol(tokens[i]) >= 0 && tokens[i + 1]
			&& token_is_symbol(tokens[i + 1]) >= 0)
			return (1);
		i++;
	}
	if (tokens[i - 1] && token_is_symbol(tokens[i - 1]) >= 0)
		return (1);
	return (0);
}
