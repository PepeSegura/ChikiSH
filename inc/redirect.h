/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:14:42 by agserran          #+#    #+#             */
/*   Updated: 2023/04/19 14:22:13 by agserran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

typedef struct s_info_cmd
{
    char    *cmd;
    char    *args;
    char    *file;
    char    *out;
    void    *next;
}   t_info_cmd;


#endif