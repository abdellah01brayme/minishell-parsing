CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = src/main.c parser/tools.c parser/tokenizer.c parser/parser.c \
		parser/valide_input.c parser/set_cmd.c parser/herdoc.c\
		parser/read_herdoc.c parser/parser_herdoc.c parser/expand.c\
		parser/expand_redir.c parser/expand_dquote.c\
		utils/signal_handler.c utils/collect_malloc.c utils/print.c\
		utils/exit_status.c utils/prompt.c

OBJS = ${SRCS:%.c=%.o}

RM = rm -f

NAME = minishell

LIBFT = libft/libft.a

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C libft

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -Ilibft/libft.h libft/libft.a -lreadline -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
