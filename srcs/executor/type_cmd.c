/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 05:11:14 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/17 11:04:30 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_is_builtin(char *cmd)
{
	int			i;
	int			type;
	const char	*symbols[] = {"pwd", "env", "cd", "echo", "export",
		"unset", "exit", NULL};

	type = OTHER;
	i = -1;
	while (symbols[++i])
		if (ft_strcmp(cmd, symbols[i]) == 0)
			type = BUILTIN;
	return (type);
}
