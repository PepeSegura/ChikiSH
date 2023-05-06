/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:37:31 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/06 01:37:23 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cosas	g_c;

/*
TODO: REVISAR LA EXPANSION ANTES DE LAS LISTAS. 
TODO: ejemplo echo "hola pepe" -> "echo" "hola" "pepe"
*/
int	main(int argc, char **argv, char **env)
{
	(void)argc, (void)argv;
	// ft_print_header();
	g_c.env = ft_get_env(env);
	manage_signal();
	readline_create();
	return (0);
}
