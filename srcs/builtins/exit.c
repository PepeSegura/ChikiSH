/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgarci <davgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:02:00 by psegura-          #+#    #+#             */
/*   Updated: 2023/03/25 17:23:04 by davgarci         ###   ########.fr       */
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
			ft_printf("msh: exit: %s : numeric argument required\n", args[0]);
			exit(255);
		}
		i++;
	}
	while (args[k])
	{
		if (++k > 1)
		{
			ft_printf("msh: exit: too many arguments\n");
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
