/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:03:40 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/21 16:43:54 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		builtins(char **commands);
void	builtin_with_redirect(t_info_cmd *info);

/*__SIGNALS___*/
void	manage_signal(void);
void	signal_heredoc(void);
void	signal_child(void);
void	signal_ignore(void);
void	manage_signal(void);

/*__PWD_____*/
int		ft_pwd(char **commands);

/*__ENV_____*/
int		ft_env(char **env);

/*__CD______*/
int		ft_cd(char **env, char **commands);

/*__ECHO____*/
int		ft_echo(char **commands);

/*__EXPORT__*/
int		ft_export(char **args);

/*__UNSET___*/
int		ft_unset(char **args);

/*__EXIT____*/
int		ft_exit(char **args);

#endif
