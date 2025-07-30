/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:23:53 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 11:46:34 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	check_for_expand(char *input, int i)
{
	if (input[i] != '$')
		return (0);
	i++;
	if (input[i] == '?')
		return (2);
	if (!ft_isalpha(input[i]) && input[i] != '_')
		return (0);
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	return (i);
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
		read_token_token(str, &info, &i);
		add_token(&tokens, str, info);
		if (info.type == AMBIGUES)
			i = check_for_expand(str, info.start);
		else if (info.type != NO_QUOTE)
			i = info.end;
	}
	return (tokens);
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

int	check_split(t_token *token, int i)
{
	while (token->str[i] && is_space(token->str[i]))
		i++;
	while (token->str[i] && !is_space(token->str[i]))
		i++;
	if (token->str[i] && is_space(token->str[i]))
		return (1);
	return (0);
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
