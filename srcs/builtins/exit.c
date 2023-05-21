/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:02:00 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/21 14:13:58 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit_args(char **args, int j)
{
	int			i;
	int			k;

	i = 0;
	k = 0;
	if (ft_strncmp(args[0], "-", 1) == 0)
		i++;
	while (args[0][i])
	{
		if (ft_isdigit(args[0][i]) != 1)
		{
			printf("msh: exit: %s : numeric argument required\n", args[0]);
			exit(2);
		}
		i++;
	}
	while (args[k])
	{
		if (++k > 1)
		{
			printf("msh: exit: too many arguments\n");
			exit(1);
		}
	}
	exit(j);
}

int	ft_exit(char **args)
{
	int			j;

	if (args[1])
	{
		j = ft_atoi(args[1]);
		ft_exit_args(++args, j);
	}
	else
		exit(g_c.dolar_q);
	return (0);
}
