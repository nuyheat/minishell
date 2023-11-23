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

SRCS		= minishell.c				\
				utils/all_utils.c		\
				utils/list_handling.c   \
				parse/parse.c			\
				parse/token_handling.c	\
				parse/token_flgs.c		\
				parse/token_utils.c		\
				parse/token_rules.c		\
				parse/my_strtrim.c		\

SRCS_BONUS	= minishell_bonus.c	\

OBJS        = $(SRCS:.c=.o)
OBJS_BONUS  = $(SRCS_BONUS:.c=.o)

ILKO_FLAG = ${-g3 -fsanitize=address}

all: pre_make $(NAME)
bonus : pre_make $(NAME_BONUS)

$(NAME): $(MINISHELL)
	$(CC) $(CFLAGS) $(LINKS_LIBRARY)  -lreadline $^ -o $@ -g

$(MINISHELL): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES_HEADER) -c $^ -o $@ -g

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
