/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:25:30 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/10 17:57:30 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

# define SPACE		' '
# define NONE		42
# define BUILTIN	1
# define STDLIB		2
# define OTHER		0

# define RIGHT 0
# define LEFT 1

/*___EXEC_CMD___*/
void	ft_exec(char **cmd);

/*___LOCATE_CMD___*/
char	*check_path(char *cmd);
char	*only_path(char *cmd);
void	cmd_not_found(char *cmd);
void	exit_failure(char *err_msg, char **to_free, int flag);

/*___MANAGER_CMD___*/
void	pipex(t_info_cmd *info);

/*___TYPE_CMD___*/
int		cmd_is_builtin(char *cmd);
int		what_cmd(char *argv);

/*___UTILS_CMD___*/
pid_t	create_fork(void);
void	create_pipe(void);
void	wait_child(void);
void	open_redirect(t_info_cmd *info, t_last_red *last);

#endif
