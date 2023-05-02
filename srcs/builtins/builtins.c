/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:57:51 by davgarci          #+#    #+#             */
/*   Updated: 2023/04/28 19:34:21 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	builtins(char *commands)
// {
// 	char	**cmd_matrix;

// 	cmd_matrix = ft_split(commands, SPACE);
// 	if (!commands)
// 		return (1);
// 	else if (ft_strcmp(cmd_matrix[0], "pwd") == 0)
// 		return (ft_	pwd(cmd_matrix));
// 	else if (ft_strcmp(cmd_matrix[0], "env") == 0)
// 		return (ft_env(g_c.env, cmd_matrix));
// 	else if (ft_strcmp(cmd_matrix[0], "cd") == 0)
// 		return (ft_cd(cmd_matrix));
// 	// else if (ft_strcmp(commands[0], "echo") == 0)
// 	// 	return (ft_echo(commands));
// 	else if (ft_strcmp(cmd_matrix[0], "export") == 0)
// 		return (ft_export(g_c.env, cmd_matrix));
// 	// else if (ft_strcmp(commands[0], "unset") == 0)
// 	// 	return (ft_unset(g_c.env, commands));
// 	// else if (ft_strcmp(commands[0], "exit") == 0)
// 	// 	return (ft_exit(commands));
// 	else
// 		return (42);
// }
