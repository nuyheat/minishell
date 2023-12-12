NAME		= minishell
NAME_BONUS	= minishell_bonus

CC			= cc
CFLAGS		=
RM			= rm -f
AR			= ar
ARFLAGS		= rcs

INCLUDES_HEADER = -I$(LIBFT_DIR) -I header
LINKS_LIBRARY    = -L$(LIBFT_DIR) -lft

LIBFT_DIR		 = ./libft
MINISHELL		 = minishell.a
MINISHELL_BONUS	 = minishell_bonus.a

SRCS		= minishell.c \
				utils/all_utils.c utils/list_handling.c utils/main_utils.c utils/ft_line_creat.c \
				builtins/builtins_utils.c builtins/built_cd.c builtins/built_echo.c \
				builtins/built_export.c builtins/built_pwd.c builtins/built_export_utils.c \
				builtins/built_unset.c builtins/built_unset_utils.c \
				builtins/built_env.c builtins/built_exit.c \
				parse/parse.c parse/parse_utils.c \
				parse/tokenize/token_handling.c parse/tokenize/token_flgs.c	\
				parse/tokenize/token_utils.c parse/tokenize/token_rules.c	\
				parse/translate/trans_utils.c parse/translate/trans_handling.c \
				parse/translate/ft_expansion_token_split.c \
				parse/translate/ft_expansion_dollar_convert.c \
				parse/translate/ft_expansion_token_merge.c \
				execute/execute.c \
				execute/execute_utils/args_utils.c \
				execute/execute_utils/builtin_utils.c \
				execute/execute_utils/ft_redirection_handling.c \
				execute/execute_utils/redirection_utils.c \
				execute/execute_utils/pipe_utils.c \
				execute/execute_utils/here_doc_utils.c \
				execute/execute_utils/path_utils.c \
				execute/parent/ft_command_error.c \
				execute/parent/ft_redirection_error.c \
				execute/parent/ft_syntax_error.c \
				execute/parent/parent_utils.c \
				execute/child/ft_child.c \
				execute/child/ft_simple_command.c \
				execute/child/child_utils.c \
				signal/signal.c \
				signal/terminal.c \

SRCS_BONUS	= minishell_bonus.c	\

OBJS        = $(SRCS:.c=.o)
OBJS_BONUS  = $(SRCS_BONUS:.c=.o)

ILKO_FLAG = -fsanitize=address

all: pre_make $(NAME)
bonus : pre_make $(NAME_BONUS)

$(NAME): $(MINISHELL)
	$(CC) $(CFLAGS) $(LINKS_LIBRARY) -fsanitize=address -lreadline $^ -o $@ -g

$(MINISHELL): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -fsanitize=address $(INCLUDES_HEADER) -c $^ -o $@ -g

$(NAME_BONUS): $(MINISHELL_BONUS)
	$(CC) $(CFLAGS) $(LINKS_LIBRARY) -lreadline $^ -o $@

$(MINISHELL_BONUS): $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $@ $^

clean: pre_clean
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(RM) $(MINISHELL)
	$(RM) $(MINISHELL_BONUS)

fclean: clean pre_fclean
	$(RM) $(NAME_BONUS)
	$(RM) $(NAME)

re: fclean all

pre_make:
	make -C $(LIBFT_DIR)

pre_clean:
	make clean -C $(LIBFT_DIR)

pre_fclean:
	make fclean -C $(LIBFT_DIR)
