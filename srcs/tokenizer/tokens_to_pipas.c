/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_pipas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgarci <davgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:08:20 by psegura-          #+#    #+#             */
/*   Updated: 2023/03/24 02:09:42 by davgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * It returns 1 if the token is a symbol, 0 otherwise
 * 
 * @param token The token to check.
 */
int	token_is_symbol(char *token)
{
	int			i;
	static char	*symbols[] = {"<<", "<", ">", ">>", "|", NULL};

	i = -1;
	if (!token)
		return (0);
	while (symbols[++i])
		if (ft_strcmp(token, symbols[i]) == 0)
			return (1);
	return (0);
}

/**
 * It counts the number of pipes in a command
 * 
 * @param tokens The tokens array
 * 
 * @return The number of pipes in the command.
 */
int	count_pipas(char **tokens)
{
	int	i;
	int	count;
	int	final;

	i = 0;
	final = 0;
	if (tokens[i] != NULL)
		count = 1;
	while (tokens[i])
	{
		if (token_is_pipe(tokens[i]) == 1 && tokens[i + 1]
			&& token_is_pipe(tokens[i + 1]) != 1)
		{
			count += 2;
			final++;
		}
		else if (tokens[i] && token_is_pipe(tokens[i]) == 1 && !tokens[i + 1])
		{
			count ++;
			final++;
		}
		i++;
	}
	return (count - final);
}

/**
 * It joins the tokens into the final array
 * 
 * @param final the final array of strings that will be returned
 * @param tokens the array of tokens
 * @param i the index of the token we're currently on
 * @param j the index of the final array
 */
void	join_commands(char **final, char **tokens, int *i, int *j)
{
	char	*aux;

	aux = NULL;
	if (final[*(j)] == NULL)
		final[*(j)] = ft_strdup(tokens[*(i)]);
	else
	{
		aux = final[*(j)];
		final[*(j)] = ft_strjoin(aux, " ");
		free(aux);
		aux = final[*(j)];
		final[*(j)] = ft_strjoin(aux, tokens[*(i)]);
		free(aux);
	}
}

/**
 * It takes a list of tokens, and returns a list of tokens where each token is
 * either a command or a symbol
 * 
 * @param tokens the array of tokens
 * 
 * @return A pointer to a pointer to a char.
 */
char	**tokens_to_pipas(char **tokens)
{
	int		i;
	int		j;
	char	**final;

	i = 0;
	j = 0;
	final = (char **)ft_calloc(sizeof(char *), (count_pipas(tokens) + 1));
	if (!final)
		return (tokens);
	while (tokens[i])
	{
		if (token_is_pipe(tokens[i]))
		{
			if (i != 0)
				j++;
		}
		if (!token_is_pipe(tokens[i]))
			join_commands(final, tokens, &i, &j);
		i++;
	}
	final[count_pipas(tokens)] = NULL;
	ft_free_matrix(tokens);
	return (final);
}

/**
 * It checks if there are two symbols in a row
 * 
 * @param tokens The array of tokens
 */
int	double_symbols(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (token_is_symbol(tokens[i]) == 1 && tokens[i + 1]
			&& token_is_symbol(tokens[i + 1]))
			return (1);
		i++;
	}
	if (tokens[i - 1] && token_is_symbol(tokens[i - 1]) == 1)
		return (1);
	return (0);
}
