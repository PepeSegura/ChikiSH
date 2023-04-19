/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:18:16 by agserran          #+#    #+#             */
/*   Updated: 2023/04/19 22:51:21 by agserran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cmd_info()
{
        t_info_cmd info;
        int         i;
        
		i = 0;
        info.cmd = g_c.tokens[0];
        while (g_c.tokens[i])
        {
            if (g_c.tokens[i][0] == '>' && g_c.tokens[i + 1])
                info.file = g_c.tokens[i + 1];
			if (g_c.tokens[i] == info.file && (token_is_symbol(g_c.tokens[i + 1]) == 0))
				info.args = g_c.tokens[i + 1];
			if(g_c.tokens[i][0] == "|")
				info.out == g_c.tokens[i];
			i++;
        }
}
