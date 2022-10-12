# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/09 01:54:24 by ahakam            #+#    #+#              #
#    Updated: 2022/09/16 08:26:18 by ahakam           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC= gcc

CFLAGS = -Wall -Werror -Wextra

USER = ahakam

INCLUDES =  -lreadline -L /Users/${USER}/.brew/opt/readline/lib -I /Users/${USER}/.brew/opt/readline/include
	
SRC = builtin/ft_atoi.c builtin/ft_strcmp_bonus.c parse_redirs.c ft_isalnum.c\
	  builtin/ft_strdup.c calloc.c builtin/ft_lstadd_back_bonus.c ft_strjoin2.c\
	  lexer.c quotes.c builtin/cd.c builtin/ft_lstadd_front_bonus.c\
	   lexer_parse_utils.c runcmd.c data.c\
	  builtin/ft_lstdelone_bonus.c builtin/ft_strncmp.c minishell.c\
	  runcmd_utils.c builtin/echo.c builtin/ft_lstnew_bonus.c builtin/ft_strnstr.c\
	  builtin/unset.c builtin/env.c ft_strrchr.c display_utils.c builtin/exit.c\
	  get_next_line/ft_substr.c parse_exec.c utils_redir.c builtin/pwd.c\
	  builtin/export.c builtin/ft_split.c get_next_line/get_next_line.c parse_pipe.c\
	  dollar.c signals.c ft_itoa.c verify_input.c sig_handle.c\
	  check_errors.c  builtin/export_utils.c if_builtin.c exec.c\
	  destructor.c here_doc.c quotes_dollar.c

all : $(NAME)

$(NAME) : $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INCLUDES) -o $(NAME)

clean :
	rm -rf $(NAME)

fclean : clean

re : fclean all
