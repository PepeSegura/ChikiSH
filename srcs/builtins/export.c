/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgarci <davgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:02:04 by psegura-          #+#    #+#             */
/*   Updated: 2023/03/25 04:16:10 by davgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_until_char(char *str, char letter)
{
	int		i;
	char	*result;

	i = 0;
	while (str[i] != '\0' && str[i] != letter)
		i++;
	if (str[i])
	{
		result = ft_strndup(str, i);
		return (result);
	}
	return (str);
}

int	check_syntax(char *str)
{
	int	i;

	i = 0;
	if (ft_strchr(str, '=') == NULL)
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (i == 0 && (ft_isalpha(str[i]) == 0 && str[i] != '_'))
			return (0);
		if (i != 0 && ((ft_isalnum(str[i]) == 0) && str[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_print_exported(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		printf("declare -x %s\n", matrix[i]);
		i++;
	}
	return (0);
}

int	ft_export(char **env, char **args)
{
	int		pos;
	int		i;
	char	**temp;
	char	*aux;

	if (!args[1])
		return (ft_print_exported(env));
	i = 0;
	while (args[++i])
	{
		if (check_syntax(args[i]) == 0)
			return (printf("export: %s: not a valid identifier\n", args[i]));
		aux = find_until_char(args[i], '=');
		pos = ft_locate_str_in_matrix(g_c.env, aux);
		if (ft_strcmp(aux, args[i]))
			free(aux);
		g_c.env = ft_delete_row_matrix(g_c.env, pos);
		temp = ft_add_row_matrix(g_c.env, args[i]);
		ft_free_matrix(g_c.env);
		g_c.env = ft_cpy_matrix(temp);
		ft_free_matrix(temp);
	}
	ft_free_matrix(env);
	return (EXIT_SUCCESS);
}
