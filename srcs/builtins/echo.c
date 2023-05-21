/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:01:54 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/22 01:09:22 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag(char *flag)
{
	char	*n_chars;
	size_t	i;

	n_chars = flag + 1;
	i = 0;
	while (n_chars[i])
	{
		if (n_chars[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **commands)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (commands[i] && check_flag(commands[i]))
	{
		flag++;
		i++;
	}
	while (commands[i])
	{
		ft_putstr_fd(commands[i], STDOUT_FILENO);
		if (commands[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (flag == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (g_c.tok_count > 1)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
