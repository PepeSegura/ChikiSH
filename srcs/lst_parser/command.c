/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 01:58:02 by pepe              #+#    #+#             */
/*   Updated: 2023/05/01 02:09:45 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*path_shorter(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

int	is_command(char *cmd, char **env)
{
	char	**paths;
	int		i;
	char	*path_cmd;
	char	*path;
	char	*aux;

	i = 0;
	paths = ft_split(aux = path_shorter(env), ':');
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin(path, cmd);
		if (access(path_cmd, X_OK) == 0)
		{
			free(path);
			free(path_cmd);
			ft_free_matrix(paths);
			return (1);
		}
		free(path);
		free(path_cmd);
		i++;
	}
	ft_free_matrix(paths);
	return (-1);
}
