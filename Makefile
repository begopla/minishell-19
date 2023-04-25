# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 17:47:42 by bpla-rub          #+#    #+#              #
#    Updated: 2023/04/24 15:30:37 by bpla-rub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME		=	minishell

LIBFT_DIR	=	libft
LIBFT		=	libft.a
RL_INC		=	-I /usr/local/opt/readline/include
RL_LINK		=	-L /usr/local/opt/readline/lib -l readline

INC_DIR		=	include
SRC_DIR		=	src
OBJ_DIR		=	objects

SRCS		=	src/main.c			    \
				src/env.c 				\
				src/shell.c		 		\
				src/free.c	    		\
				src/free2.c	    		\
				src/prompt.c			\
				src/shell_utils.c		\
				src/utils.c				\
				src/builtin.c			\
				builtin/ft_getenv.c		\
				builtin/cd.c			\
				builtin/echo.c			\
				builtin/env.c			\
				builtin/export.c		\
				builtin/ft_putenv.c		\
				builtin/pwd.c			\
				builtin/unset.c			\
				builtin/builtin_utils.c	\
				builtin/builtin_utils2.c	\
				builtin/builtin_utils3.c	\
				builtin/exit.c 			\
				parse/parser_utils.c    \
				parse/parse_steps.c		\
				parse/parse_execution.c \
				tokens/tokens.c		    \
				tokens/check_env.c	    \
				tokens/tokens_env.c		\
				tokens/tokens_utils.c   \
				tokens/tokens_utils2.c  \
				tokens/tokens_types.c   \
				tokens/tokens_nested.c  \
				tokens/expand_env.c 	\
				tokens/tokens_normal.c	\
				tokens/trim_quotes.c	\
				execution/check_redirec.c \
				execution/cmd_check.c \
				execution/dup.c \
				execution/error_check.c \
				execution/error_mssg.c \
				execution/exec.c \
				execution/exec1.c \
				execution/executils.c \
				execution/get_exit.c \
				execution/handle_invalid.c \
				execution/heredoc.c \
				execution/other_cmd.c \
				execution/redirec.c \
				execution/run_builtin.c \
				execution/run_cmd.c \
				execution/set_cmd_path.c \
				execution/signal.c \
				execution/signal_functions.c \
				execution/steps.c \
				execution/subexpr.c \
				execution/get_next_line.c \
				execution/run_heredoc.c \
				data_ex.c
				

OBJS		=	$(SRCS:%c=%o)

CC			=	gcc
#CFLAGS		=	-g -Wall -Wextra -Werror
CFLAGS		=	-g -Wall -Wextra -Werror #-fsanitize=address
RM			=	rm -rf

all:		$(NAME)
	@echo 🔥🔥minishell🔥🔥
	
%.o : %.c
# @mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) $(RL_INC) -c $< -o $@

$(NAME):	$(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(RL_LINK) -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) all
	@make -C $(LIBFT_DIR) bonus

leaks:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=./readline.supp ./minishell \
	
# --track-origins=yes --show-leak-kinds=all 

clean:
		@make -C $(LIBFT_DIR) fclean
	$(RM) ./*/*.o
	@$(RM) $(OBJ_DIR)

fclean:		clean
	@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
