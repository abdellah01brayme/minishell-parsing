/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:30 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 11:49:09 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	is_operator(char *input, int *i, int flag)
{
	static char	oper[6][3] = {"|", ">>", "<<", ">", "<"};
	static int	type[6] = {PIPE, RED_APPOUT, RED_HERDOC, RED_OUT, RED_INP};
	int			len;
	int			j;

	j = 0;
	while (j < 5)
	{
		len = ft_strlen(oper[j]);
		if (ft_strncmp(oper[j], input + *i, len) == 0)
		{
			if (flag)
				*i += len;
			return (type[j]);
		}
		j++;
	}
	return (0);
}

int	is_redirection(t_token *token)
{
	return (token->type == RED_INP || token->type == RED_OUT
		|| token->type == RED_APPOUT || token->type == RED_HERDOC);
}
