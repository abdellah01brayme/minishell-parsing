/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:04 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 06:32:53 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/minishell.h"
#include "../includes/utils.h"

static int	remove_quote(char *str)
{
	int		count;
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	count = 0;
	while (str[i + count])
	{
		if (is_quote(str[i + count]) && quote == str[i + count])
		{
			count++;
			quote = 0;
			continue ;
		}
		else if (is_quote(str[i + count]) && !quote)
		{
			quote = str[i + count];
			count++;
			continue ;
		}
		str[i] = str[i + count];
		i++;
	}
	return (str[i] = '\0', count);
}

static int	parser_heredoc_line(char *delmiter, int fd, int expand)
{
	char	*content;
	char	*input;

	input = readline(">");
	if (!input)
	{
		ft_printf_fd(2,
			"minishell: here-document delimited by EOF (wanted `%s')\n",
			delmiter);
		return (1);
	}
	content = parser_line(input, expand);
	if (ft_strcmp(input, delmiter) == 0)
	{
		if (content != input)
			collect_malloc(content, DELETE);
		free(input);
		return (1);
	}
	write (fd, content, ft_strlen(content));
	write (fd, "\n", 1);
	if (content != input)
		collect_malloc(content, DELETE);
	free(input);
	return (0);
}

void	read_heredoc(char *delmiter, int fd)
{
	int		_expand;

	signal(SIGINT, SIG_DFL);
	_expand = remove_quote(delmiter);
	while (true)
		if (parser_heredoc_line(delmiter, fd, _expand))
			break ;
	collect_malloc(NULL, CLEAR);
	exit(EXIT_SUCCESS);
}
