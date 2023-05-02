/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 01:56:46 by pepe              #+#    #+#             */
/*   Updated: 2023/05/03 01:12:48 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_PARSER_H
# define LST_PARSER_H

# include "minishell.h"

# define PIPE	"|"
# define H_DOC	"<<"
# define INPUT	"<"
# define APEND	">>"
# define TRUNC	">"

typedef struct s_redirect
{
	int					type;
	char				*file;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_info_cmd
{
	char					*cmd;
	char					**cmd_args;
	t_redirect				*re;
	//char					*out;
	struct s_info_cmd		*next;
}	t_info_cmd;

t_info_cmd	*lst_new_cmd(char *cmd, t_redirect *redir);
void		create_stack(t_info_cmd *info, char **matrix);
void		lst_create_cmd(t_info_cmd **cmd, t_info_cmd *new);
void		lst_create_redirect(t_redirect **args, t_redirect *new);
t_redirect	*lst_new_redirect(int type, char *file);
void		print_lst(t_info_cmd *list);
void		free_lst(t_info_cmd *list);
int			is_command(char *cmd, char **env);
t_info_cmd	*process_input(char **input);

#endif
