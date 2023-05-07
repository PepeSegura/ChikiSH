/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_expand_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:13:06 by davgarci          #+#    #+#             */
/*   Updated: 2023/05/07 04:49:18 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cp_find_dolar_q(t_expand *expand, char *new_str)
{
	char	*nbr;
	char	*result;

	expand->i++;
	nbr = ft_itoa(g_c.dolar_q);
	expand->n += ft_strlen(nbr);
	result = copy_join(new_str, nbr, expand);
	free(nbr);
	return (result);
}

char	*cp_find_dolar(t_expand *expand, char *command_buf, char **environment,
	char *new_str)
{
	expand->i++;
	if ((ft_isdigit(command_buf[expand->i]) == 1))
	{
		expand->i++;
		return (new_str);
	}
	else if (command_buf[expand->i] == '?')
		return (cp_find_dolar_q(expand, new_str));
	else if (command_buf[expand->i] == ' ' || command_buf[expand->i] == '\0')
	{
		cp_find_dolar_aux(expand, command_buf, new_str);
		return (new_str);
	}
	expand->k = expand->i;
	while (ft_isalnum(command_buf[expand->i]) || command_buf[expand->i] == '_')
		expand->i++;
	expand->n += ft_strlen(cp_expander(command_buf + expand->k,
				expand->i - expand->k, environment));
	new_str = copy_join(new_str, cp_expander(command_buf + expand->k,
				expand->i - expand->k, environment), expand);
	return (new_str);
}

char	*cp_second_elif(t_expand *expand, char *command_buf, char **environment,
	char *new_str)
{
	expand->i++;
	while (command_buf[expand->i] != '\"' && command_buf[expand->i])
	{
		if (command_buf[expand->i] == '$')
			new_str = cp_find_dolar(expand, command_buf, environment, new_str);
		else
		{
			new_str[expand->n] = command_buf[expand->i];
			expand->n++;
			expand->j++;
			expand->i++;
		}
	}
	if (command_buf[expand->i])
		expand->i++;
	return (new_str);
}

char	*copy_expanded(t_expand *expand, char *command_buf, char **environment,
	char *new_str)
{
	expand->i = 0;
	while (expand->i < ft_strlen(command_buf) && command_buf[expand->i])
	{
		if (command_buf[expand->i] == '$')
			new_str = cp_find_dolar(expand, command_buf, environment, new_str);
		else if (command_buf[expand->i] == '\'')
			copy_expanded_aux(expand, command_buf, new_str);
		else if (command_buf[expand->i] == '\"')
			new_str = cp_second_elif(expand, command_buf, environment, new_str);
		else
		{
			new_str[expand->n] = command_buf[expand->i];
			expand->n++;
			expand->j++;
			if (command_buf[expand->i])
				expand->i++;
		}
	}
	return (new_str);
}

char	*malloc_expand(t_expand *expand, char *command_buf, char **environment)
{
	char	*new_str;

	expand->i = 0;
	expand->n = 0;
	new_str = (char *)ft_calloc((sizeof(char)), (expand->j + 1));
	new_str[expand->j] = '\0';
	expand->j = 0;
	new_str = copy_expanded(expand, command_buf, environment, new_str);
	free(command_buf);
	return (new_str);
}
