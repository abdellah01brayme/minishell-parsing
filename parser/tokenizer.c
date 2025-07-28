
# include "../includes/parser.h"

int	add_token(t_token **tokens, char *input, t_info info)
{
	t_token	*token;
	t_token	*tmp;

	if (info.end <= info.start)
		return (0);
	token = ft_calloc(1, sizeof(t_token));
	collect_malloc(token, CHECK);
	token->str = ft_substr(input, info.start, info.end - info.start);
	collect_malloc(token->str, CHECK);
	token->type = info.type;
	token->next = NULL;
	if (!(*tokens))
		*tokens = token;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
	}
	return (0);
}

static void	read_token1(char *input, t_info *info, size_t *i)
{
	info->start = *i;
	info->type = WORD;
	while (input[*i])
	{
		if (input[*i] == '\'' && !info->is_dquote)
			info->is_squote = !info->is_squote;
		else if (input[*i] == '"' && !info->is_squote)
			info->is_dquote = !info->is_dquote;
		else if (is_space(input[*i]) && !info->is_squote && !info->is_dquote)
			break ;
		else if (is_operator(input, i, 0) && info->start != *i
				&& !info->is_squote && !info->is_dquote)
			break ;
		else if (is_operator(input, i, 0)
				&& !info->is_squote && !info->is_dquote)
		{
			info->type = is_operator(input, i, 1);
			break ;
		}
		(*i)++;
	}
	info->end = *i;
}

t_token	*get_tokens(char *input)
{
	t_token	*tokens;
	t_info	info;
	size_t	i;

	i = 0;
	tokens = NULL;
	ft_memset(&info, 0, sizeof(info));
	while (input[i])
	{
		while (is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		read_token1(input, &info, &i);
		add_token(&tokens, input, info);
	}
	return (tokens);
}
