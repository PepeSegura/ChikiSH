/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:57:51 by davgarci          #+#    #+#             */
/*   Updated: 2023/05/17 11:02:16 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_executor(char **cmd, char **env)
{
	if (ft_strcmp(cmd[0], "pwd") == 0)
		g_c.dolar_q = ft_pwd(cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		g_c.dolar_q = ft_env(env);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		g_c.dolar_q = ft_cd(env, cmd);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		g_c.dolar_q = ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		g_c.dolar_q = ft_export(cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		g_c.dolar_q = ft_unset(cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		g_c.dolar_q = ft_exit(cmd);
}
