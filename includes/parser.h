#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../libft/libft.h"
# include "utils.h"
# include <dirent.h>
# include <wait.h>
# include <stdio.h> /////////////////del
typedef enum s_enum
{
	WORD = 1,
	PIPE,
	RED_OUT,
	RED_INP,
	RED_APPOUT,
	RED_HERDOC,
	AMBIGUES,
	S_QUOTE,
	D_QUOTE,
	NO_QUOTE,
	SPLIT,
	JOIN
}	t_enum;

typedef enum
{
	NOT,
	CD,
	ECHO,
	EXIT,
	PWD,
	ENV,
	EXPORT,
	UNSET
}	t_builtins;

typedef struct s_info
{
	char	type;
	size_t	start;
	size_t	end;
	char	is_squote;
	char	is_dquote;
}	t_info;

typedef	struct s_token
{
	char			*str;
	char			type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int		type;
	char	*file;
	int		heredoc_fd;
}	t_redir;

typedef struct s_cmd
{
	int		is_builtin;
	t_list	*args;
	t_list	*redir;
}	t_cmd;

typedef struct s_expand
{
	char			*buf;
	size_t			start;
	size_t			end;
	char			*born_buf;
	struct s_expand *next;
}	t_expand;



int		is_quote(char c);
int		is_space(char c);
int		is_operator(char *input, size_t *i, int flag);

////////////// tokenizer.c
t_token	*get_tokens(char *input);
int		add_token(t_token **tokens, char *input, t_info info);

////////////// parser.c
t_list	*parser(char *input);
int		check_for_expand(char *input, int i);
void 	free_list_token(t_token *token);

////////////// valide_input.c
int		check_valide_input(t_token *token);

////////////// tolls.c
int		is_redirection(t_token *token);
int		remove_quote(char *str);

////////////// set_cmd.c
t_list	*set_cmd(t_token *token);
void	add_to_args(t_list **args, t_token *token);
int 	is_builtin(char *cmd);

////////////// expand*.c
int		expand(t_list *cmd);
int		expand_args(t_list *args);
int		expand_redir(t_list *redir);

////////////// expand_redir.c
void	expand_token_var(t_token *token);

///////////// herdorc.c
int		parser_heredoc(char *delim);
///////////// read_herdoc.c
void	read_herdoc(char *delmiter, int fd);
///////////// parser_herdoc.c
char	*parser_line(char *input, int _expand);



void	join_tokens_redir(t_redir *redir, t_token *tokens);
int		split_new_token(char *token);
void	expand_tokens(t_token *tokens);
int		check_last_token_unexpanded(t_token *tokens);
void	rm_quote(char *str);
void	expand_token_var(t_token *token);
t_token	*split_token(char *str);
void	read_token2(char *input, t_info *info, int *i);
void	expand_token_dqoute(t_token *token);
char	*ft_join1(char *str1, int free1, char *str2, int free2);
void	split_after_expand(t_token *tokens);
t_token	*new_tokens_expanded(t_token *token);






void	print_tokens(t_token *tmp);
#endif
