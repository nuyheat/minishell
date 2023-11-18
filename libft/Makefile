NAME		= libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

AR			= ar
ARFLAGS		= rcs

INCLUDES	= ./libft.h

PART_1		= ft_isalpha.c		\
				ft_isdigit.c		\
				ft_isalnum.c		\
				ft_isascii.c		\
				ft_isprint.c		\
				ft_strlen.c			\
				ft_memset.c			\
				ft_bzero.c			\
				ft_memcpy.c			\
				ft_memmove.c		\
				ft_strlcpy.c		\
				ft_strlcat.c		\
				ft_toupper.c		\
				ft_tolower.c		\
				ft_strchr.c			\
				ft_strrchr.c		\
				ft_strncmp.c		\
				ft_memchr.c			\
				ft_memcmp.c			\
				ft_strnstr.c		\
				ft_atoi.c			\
				ft_calloc.c			\
				ft_strdup.c			\

PART_2		= ft_substr.c			\
				ft_strjoin.c		\
				ft_strtrim.c		\
				ft_split.c			\
				ft_itoa.c			\
				ft_strmapi.c		\
				ft_striteri.c		\
				ft_putchar_fd.c		\
				ft_putstr_fd.c		\
				ft_putendl_fd.c		\
				ft_putnbr_fd.c		\

BONUS		= ft_lstnew_bonus.c			\
				ft_lstadd_front_bonus.c	\
				ft_lstsize_bonus.c		\
				ft_lstlast_bonus.c		\
				ft_lstadd_back_bonus.c	\
				ft_lstdelone_bonus.c	\
				ft_lstclear_bonus.c		\
				ft_lstiter_bonus.c		\
				ft_lstmap_bonus.c		\

SRCS        = $(PART_1) $(PART_2)
OBJS        = $(SRCS:.c=.o)
OBJS_BONUS  = $(BONUS:_bonus.c=.o)

all: $(NAME)
bonus : make_bonus

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

make_bonus: $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $^
	touch $@

$(OBJS_BONUS): %.o: %_bonus.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)
	$(RM) make_bonus

re: fclean all