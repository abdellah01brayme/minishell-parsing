#include "../includes/parser.h"
#include "../includes/utils.h"

int	check_close_quote(t_token *token)
{
	size_t	i;
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

static int	exit_invalide_input(char *msg)
{
	print_err_syntax(msg);
	collect_malloc(NULL, CLEAR);
	access_exit_code(2, WRITE);
	return (1);
}

int	check_last(t_token *last)
{
	if (check_close_quote(last))
		return (exit_invalide_input("unclosed quote"));
	if (last->type == PIPE)
		return (exit_invalide_input(last->str));
	if (last->type != WORD)
		return (exit_invalide_input("newline"));
	return (0);
}

int	check_first(t_token *token)
{
	if (token->type == WORD)
		return (0);
	if (token->type == PIPE)
		return (exit_invalide_input(token->str));
	if (!token->next)
		return (exit_invalide_input("newline"));
	return (0);
}

int	check_valide_input(t_token *token)
{
	t_token	*cur;
	t_token	*prev;

	cur = token;
	prev = token;
	if (check_first(cur))
		return (1);
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		if (!cur)
			break ;
		if ((is_redirection(prev) && cur->type != WORD) ||
			(prev->type == PIPE && cur->type == PIPE))
			{
				printf("%s   %s\n", prev->str, cur->str);
				return (exit_invalide_input(cur->str));
			}
	}
	if (check_last(prev))
		return (1);
	return (0);
}
