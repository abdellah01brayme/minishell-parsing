/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:22:48 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 09:30:05 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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

typedef enum s_enum_buil
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
	int	start;
	int	end;
	char	is_squote;
	char	is_dquote;
}	t_info;

typedef struct s_token
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

////////////// tools.c
int		is_quote(char c);
int		is_space(char c);
int		is_operator(char *input, int *i, int flag);
int		is_redirection(t_token *token);

////////////// tokenizer.c
t_token	*get_tokens(char *input);
int		add_token(t_token **tokens, char *input, t_info info);
void	read_token_token(char *input, t_info *info, int *i);
void	split_token_dquote(t_token **side_tokens, char *input);

////////////// parser.c
t_list	*parser(char *input);
void	free_list_token(t_token *token);

////////////// valid_input.c
int		check_valid_input(t_token *token);

////////////// set_commands.c
t_list	*set_cmd(t_token *token);

////////////// expand*.c
int		expand(t_list *cmd);
void	split_after_expand(t_token *tokens);
int		check_split(t_token *token, int i);
int		split_new_token(char *token);
t_token	*split_token(char *str);
int		check_for_expand(char *input, int i);
void	expand_tokens(t_token *tokens);
void	expand_token_dqoute(t_token *token);
void	expand_token_var(t_token *token);
t_token	*new_tokens_expanded(t_token *token);
t_list	*join_tokens_args(t_list **arg, t_token *tokens);
void	join_tokens_redir(t_redir *redir, t_token *tokens);
t_token	*prepar_args(t_list	**arg, t_token *tokens);
int		check_last_token_unexpanded(t_token *tokens);

////////////// heredoc*.c
t_list	*parser(char *input);
void	free_list_token(t_token *token);
void	read_heredoc(char *delmiter, int fd);
int		parser_heredoc(char *delim);
char	*ft_join(char *str1, int free1, char *str2, int free2);
char	*parser_line(char *input, int _expand);


int	check_valid_variable(char *str); /// add to builtins header
#endif
