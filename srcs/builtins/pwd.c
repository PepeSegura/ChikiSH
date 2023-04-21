/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:02:06 by psegura-          #+#    #+#             */
/*   Updated: 2023/04/20 20:21:16 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **commands)
{
	char	*str_pwd;

	(void) commands;
	str_pwd = malloc(1024);
	getcwd(str_pwd, 1024);
	ft_putendl_fd(str_pwd, 1);
	free(str_pwd);
	return (EXIT_SUCCESS);
}
