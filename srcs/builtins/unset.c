/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:02:08 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/30 14:55:08 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && (ft_isalpha(str[i]) == 0 && str[i] != '_'))
			return (0);
		if (i != 0 && ((ft_isalnum(str[i]) == 0) && str[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(char **args)
{
	int		pos;
	char	*to_find;
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	while (args[i])
	{
		if (check_syntax(args[i]) == 0)
		{
			printf("unset: %s: not a valid identifier\n", args[i++]);
			flag = 1;
			continue ;
		}
		to_find = ft_strjoin(args[i], "=");
		pos = ft_locate_str_in_matrix(g_c.env, to_find);
		free(to_find);
		if (pos != -10)
			g_c.env = ft_delete_row_matrix(g_c.env, pos);
		i++;
	}
	if (g_c.tok_count > 1)
		exit(flag);
	return (flag);
}
