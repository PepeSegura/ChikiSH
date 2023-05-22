/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:55:15 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/22 17:48:47 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_exit(char *command_buf)
{
	if (!ft_strcmp(command_buf, "quit")
		|| !ft_strcmp(command_buf, "e") || !ft_strcmp(command_buf, "q"))
	{
		free(command_buf);
		return (1);
	}
	return (0);
}

void	expand_while(void)
{
	g_c.tok_count = 0;
	while (g_c.tokens[g_c.tok_count])
	{
		g_c.tokens[g_c.tok_count] = expan_token(g_c.tokens[g_c.tok_count],
				g_c.env);
		g_c.tok_count++;
	}
	g_c.tokens[g_c.tok_count] = NULL;
}

int	ft_continue(char *command_buf)
{
	if (ft_strlen(command_buf) == 0)
	{
		free(command_buf);
		return (1);
	}
	else
		add_history(command_buf);
	if (!check_quotes(command_buf))
	{
		printf("The quotes are not closed!\n");
		free(command_buf);
		return (1);
	}
	g_c.tokens = malloc(sizeof(char *) * (count_tokens(command_buf) + 1));
	store_tokens(command_buf, g_c.tokens);
	if (double_symbols(g_c.tokens) == 1)
	{
		g_c.dolar_q = 258;
		free(command_buf);
		return (1);
	}
	return (0);
}

void	readline_create(void)
{
	char		*command_buf;
	char		*line;
	t_info_cmd	*info;

	while (1)
	{
		manage_signal();
		if (isatty(fileno(stdin)))
			line = readline(PROMPT);
		command_buf = ft_strtrim(line, " \f\n\r\t\v");
		free(line);
		if (!command_buf)
			exit(0);
		if (read_exit(command_buf))
			break ;
		if (ft_continue(command_buf))
			continue ;
		free(command_buf);
		expand_while();
		info = process_input(g_c.tokens);
		pipex(info);
		free_lst(info);
	}
}

		// print_lst(info);