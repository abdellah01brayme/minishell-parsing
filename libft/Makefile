CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRC_FILES  = ft_atoi2.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c\
ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c ft_itoa_base.c ft_itoa.c\
ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c\
ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c\
ft_lstnew_bonus.c ft_lstsize_bonus.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c\
ft_memset.c ft_printf.c ft_putaddress.c ft_split2.c ft_putchar.c ft_putchar_fd.c ft_putendl_fd.c\
ft_putnbr_base_capital.c ft_putnbr_base_lower.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c\
ft_putstr_fd.c ft_putunsigned.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c\
ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strcmp.c ft_strncmp.c ft_strnstr.c ft_strrchr.c\
ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c handle_flags.c utils.c\

SRC_OBJS = $(SRC_FILES:.c=.o)

AR = ar rcs

RM = rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRC_OBJS)
	$(AR) $(NAME) $(SRC_OBJS)

all: $(NAME)
	
clean:
	$(RM) $(SRC_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
