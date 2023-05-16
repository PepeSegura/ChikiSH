/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:01:54 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/15 11:18:00 by agserran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **commands)
{
	int	i;
	int	menos_n;

	i = 0;
	menos_n = 0;
	if (commands[1] && ft_strcmp(commands[1], "-n") == 0)
	{
		i++;
		menos_n++;
	}
	i++;
	while (commands[i])
	{
		ft_putstr_fd(commands[i], STDOUT_FILENO);
		if (commands[++i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (menos_n == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	// ft_free_matrix(commands);
	return (EXIT_SUCCESS);
}
