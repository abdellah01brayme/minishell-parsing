/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:15 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 11:46:48 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

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

static void	read_token_input(char *input, t_info *info, int *i)
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

void	split_token_dquote(t_token **side_tokens, char *input)
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

void	read_token_token(char *input, t_info *info, int *i)
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

t_token	*get_tokens(char *input)
{
	t_token	*tokens;
	t_info	info;
	int		i;

	i = 0;
	tokens = NULL;
	ft_memset(&info, 0, sizeof(info));
	while (input[i])
	{
		while (is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		read_token_input(input, &info, &i);
		add_token(&tokens, input, info);
	}
	return (tokens);
}
