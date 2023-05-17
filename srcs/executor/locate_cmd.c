/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:26:54 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/17 23:28:45 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path(char *cmd)
{
	int	i;

	i = 0;
	while (g_c.env[i])
	{
		if (ft_strncmp(g_c.env[i], "PATH=", 5) == 0)
			return (g_c.env[i] + 5);
		i++;
	}
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(127);
	return (0);
}

char	*only_path(char *cmd)
{
	int			i;
	char		**env_paths;
	char		*path;
	char		*path_cmd;
	const char	*env;

	env = check_path(cmd);
	env_paths = ft_split(env, ':');
	i = 0;
	while (env_paths[i])
	{
		path = ft_strjoin(env_paths[i], "/");
		path_cmd = ft_strjoin(path, cmd);
		free(path);
		if (access(path_cmd, X_OK) == 0)
		{
			ft_free_matrix(env_paths);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	ft_free_matrix(env_paths);
	return (EXIT_SUCCESS);
}

void	exit_failure(char *err_msg, int flag)
{
	if (flag == 1)
		perror(err_msg);
	exit(flag);
}

void	cmd_not_found(char *cmd)
{
	char	*error;

	error = ft_strjoin(cmd, ": command not found\n");
	ft_putstr_fd(error, 2);
	free(error);
	g_c.dolar_q = CMD_NOT_FOUND;
}
