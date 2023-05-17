/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:02:06 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/17 10:33:20 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **commands)
{
	char	*str_pwd;

	(void) commands;
	str_pwd = malloc(1024);
	getcwd(str_pwd, 1024);
	ft_putstr_fd(str_pwd, 1);
	ft_putchar_fd('\n', 1);
	free(str_pwd);
	if (g_c.tok_count > 1)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
