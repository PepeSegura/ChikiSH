/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:35:24 by psegura-          #+#    #+#             */
/*   Updated: 2023/03/29 01:59:51 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_exec(char **cmd)
// {
// 	char	*path;

// 	path = NULL;
// 	if (cmd == NULL)
// 		exit_failure("malloc", NULL, 1);
// 	path = cmd[0];
// 	if (cmd[0][0] != '/' && cmd[0][0] != '.')
// 	{
// 		path = only_path(cmd[0]);
// 		if (!path)
// 		{
// 			cmd_not_found(cmd[0]);
// 			exit_failure(path, cmd, 127);
// 		}
// 	}
// 	execve(path, cmd, g_c.env);
// 	exit_failure(path, cmd, 1);
// }
