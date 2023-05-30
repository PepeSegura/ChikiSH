# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 16:12:27 by psegura-          #+#    #+#              #
#    Updated: 2023/05/26 18:18:15 by psegura-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### Colors ###

#RESET	=	\033c
GREEN	=	\033[1;32m
RED		=	\033[0;31m
CYAN	=	\033[0;36m
WHITE	=	\033[0m

NAME = minishell

SRCS =											\
		srcs/main.c								\
												\
		srcs/intro/intro.c						\
												\
		srcs/readline/readline.c				\
												\
		srcs/tokenizer/store_tokens.c			\
		srcs/tokenizer/store_tokens_utils.c		\
		srcs/tokenizer/tokens_to_pipas.c		\
		srcs/tokenizer/utils.c					\
		srcs/tokenizer/expand_token.c			\
		srcs/tokenizer/malloc_expand_token.c	\
		srcs/tokenizer/malloc_expand_token_aux.c\
		srcs/tokenizer/copy_join.c 				\
												\
		srcs/executor/locate_cmd.c				\
		srcs/executor/exec_cmd.c				\
		srcs/executor/type_cmd.c				\
		srcs/executor/manager_cmd.c				\
		srcs/executor/utils_cmd.c				\
												\
		srcs/utils/errors.c						\
		srcs/utils/environment.c				\
												\
		srcs/builtins/builtins.c				\
		srcs/builtins/cd.c						\
		srcs/builtins/echo.c					\
		srcs/builtins/env.c						\
		srcs/builtins/exit.c					\
		srcs/builtins/export.c					\
		srcs/builtins/pwd.c						\
		srcs/builtins/unset.c					\
		srcs/builtins/signals.c					\
												\
		srcs/lst_parser/cmd_lst.c				\
		srcs/lst_parser/free_lst.c				\
		srcs/lst_parser/parser_lst.c			\
		srcs/lst_parser/print_lst.c				\
		srcs/lst_parser/redir_lst.c				\
		srcs/lst_parser/utils_lst.c				\
												\
		srcs/redirections/redirect.c			\
		srcs/redirections/here_doc.c			\
												\

OBJS = $(SRCS:%.c=objs/%.o)

LIB = libft/libft.a

CC = gcc

# MAKEFLAGS += -j6

CFLAGS	 =	-Wall -Wextra -Werror -g3 -fsanitize=address,leak
CFLAGS	+=	-I inc
CFLAGS	+=	-I libft
READLINE =	-lreadline -L /Users/$(USER)/.brew/opt/readline/lib	\
			-I /Users/$(USER)/.brew/opt/readline/include

date := $(shell date +"%a %b %_d %H:%M")

$(NAME): objs $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) $(READLINE) -o $(NAME)
	@echo -e "$(CYAN) MINISHELL RIDERS GOING AFTER YOU $(WHITE)"

objs:
	@mkdir -p	objs/srcs/intro objs/srcs/readline objs/srcs/tokenizer	\
				objs/srcs/executor objs/srcs/utils objs/srcs/builtins	\
				objs/srcs/lst_parser objs/srcs/redirections				\

objs/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@make clean -C libft
	@rm -rf objs

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

norma:
	@echo 6e6f726d696e65747465207372637320696e6320313e2f6465762f6e756c6c3b206966205b5b20243f202d65712030205d5d3b207468656e206e6f726d696e65747465207372637320696e633b20656c7365206e6f726d696e65747465207372637320696e63207c206772657020274572726f7227203b206669 | xxd -r -p | zsh

commit: fclean
	@git add .
	@./input.sh
	@INPUT_VAR=$$(cat input.txt) && git commit -m "$(date):  $$INPUT_VAR" && rm -f input.txt
	@git push

.PHONY: all clean fclean re norma commit
