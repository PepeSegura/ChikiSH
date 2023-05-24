/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:16:12 by pepe              #+#    #+#             */
/*   Updated: 2023/05/24 13:39:06 by pepe             ###   ########.fr       */
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
		{
			ft_putendl_fd(WARNING_EOF, 2);
			break ;
		}
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

char	*create_filename(void)
{
	static int	i = 0;
	char		*filename;
	char		*nbr;

	while (i < 1000)
	{
		nbr = ft_itoa(i);
		filename = ft_strjoin("/tmp/.CSH_here_doc_", nbr);
		if (!filename)
			continue ;
		free(nbr);
		if (access(filename, F_OK))
			return (filename);
		free(filename);
		i++;
	}
	i = 0;
	ft_print_error("Cannot create file in /tmp");
	return (filename);
}
