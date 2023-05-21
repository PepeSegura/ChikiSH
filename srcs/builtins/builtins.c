/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:57:51 by davgarci          #+#    #+#             */
/*   Updated: 2023/05/21 16:43:22 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_stdin_stdout(int fd[2], t_redirect *re)
{
	if (re->type == TRUNC_F || re->type == APPEND_F)
	{
		fd[1] = open_files_b(re->type, re->file);
		if (fd[1] == -1)
			return (1);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (re->type == INPUT_F || re->type == H_DOC_F)
	{
		fd[0] = open_files_b(INPUT_F, re->file);
		if (fd[0] == -1)
			return (1);
		if (re->type == H_DOC_F)
			unlink(re->file);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return (0);
}

void	restore_stdin_stdout(int fd_cp[2])
{
	dup2(fd_cp[0], STDIN_FILENO);
	dup2(fd_cp[1], STDOUT_FILENO);
	close(fd_cp[0]);
	close(fd_cp[1]);
}

void	builtin_with_redirect(t_info_cmd *info)
{
	int	fd[2];
	int	fd_cp[2];

	fd_cp[0] = dup(STDIN_FILENO);
	fd_cp[1] = dup(STDOUT_FILENO);
	ft_memset(fd, 0, sizeof(int) * 2);
	while (info->re)
	{
		if (redirect_stdin_stdout(fd, info->re) == 0)
			info->re = info->re->next;
		else
		{
			g_c.dolar_q = 1;
			return ;
		}
	}
	builtin_executor(info->cmd_args, g_c.env);
	restore_stdin_stdout(fd_cp);
}

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
