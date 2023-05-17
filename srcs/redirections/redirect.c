/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:23:43 by agserran          #+#    #+#             */
/*   Updated: 2023/05/18 00:34:28 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_files(int identifier, char *filename)
{
	int	fd;

	if (identifier == INPUT_F)
		fd = open(filename, O_RDONLY);
	if (identifier == TRUNC_F)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (identifier == APPEND_F)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_perror(filename);
	return (fd);
}

void	open_redirect(t_info_cmd *info, t_last_red *last)
{
	int	fd[2];

	ft_memset(fd, 0, sizeof(int) * 2);
	while (info->re)
	{
		if (info->re->type == TRUNC_F || info->re->type == APPEND_F)
		{
			if (info->re->type == TRUNC_F)
				fd[1] = open_files(TRUNC_F, info->re->file);
			if (info->re->type == APPEND_F)
				fd[1] = open_files(APPEND_F, info->re->file);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			last->type = info->re->type;
			last->file = ft_strdup(info->re->file);
		}
		if (info->re->type == INPUT_F)
		{
			fd[0] = open_files(INPUT_F, info->re->file);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		info->re = info->re->next;
	}
	unlink(TEMP_FILE);
}
