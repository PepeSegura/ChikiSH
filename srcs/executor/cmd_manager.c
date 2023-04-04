/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:21:39 by psegura-          #+#    #+#             */
/*   Updated: 2023/04/04 18:13:16 by pepe             ###   ########.fr       */
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
	if (cmd[0][0] != '/' && cmd[0][0] != '.')
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

// void	first_child(int *pipa)
// {
// 	pid_t	child;
// 
// 	// dprintf(STDERR_FILENO, "[FIRST_CHILD] pipe: %d, %d\n", pipa[0], pipa[1]);
// 	child = fork();
// 	if (child < 0)
// 		ft_perror("fork ");
// 	if (child == CHILD)
// 	{
// 		if (dup2(pipa[1], 1) == -1) {
// 			perror("in dup2 of STDOUT");
// 		}
// 		close(pipa[0]);
// 		close(pipa[1]);
// 		ft_exec(g_c.tokens[0]);
// 	}
// }
// void	mid_child(int *prev, int *pipa)
// {
// 	pid_t child;
// 	int ret_dup2;
// 
// 	// dprintf(STDERR_FILENO, "[MID_CHILD] prev: %d, %d | pipe: %d, %d\n", prev[0], prev[1], pipa[0], pipa[1]);
// 	child = fork();
// 	if (child < 0)
// 		ft_perror("fork ");
// 	if (child == CHILD)
// 	{
// 		ret_dup2 = dup2(prev[0], 0) ;
// 		if (ret_dup2 == -1) {
// 			perror("in dup2 of STDIN");
// 		}
// 		ret_dup2 = dup2(pipa[1], 1);
// 		if (ret_dup2 == -1) {
// 			perror("in dup2 of STDOUT");
// 		}
// 		dprintf(STDERR_FILENO, "[ dup ret mid1 ] %d\n", ret_dup2);		
// 		close(prev[0]);
// 		close(prev[1]);
// 		close(pipa[0]);
// 		close(pipa[1]);
// 		ft_exec(g_c.tokens[1]);
// 	}
// }
// void	last_child(int *pipa)
// {
// 	pid_t child;
// 
// 	dprintf(STDERR_FILENO, "[LAST_CHILD] pipe: %d, %d\n", pipa[0], pipa[1]);
// 	child = fork();
// 	if (child < 0)
// 		ft_perror("fork ");
// 	if (child == CHILD)
// 	{
// 		int ret_dup2 = dup2(pipa[0], 0);
// 		if (ret_dup2 == -1) {
// 			perror("in dup2 of STDIN");
// 		}
// 		close(pipa[1]);
// 		close(pipa[0]);
// 		ft_exec(g_c.tokens[2]);
// 	}
// }
// /*
// ls | cat -e | cat -e
// */
// void	pipas_handler(void)
// {
// 	int		pipa[2];
// 	int		prev[2];
// 	int		status;
// 	int		waiting;
// 	
// 	waiting = ft_len_matrix(g_c.tokens);
// 	if (waiting != 3)
// 		return ;
// 	if (pipe(pipa) < 0)
// 		ft_perror(NULL);
// 	first_child(pipa);
// 	prev[0] = pipa[0];
// 	prev[1] = pipa[1];
// 	if (pipe(pipa) < 0)
// 		ft_perror(NULL);
// 	mid_child(prev, pipa);
// 	close(prev[0]);
// 	close(prev[1]);
// 	close(pipa[1]);
// 	last_child(pipa);
// 	close(pipa[0]);
// 	while (waiting-- > 0)
// 	{
// 		waitpid(ANY, &status, 0);
// 		// ret = waitpid(ANY, &status, 0);
// 		// if ret == last_pid
// 		// 	status = WEXITSTATUS(status);
// 	}
// }

#define RIGHT 0
#define LEFT 1

void	child_process(int i)
{
	close(g_c.pipa[RIGHT]);
	if (i > 0)
		dup2(g_c.prev, STDIN_FILENO);
	if (i < g_c.tok_count - 1)
		dup2(g_c.pipa[LEFT], STDOUT_FILENO);
	ft_exec(g_c.tokens[i]);
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
			close(g_c.prev);
			close(g_c.pipa[LEFT]);
			g_c.prev = g_c.pipa[RIGHT];
		}
		i++;
	}
	i = 0;
	while (i++ < g_c.tok_count)
		waitpid(ANY, &status, 0);
}

void	pipas_handler(void)
{
	pid_t	pid;
	int		status;

	// ft_print_matrix(g_c.tokens, "tok");
	pid = fork();
	if (pid < 0)
		ft_perror("fork ");
	if (pid == CHILD)
	{
		pipex();
		exit(0);
	}
	else
		waitpid(ANY, &status, 0);
}
