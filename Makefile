# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 16:58:29 by aaoutem-          #+#    #+#              #
#    Updated: 2023/08/10 23:40:30 by aaoutem-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -g #-fsanitize=address #-Werror  -g3

HEADER = minishell.h

L = -L$(HOME)/.brew/opt/readline/lib
I = -I$(HOME)/.brew/opt/readline/include

SRC = minishell.c \
		init.c \
		signal.c \
		free_mem.c \
		execution/her_doc.c \
		execution/multi_cmds.c \
		execution/Builtins/builtin_utils.c \
		execution/Builtins/cd.c \
		execution/uno_cmd_exec.c \
		execution/builtin_exec.c \
		execution/Builtins/env.c \
		execution/redirections.c \
		execution/Builtins/exit.c \
		execution/Builtins/echo.c \
		execution/Builtins/export.c \
		execution/Builtins/pwd.c \
		execution/Builtins/unset.c \
		execution/heredoc_utils.c \
		utils/lexer/fix_index.c \
		utils/lexer/expand.c \
		utils/lexer/merge_words.c \
		utils/lexer/process_right_redirection.c \
		utils/lexer/ft_init_vars.c \
		utils/lexer/lexer.c \
		utils/lexer/pop_node.c \
		utils/lexer/process_single_quote.c \
		utils/lexer/process_double_quote.c \
		utils/lexer/lexer_last.c \
		utils/lexer/process_var.c \
		utils/lexer/process_word.c \
		utils/lexer/lexer_add_back.c \
		utils/lexer/process_left_redirection.c \
		utils/lexer/lexer_new.c \
		utils/lexer/process_pipe.c \
		utils/minishell_gears/cmd_inlexer_toarray.c \
		utils/minishell_gears/ft_itoa.c \
		utils/minishell_gears/ft_atoi.c \
		utils/minishell_gears/ft_lstadd_back.c \
		utils/minishell_gears/error.c \
		utils/minishell_gears/ft_bzero.c \
		utils/minishell_gears/ft_split.c \
		utils/minishell_gears/ft_close.c \
		utils/minishell_gears/ft_dup2.c \
		utils/minishell_gears/ft_strcmp.c \
		utils/minishell_gears/ft_strchr.c \
		utils/minishell_gears/ft_malloc.c \
		utils/minishell_gears/ft_memcpy.c \
		utils/minishell_gears/ft_memset.c \
		utils/minishell_gears/ft_substr.c \
		utils/minishell_gears/ft_strdup.c \
		utils/minishell_gears/ft_strncmp.c \
		utils/minishell_gears/get_newenv.c \
		utils/minishell_gears/ft_lstsize.c \
		utils/minishell_gears/get_envvar.c \
		utils/minishell_gears/ft_isdigit.c \
		utils/minishell_gears/ft_putstr_fd.c \
		utils/minishell_gears/max.c \
		utils/minishell_gears/ft_strjoin.c \
		utils/minishell_gears/ft_isalnum.c \
		utils/minishell_gears/ft_isalpha.c \
		utils/minishell_gears/sdup.c \
		utils/minishell_gears/ft_calloc.c \
		utils/minishell_gears/ft_open.c \
		utils/minishell_gears/ft_strlen.c \
		utils/minishell_gears/env_utils/env_lst_to_array.c \
		utils/minishell_gears/env_utils/ft_envadd_front.c \
		utils/minishell_gears/env_utils/ft_envsize.c \
		utils/minishell_gears/env_utils/ft_envadd_back.c \
		utils/minishell_gears/env_utils/set_env.c \
		utils/minishell_gears/exec_utils/ft_pipe.c \
		utils/minishell_gears/exec_utils/ft_fork.c \
		utils/minishell_gears/exec_utils/get_abs_cmd.c \
		utils/minishell_gears/exec_utils/is_directory.c \
		utils/minishell_gears/env_utils/ft_envnew.c \
		utils/parser/parser.c \
		utils/parser/split_cmds.c \
		utils/parser/syntaxe_error.c



OBJ_F = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ_F) $(HEADER)
	@$(CC) $(CFLAGS) $(I) $(L) $(OBJ_F) -lreadline -o $(NAME)


%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(I) -c  $< -o $@

clean:
	@echo "\033[1;31mCleaning"
	@$(RM) $(OBJ_F)

fclean: clean
	@echo "\033[1;31mClean it all!"
	@$(RM)  $(NAME)

re: fclean all

.PHONY: all clean fclean re
