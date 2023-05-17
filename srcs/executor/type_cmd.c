/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 05:11:14 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/17 09:32:12 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_is_builtin(char *cmd)
{
	int			i;
	int			type;
	const char	*symbols[] = {"pwd", "env", "cd", "echo", "export",
		"unset", NULL};

	// if (!cmd)
	// 	return (0);
	// if (cmd == NULL)
	// 	exit_failure("malloc", NULL, 1);
	type = OTHER;
	i = -1;
	while (symbols[++i])
		if (ft_strcmp(cmd, symbols[i]) == 0)
			type = BUILTIN;
	return (type);
}

int	cmd_is_stdlib(char *argv)
{
	char	**cmd;
	char	*path;

	path = NULL;
	cmd = ft_split(argv, SPACE);
	free((void *)argv);
	if (cmd == NULL)
		exit_failure("malloc", NULL, 1);
	path = cmd[0];
	if (cmd[0][0] != '/' && cmd[0][0] != '.')
	{
		path = only_path(cmd[0]);
		if (!path)
			return (OTHER);
	}
	return (STDLIB);
}

int	what_cmd(char *argv)
{
	char	**cmd;
	char	*path;

	path = NULL;
	cmd = ft_split(argv, SPACE);
	if (cmd == NULL)
		exit_failure("malloc", NULL, 1);
	path = cmd[0];
	if (cmd_is_builtin(path) == BUILTIN)
		return (BUILTIN);
	if (cmd_is_stdlib(path) == STDLIB)
		return (STDLIB);
	else
		return (OTHER);
}

void	builtin_executor(char **cmd, char **env)
{
	dprintf(2, "BUILTIN\n");
	if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd(cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(env);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(env, cmd);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd);
}
