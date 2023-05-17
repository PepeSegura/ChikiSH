/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:21:39 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/17 09:40:44 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CHILD	0
#define ANY 	-1

void	child_process(int i, t_info_cmd *info)
{
	int	flag;
	t_last_red last;

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
	{
		builtin_executor(info->cmd_args, g_c.env);
		exit(42);
	}
	else
		ft_exec(info->cmd_args);
}

void	pipex(t_info_cmd *info)
{
	int		i;
	pid_t	pid;

	i = 0;
	if (cmd_is_builtin(info->cmd_args[0]) == BUILTIN && g_c.tok_count == 1)
		return (builtin_executor(info->cmd_args, g_c.env));
	while (i <= g_c.tok_count - 1)
	{
		dprintf(2, "HAY PIPES\n");
		create_pipe();
		pid = create_fork();
		if (pid == CHILD)
			child_process(i, info);
		else
		{
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
