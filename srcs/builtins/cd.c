/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:01:49 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/22 00:19:42 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * It changes the current working directory to the one specified by the user.
 * 
 * @param tokens An array of strings, each string is a token from the command
 * line.
 * @param env The environment variables.
 * 
 * @return The return value of the function is the return value of the last
 * command executed.
 */
int	ft_cd(char **env, char **commands)
{
	char		*path;
	int			i;

	i = 1;
	path = commands[i];
	if (ft_len_matrix(commands) > 2)
		printf("cd: too many arguments\n");
	else
	{
		if (!path)
		{	
			while (env[i])
			{
				if (ft_strncmp("HOME=", env[i], 5) == 0)
					chdir(env[i] + 5);
				i++;
			}
		}
		else if (chdir(path) == -1)
			printf("cd: No such file or directory\n");
	}
	if (g_c.tok_count > 1)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
