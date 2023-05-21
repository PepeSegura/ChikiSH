/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:35:24 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/21 14:54:33 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(char **cmd)
{
	char	*path;

	if (cmd == NULL)
		exit(0);
	path = cmd[0];
	if (!path)
	{
		cmd_not_found("");
		exit_failure(path, 127);
	}
	if (cmd[0][0] != '/'
		&& ft_strncmp(cmd[0], "./", 2) && ft_strncmp(cmd[0], "../", 3))
	{
		path = only_path(cmd[0]);
		if (!path)
		{
			cmd_not_found(cmd[0]);
			exit_failure(path, 127);
		}
	}
	execve(path, cmd, g_c.env);
	exit_failure(path, 1);
}
