/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:23:43 by agserran          #+#    #+#             */
/*   Updated: 2023/05/10 01:10:50 by agserran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    open_redirect(t_info_cmd *info)
{
    int fd[2];

    fd[0] = 0; 
    fd[1] = 0;
     while (info->re)
     {
        if (info->re->type == 2 || info->re->type == 3)
        {
            if (info->re->type == 2)
                fd[1] = open(info->re->file, O_CREAT | O_TRUNC, 0644);
            if (info->re->type == 3)
                fd[1] = open(info->re->file, O_CREAT | O_APPEND, 0644);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
        }
        if (info->re->type == 1 ||info->re->type == 3)
        {
            fd[0] = open(info->re->file, O_RDONLY);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
        }
        info->re = info->re->next;
     }
}
