/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:21:39 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/21 14:10:37 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CHILD 0
#define ANY -1

void	child_process(int i, t_info_cmd *info)
{
	int			flag;
	t_last_red	last;

	signal_child();
	flag = 1;
	ft_memset(&last, 0, sizeof(t_last_red));
	open_redirect(info, &last);
	close(g_c.pipa[RIGHT]);
	if (last.file)
	{
		if (last.type == 2 || last.type == 3)
			flag = 0;
	}
	if (i > 0)
		dup2(g_c.prev, STDIN_FILENO);
	if (i < g_c.tok_count - 1 && flag == 1)
		dup2(g_c.pipa[LEFT], STDOUT_FILENO);
	if (cmd_is_builtin(info->cmd) == BUILTIN)
		builtin_executor(info->cmd_args, g_c.env);
	else
		ft_exec(info->cmd_args);
}

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

void	pipex(t_info_cmd *info)
{
	int		i;
	pid_t	pid;

	i = 0;
	if (cmd_is_builtin(info->cmd) == BUILTIN && g_c.tok_count == 1)
		return (builtin_with_redirect(info));
	while (i <= g_c.tok_count - 1)
	{
		create_pipe();
		pid = create_fork();
		if (pid == CHILD)
			child_process(i, info);
		else
		{
			signal_ignore();
			if (g_c.prev > 0)
				close(g_c.prev);
			close(g_c.pipa[LEFT]);
			g_c.prev = g_c.pipa[RIGHT];
		}
		info = info->next;
		i++;
	}
	wait_child();
}
