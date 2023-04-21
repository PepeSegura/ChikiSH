/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:01:49 by psegura-          #+#    #+#             */
/*   Updated: 2023/04/21 17:15:22 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_old_pwd(void)
{
	char	*pwd;
	char	*aux;
	int		i = 0;

	while (g_c.env[i])
	{
		if (ft_strncmp("PWD=", g_c.env[i], 4) == 0)
			pwd = g_c.env[i] + 4;
		i++;
	}
	aux = ft_strjoin("OLDPWD=", pwd);

	char	*path_2[] = {"export", aux, NULL};

	ft_print_matrix(path_2, "set_old");
	ft_export(g_c.env, path_2);
}

void	set_new_pwd(void)
{
	char	*pwd;
	char	*aux;

	pwd = getcwd(NULL, 0);
	aux = ft_strjoin("PWD=", pwd);
	free(pwd);

	char	*path_2[] = {"export", aux, NULL};

	ft_print_matrix(path_2, "set_new");
	ft_export(g_c.env, path_2);
}

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
int	ft_cd(char **commands)
{
	char	*path;
	int		i;

	i = 1;
	set_old_pwd();
	ft_print_matrix(commands, "new_dir");
	path = commands[i];
	if (!path)
	{	
		while (g_c.env[i])
		{
			if (ft_strncmp("HOME=", g_c.env[i], 5) == 0)
				chdir(g_c.env[i] + 5);
			i++;
		}
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		while (g_c.env[i])
		{
			if (ft_strncmp("OLDPWD=", g_c.env[i], 7) == 0)
				chdir(g_c.env[i] + 7);
			i++;
		}
	}
	else if (chdir(path) == -1)
		printf("cd: %s: No such file or directory\n", path);
	set_new_pwd();
	ft_free_matrix(commands);
	return (EXIT_SUCCESS);
}
