/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:34 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 11:48:39 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/utils.h"

static int	check_close_quote(t_token *token)
{
	int		i;
	char	is_squote;
	char	is_dquote;

	if (token->type != WORD)
		return (0);
	i = 0;
	is_squote = 0;
	is_dquote = 0;
	while (token->str[i])
	{
		if (token->str[i] == '\'' && !is_dquote)
			is_squote = !is_squote;
		if (token->str[i] == '"' && !is_squote)
			is_dquote = !is_dquote;
		i++;
	}
	if (is_squote || is_dquote)
		return (1);
	return (0);
}

static void	exit_unvalid_input(char *msg)
{
	print_err_syntax(msg);
	access_exit_code(2, WRITE);
}

int	check_valid_input(t_token *token)
{
	t_token	*cur;
	t_token	*prev;

	cur = token;
	prev = token;
	if (cur->type == PIPE)
		return (exit_unvalid_input(cur->str), -1);
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		if (!cur)
			break ;
		if ((is_redirection(prev) && cur->type != WORD)
			|| (prev->type == PIPE && cur->type == PIPE))
			return (exit_unvalid_input(cur->str), 1);
	}
	if (check_close_quote(prev))
		return (exit_unvalid_input("unclosed quote"), -1);
	if (prev->type != WORD)
		return (exit_unvalid_input("newline"), 1);
	return (0);
}
