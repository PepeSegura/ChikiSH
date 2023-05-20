/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:41:16 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/17 21:22:22 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*__HEADER FILES__*/
# include "libs.h"

/*__READLINE______*/
# include "readline.h"

/*__TOKENIZER_____*/
# include "tokenizer.h"

/*__LST_PARSER_____*/
# include "lst_parser.h"

/*__INTRO_________*/
# include "intro.h"

/*__EXECUTOR______*/
# include "executor.h"

/*__BUILTINS______*/
# include "builtins.h"

/*__UTILS_________*/
# include "utils.h"

/*__ERROR_MESSAGES_________*/
# include "error_messages.h"

/*__REDIRECTIONS_________*/
# include "redirections.h"

/*__LIBFT_________*/
# include "../libft/inc/libft.h"

typedef struct s_cosas {
	char	**env;
	char	**tokens;
	int		tok_count;
	int		flag;
	int		dolar_q;
	int		fd[2];
	int		redirection_out;
	int		redirection_in;
	int		read;
	int		pipa[2];
	int		prev;
	pid_t	last_pid;
	int		status;
}	t_cosas;

extern t_cosas		g_c;

#endif
