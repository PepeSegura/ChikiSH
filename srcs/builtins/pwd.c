/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:02:06 by psegura-          #+#    #+#             */
/*   Updated: 2023/08/19 19:35:33 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*str_pwd;

	str_pwd = getcwd(NULL, 0);
	ft_putendl_fd(str_pwd, 1);
	free(str_pwd);
	if (g_c.tok_count > 1)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
