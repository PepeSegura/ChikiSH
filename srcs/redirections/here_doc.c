/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:16:12 by pepe              #+#    #+#             */
/*   Updated: 2023/05/18 00:15:51 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(char *filename)
{
	ft_putstr_fd("\033[0;32m➜  \033[0;36mhere_doc_\033[0;31m", 1);
	ft_putstr_fd(filename, 1);
	ft_putstr_fd("\033[0m \033[1;33m✗ \033[0m", 1);
}

void	here_doc(char *limit, int fd)
{
	char	*line;
	char	*clean;

	line = "";
	while (1)
	{
		print_prompt(limit);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			ft_print_error("Malloc KO");
		clean = ft_strtrim(line, "\n");
		if (ft_strcmp(clean, limit) != 0)
			ft_putstr_fd(line, fd);
		free(line);
		if (ft_strcmp(clean, limit) == 0)
		{
			free(clean);
			break ;
		}
		free(clean);
	}
}
