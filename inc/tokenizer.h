/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:22:05 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/07 04:55:00 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

typedef struct s_quotes {
	int	s_count;
	int	d_count;
	int	i;
}	t_quotes;

typedef struct s_count {
	int		i;
	int		j;
	int		k;
}	t_count;

typedef struct s_expand {
	int		i;
	int		j;
	int		k;
	int		l;
	int		m;
	int		n;
	int		flag;
	char	*expanded;
	char	*post_expanded;
	char	*final;
	char	*dolar;
}	t_expand;

char	*copy_join(char *str1, char *str2, t_expand *expand);
char	*expan_token(char *command_buf, char **environment);
char	*expander(char *post_dolar, int i, char **environment);
char	*malloc_expand(t_expand *expand, char *command_buf, char **environment);

/*__MALLOC_EXPAND_TOKENS_AUX__*/
char	*cp_expander(char *post_dolar, int i, char **environment);
void	copy_expanded_aux(t_expand *expand, char *command_buf, char *new_str);
void	cp_find_dolar_aux(t_expand *expand, char *command_buf, char *new_str);

/*__STORE_TOKENS_UTILS____*/
int		count_tokens(char *str);
void	main_while(const char *str, t_count *c);
int		char_is_symbol(char letter, char *symbols);
void	find_next_quote(const char *str, int *i, char quote);
void	if_char_is_symbol(const char *str, t_count *c, int *len);

/*__STORE_TOKENS____*/
void	store_tokens(const char *str, char **tokens);

/*__UTILS____*/
int		check_quotes(const char *readline);

/*__LOCATE_SYMBOLS____*/
void	find_next_quote(const char *str, int *i, char quote);
void	store_tokens(const char *str, char **tokens);

/*__TOKENS_TO_PIPAS____*/
int		count_pipas(char **tokens);
int		double_symbols(char **tokens);
char	**tokens_to_pipas(char **tokens);
int		token_is_symbol(char *token);
int		token_is_pipe(char *token);

#endif
