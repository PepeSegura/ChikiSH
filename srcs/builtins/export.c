/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:02:04 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/24 14:33:42 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_export
{
	int		pos;
	int		i;
	char	**temp;
	char	*aux;
	int		flag;
}			t_export;

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
	while (str[i] && str[i] != '=')
	{
		if (i == 0 && (ft_isalpha(str[i]) == 0 && str[i] != '_'))
			return (0);
		if (i != 0 && ((ft_isalnum(str[i]) == 0) && str[i] != '_'))
			return (0);
		i++;
	}
	if (ft_strchr(str, '=') == NULL)
		return (2);
	if (str[0] == '=')
		return (0);
	return (1);
}

int	ft_print_exported(char **matrix)
{
	int	i;

	i = 0;
	ft_sort_matrix(matrix);
	while (matrix[i])
	{
		printf("declare -x %s\n", matrix[i]);
		i++;
	}
	return (0);
}

void	export_aux(t_export *e, char **args)
{
	if (g_c.env == NULL)
		g_c.env = malloc(1);
	e->aux = find_until_char(args[e->i], '=');
	e->pos = ft_locate_str_in_matrix(g_c.env, e->aux);
	if (ft_strcmp(e->aux, args[e->i]))
		free(e->aux);
	g_c.env = ft_delete_row_matrix(g_c.env, e->pos);
	e->temp = ft_add_row_matrix(g_c.env, args[e->i]);
	ft_free_matrix(g_c.env);
	g_c.env = ft_cpy_matrix(e->temp);
}

int	ft_export(char **args)
{
	t_export	e;

	ft_memset(&e, 0, sizeof(t_export));
	if (!args[1] && g_c.tok_count > 1)
		exit(ft_print_exported(g_c.env));
	if (!args[1])
		return (ft_print_exported(g_c.env));
	e.i = 0;
	while (args[++e.i])
	{
		if (check_syntax(args[e.i]) == 0 || check_syntax(args[e.i]) == 2)
		{
			if (check_syntax(args[e.i]) == 2)
				continue ;
			printf("export: %s: not a valid identifier\n", args[e.i]);
			e.flag = 1;
			continue ;
		}
		export_aux(&e, args);
	}
	if (g_c.tok_count > 1)
		exit(e.flag);
	return (e.flag);
}
