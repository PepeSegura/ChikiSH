/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:33:59 by pepe              #+#    #+#             */
/*   Updated: 2023/06/12 03:46:59 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	create_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_perror("fork ");
	g_c.last_pid = pid;
	return (pid);
}

void	create_pipe(void)
{
	if (pipe(g_c.pipa) < 0)
		ft_perror("pipe ");
}

void	wait_child(void)
{
	int	status;
	int	pid;

	close(g_c.pipa[RIGHT]);
	g_c.prev = 0;
	g_c.dolar_q = 0;
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid <= 0)
			break ;
		if (pid == g_c.last_pid)
		{
			if (WEXITSTATUS(status))
				g_c.dolar_q = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				g_c.dolar_q = WTERMSIG(status) + 128;
		}
	}
}
