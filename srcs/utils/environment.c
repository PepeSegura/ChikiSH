/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:35:36 by davgarci          #+#    #+#             */
/*   Updated: 2023/05/07 04:49:59 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_env(char **env)
{
	char	**aux;
	int		i;

	if (!env)
		return (NULL);
	aux = malloc(sizeof(char *) * (ft_len_matrix(env) + 1));
	if (!aux)
		return (NULL);
	i = 0;
	while (env[i])
	{
		aux[i] = ft_strdup(env[i]);
		if (!aux[i])
			return (ft_free_matrix(aux), NULL);
		i++;
	}
	aux[i] = NULL;
	return (aux);
}
