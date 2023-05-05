/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:21:39 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/04 23:39:02 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CHILD	0
#define ANY 	-1

#define WRITE_END 1
#define READ_END 0

void	ft_exec(const char *argv)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, SPACE);
	free((void *)argv);
	if (cmd == NULL)
		exit_failure("malloc", NULL, 1);
	path = cmd[0];
	if (!path)
	{
		cmd_not_found("");
		exit_failure(path, cmd, 0);
	}
	if (cmd[0][0] != '/'
		&& ft_strncmp(cmd[0], "./", 2) && ft_strncmp(cmd[0], "../", 3))
	{
		path = only_path(cmd[0]);
		if (!path)
		{
			cmd_not_found(cmd[0]);
			exit_failure(path, cmd, 0);
		}
	}
	execve(path, cmd, g_c.env);
	exit_failure(path, cmd, 1);
}

#define RIGHT 0
#define LEFT 1

void	child_process(int i)
{
	close(g_c.pipa[RIGHT]);
	if (i > 0)
		dup2(g_c.prev, STDIN_FILENO);
	if (i < g_c.tok_count - 1)
		dup2(g_c.pipa[LEFT], STDOUT_FILENO);
	// TODO redir
	ft_exec(g_c.tokens[i]);
}

void	ft_wait(int *status)
{
	int	i;

	close(g_c.pipa[RIGHT]);
	g_c.prev = 0;
	i = 0;
	while (i++ < g_c.tok_count)
		waitpid(ANY, status, 0);
}

void	pipex(void)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i <= g_c.tok_count - 1)
	{
		if (pipe(g_c.pipa) < 0)
			ft_perror("pipe ");
		pid = fork();
		if (pid < 0)
			ft_perror("fork ");
		else if (pid == CHILD)
			child_process(i);
		else
		{
			if (g_c.prev > 0)
				close(g_c.prev);
			close(g_c.pipa[LEFT]);
			g_c.prev = g_c.pipa[RIGHT];
		}
		i++;
	}
	ft_wait(&status);
	// printf("status: [%d]\n", status);
}

void	pipas_handler(void)
{
	pipex();
}
