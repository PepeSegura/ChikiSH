/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:52:23 by psegura-          #+#    #+#             */
/*   Updated: 2023/04/18 19:25:41 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_cpy_matrix(char **matrix)
{
	char	**aux;
	int		i;

	if (!matrix)
		return (NULL);
	aux = malloc(sizeof(char *) * (ft_len_matrix(matrix) + 1));
	if (!aux)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		aux[i] = ft_strdup(matrix[i]);
		if (!aux[i])
			return (ft_free_matrix(aux), NULL);
		i++;
	}
	aux[i] = NULL;
	return (aux);
}
