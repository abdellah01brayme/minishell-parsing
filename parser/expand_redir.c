#include "../includes/parser.h"

void	read_token2(char *input, t_info *info, int *i)
{
	info->start = *i;
	if (input[*i] == '\'')
		info->end = ft_strchr(input + *i + 1, '\'') - input + 1;
	else if (input[*i] == '"')
		info->end = ft_strchr(input + *i + 1, '"') - input + 1;
	else if (check_for_expand(input, *i))
		info->end = check_for_expand(input, *i);
	else
	{
		while (input[*i] && !check_for_expand(input, *i) && input[*i] != '\''
				&& input[*i] != '"')
			(*i)++;
		info->end = *i;
	}
	info->type = NO_QUOTE;
	if (input[info->start] == '\'')
		info->type = S_QUOTE;
	else if (input[info->start] == '"')
		info->type = D_QUOTE;
	else if (check_for_expand(input, info->start))
		info->type = AMBIGUES;
}

void	print_tokens(t_token *tmp)
{
	printf("||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	while (tmp)
	{
		printf("|%s\t\t\t\t\t%d\t\t|\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
	printf("||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
}


t_token	*split_token(char *str)
{
	int		i;
	t_token	*tokens;
	t_info	info;

	tokens = NULL;
	i = 0;
	while (str[i])
	{
		read_token2(str, &info, &i);
		add_token(&tokens, str, info);
		if (info.type == AMBIGUES)
			i = check_for_expand(str, info.start);
		else if (info.type != NO_QUOTE)
			i = info.end;
	}
	return (tokens);
}

void	expand_token_var(t_token *token)
{
	char	*var;

	var = getenv(token->str + 1);
	if (!var)
	{
		// var = "";
		collect_malloc(token->str, DELETE);
		token->str = NULL;
		return ;
	}
	var = ft_strdup(var);
	collect_malloc(token->str, DELETE);
	collect_malloc(var, CHECK);
	token->str = var;
}

int	check_last_token_unexpanded(t_token *tokens)
{
	int	i;

	while (tokens->next)
		tokens = tokens->next;
	i = 0;
	if (tokens->type == AMBIGUES || tokens->type == D_QUOTE
		|| tokens->type == S_QUOTE)
		return (1);
	while (tokens->str && tokens->str[i])
	{
		if (tokens->str[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

void	expand_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type != NO_QUOTE && tmp->type != S_QUOTE)
		{
			if (tmp->type == D_QUOTE)
				expand_token_dqoute(tmp);
			else if (tmp->type == AMBIGUES)
				expand_token_var(tmp);
		}
		if (tmp->type == D_QUOTE || tmp->type == S_QUOTE)
			rm_quote(tmp->str);
		tmp = tmp->next;
	}
}

int	split_new_token(char *token)
{
	t_info	info;
	int		i;

	i = 0;
	ft_memset(&info, 0, sizeof(t_info));
	while (token[i])
	{
		if (token[i] == '"')
			info.is_dquote = !info.is_dquote;
		else if (is_space(token[i]) && !info.is_dquote)
		{
			while (is_space(token[i]))
				i++;
			if (token[i])
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int	ambiguous(t_redir *redir, t_token *token)
{
	while (token)
	{
		if (token->type == SPLIT || !token->str)
		{
			redir->type = AMBIGUES;
			return (1);
		}
		token = token->next;
	}
	return (0);
}

void	join_tokens_redir(t_redir *redir, t_token *tokens)
{
	char	*new_token;
	t_token	*tmp;

	tmp = tokens;
	if (ambiguous(redir, tokens))
		return ;
	new_token = ft_strdup("");
	collect_malloc(new_token, CHECK);
	while (tmp)
	{
		new_token = ft_join1(new_token, 1, tmp->str, 1);
		tmp = tmp->next;
	}
	collect_malloc(redir->file, DELETE);
	redir->file = new_token;
}

int	check_split(t_token *token, int i)
{
	int	split;

	split = 0;
	if (is_space(token->str[i]))
		split = 1;
	while (token->str[i] && is_space(token->str[i]))
		i++;
	while (token->str[i] && !is_space(token->str[i]))
		i++;
	if (token->str[i] && is_space(token->str[i]))
		split = 1;
	if (!token->str[i] && token->next && !is_space(token->next->str[0]))
		split = 0;
	return (split);
}

t_token	*new_tokens_expanded(t_token *token)
{
	t_token	*token_split;
	t_info	info;
	int		i;

	i = 0;
	token_split = NULL;
	ft_memset(&info, 0, sizeof(t_info));
	while (token && token->str && token->str[i])
	{
		info.type = JOIN;
		if (check_split(token, i))
			info.type = SPLIT;
		while (is_space(token->str[i]))
			i++;
		info.start = i;
		while (token->str[i] && !is_space(token->str[i]))
			i++;
		info.end = i;
		printf("%s <==> split :%d != %d\n", token->str + info.start, info.type, SPLIT);
		add_token(&token_split, token->str, info);
	}
	if (!token_split)
		return (token_split = ft_calloc(1, sizeof(t_token)), 
				collect_malloc(token_split, CHECK), token_split);
	return (token_split);
}

void	split_after_expand(t_token *tokens)
{
	t_token	*tmp;
	t_token	*tmp2;
	t_token	*news;
	int		split;

	tmp = tokens;
	while (tmp)
	{
		split = check_last_token_unexpanded(tmp);
		if (tmp->type == AMBIGUES && split)
		{
			news = new_tokens_expanded(tmp);
			collect_malloc(tmp->str, DELETE);
			tmp->str = news->str;
			tmp->type = news->type;
			tmp2 = tmp->next;
			tmp->next = news->next;
			collect_malloc(news, DELETE);
			while (tmp && tmp->next)
				tmp = tmp->next;
			tmp->next = tmp2;
		}
		tmp = tmp->next;
	}
}

int	expand_redir(t_list *list_redir)
{
	t_list	*tmp;
	t_redir	*redir;
	t_token	*tokens;

	tmp = list_redir;
	tokens = NULL;
	while (tmp)
	{
		redir = (t_redir *)tmp->content;
		if (redir->type == RED_HERDOC)
		{
			redir->heredoc_fd = parser_heredoc(redir->file);
			tmp = tmp->next;
			continue ;
		}
		tokens = split_token(redir->file);
		expand_tokens(tokens);
		split_after_expand(tokens);
		join_tokens_redir(redir, tokens);
		free_list_token(tokens);
		tmp = tmp->next;
	}
	return (0);
} 
