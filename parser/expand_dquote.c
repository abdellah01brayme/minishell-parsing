#include "../includes/parser.h"

static void	split_token_dquote(t_token **side_tokens, char *input)
{
	int		i;
	t_info	info;

	i = 0;
	ft_memset(&info, 0, sizeof(t_info));
	while (input[i])
	{
		if (check_for_expand(input, i))
		{
			info.end = i;
			info.type = NO_QUOTE;
			add_token(side_tokens, input, info);
			info.start = i;
			info.type = AMBIGUES;
			i = check_for_expand(input, i);
			info.end = i;
			add_token(side_tokens, input, info);
			info.start = i;
			continue ;
		}
		i++;
	}
	info.end = i;
	info.type = NO_QUOTE;
	add_token(side_tokens, input, info);
}

void	rm_quote(char *str)
{
	int		i;

	i = 0;
	while (str[i + 2])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
}

void	expand_token_dqoute(t_token *token)
{
	t_token	*side_token;
	t_token	*tmp;

	side_token = NULL;
	split_token_dquote(&side_token, token->str);
	tmp = side_token;
	while (tmp)
	{
		if (tmp->type == AMBIGUES)
			expand_token_var(tmp);
		tmp = tmp->next;
	}
	collect_malloc(token->str, DELETE);
	token->str = ft_strdup("");
	collect_malloc(token->str, CHECK);
	tmp = side_token;
	while (tmp)
	{
		token->str = ft_join1(token->str, 1, tmp->str, 1);
		tmp = tmp->next;
	}
	free_list_token(side_token);
}
 