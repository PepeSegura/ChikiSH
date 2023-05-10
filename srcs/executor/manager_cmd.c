/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:21:39 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/10 02:02:50 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CHILD	0
#define ANY 	-1

void	child_process(int i, t_info_cmd *info)
{
	int	flag;

	flag = 1;
	open_redirect(info);
	close(g_c.pipa[RIGHT]);
	//TODO: REVISAR POR QUE INFO->RE ES NULL SIEMPRE!!!!
	dprintf(2, "hola manolo [%p]\n", info->re);
	if (info->re)
	{
		if (info->re->type == 2 || info->re->type == 3)
			flag = 0;
	}
	dprintf(2, "flag [%d]\n", flag);
	//TO DO DESPUES DEL DUP HAY QUE CERRAR AMBOS EN HIJOS(LOS BUILTINGS NO HAY QUE HACER) 
	if (i > 0)
		dup2(g_c.prev, STDIN_FILENO);
	if (i < g_c.tok_count - 1 && flag == 1)
		dup2(g_c.pipa[LEFT], STDOUT_FILENO);
	ft_exec(info->cmd_args);
}

void	pipex(t_info_cmd *info)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i <= g_c.tok_count - 1)
	{
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
