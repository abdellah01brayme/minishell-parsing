#include "../includes/parser.h"
#include "../includes/minishell.h"
#include "../includes/utils.h"

int	parse_herdoc(char *delmiter, int fd, int expand)
{
	char	*content;
	char	*input;

	input = readline(">");
	if (!input)
		return (ft_printf_fd(2, 
			"minishell: here-document delimited by EOF (wanted `%s')\n",
			delmiter), 1);
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
	if (!delmiter)
		return (1);
	return (0);
}

void	read_herdoc(char *delmiter, int fd)
{
	int		_expand;

	signal(SIGINT, SIG_DFL);
	_expand = remove_quote(delmiter);
	while (true)
		if (parse_herdoc(delmiter, fd, _expand))
			break ;
	collect_malloc(NULL, CLEAR);
	exit(EXIT_SUCCESS);
}
