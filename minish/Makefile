CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = src/main.c parser/expander.c parser/expander_join_tokens.c parser/expander_tokens.c \
	parser/expander_tools.c parser/heredoc.c parser/heredoc_parser.c parser/heredoc_read.c \
	parser/parser.c parser/set_commands.c parser/tokenizer.c parser/tools.c parser/valid_input.c\
	utils/collect_malloc.c\
	utils/exit_status.c utils/printer.c utils/prompt.c utils/signal_handler.c


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
