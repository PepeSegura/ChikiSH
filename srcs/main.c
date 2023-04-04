/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:37:31 by psegura-          #+#    #+#             */
/*   Updated: 2023/04/04 17:58:19 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cosas	g_c;

int	main(int argc, char **argv, char **env)
{
	(void)argc, (void)argv;
	// ft_memset(&g_c, 0, sizeof(t_cosas));
	g_c.env = ft_get_env(env);
	g_c.dolar_q = 0;
	manage_signal();
	readline_create();
	return (0);
}
