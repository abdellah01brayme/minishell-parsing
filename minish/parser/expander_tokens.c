/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:23:50 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 11:46:05 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static void	rm_quote(char *str)
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
		add_token(&token_split, token->str, info);
	}
	if (!token_split)
		return (token_split = ft_calloc(1, sizeof(t_token)),
			collect_malloc(token_split, CHECK), token_split);
	return (token_split);
}

void	expand_token_var(t_token *token)
{
	char	*var;

	if (token->str[1] == '?')
	{
		var = ft_itoa(access_exit_code(0, READ));
		collect_malloc(var, CHECK);
	}
	else
		var = getenv(token->str + 1);
	if (!var)
	{
		collect_malloc(token->str, DELETE);
		token->str = NULL;
		return ;
	}
	var = ft_strdup(var);
	collect_malloc(token->str, DELETE);
	collect_malloc(var, CHECK);
	token->str = var;
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
		token->str = ft_join(token->str, 1, tmp->str, 1);
		tmp = tmp->next;
	}
	free_list_token(side_token);
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
