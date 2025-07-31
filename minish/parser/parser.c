/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:09 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/31 06:50:31 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	free_list_token(t_token *token)
{
	t_token	*t;

	while (token)
	{
		t = token->next;
		if (token)
			collect_malloc(token, DELETE);
		token = t;
	}
}

static void	run_heredoc(t_token *tokens, int valid)
{
	t_token	*prev;

	if (valid < 0)
		return ;
	while (tokens)
	{
		prev = tokens;
		tokens = tokens->next;
		if (!tokens)
			break ;
		if ((is_redirection(prev) && tokens->type != WORD)
			|| (prev->type == PIPE && tokens->type == PIPE))
			break ;
		if (prev->type == RED_HERDOC && tokens->str)
			close(parser_heredoc(tokens->str));
	}
}

t_list	*parser(char *input)
{
	t_token	*token;
	t_list	*cmd;
	int		valid;

	token = get_tokens(input);
	if (!token)
		return (NULL);
	valid = check_valid_input(token);
	if (valid)
		return (run_heredoc(token, valid), NULL);
	cmd = set_cmd(token);
	if (!cmd)
		return (NULL);
	free_list_token(token);
	expand(cmd);
	return (cmd);
}
