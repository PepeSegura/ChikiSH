/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 05:11:14 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/21 14:53:31 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_is_builtin(char *cmd)
{
	int			i;
	const char	*symbols[] = {"pwd", "env", "cd", "echo", "export",
		"unset", "exit", NULL};

	i = -1;
	if (!cmd)
		return (OTHER);
	while (symbols[++i])
		if (ft_strcmp(cmd, symbols[i]) == 0)
			return (BUILTIN);
	return (OTHER);
}
