#include "../includes/parser.h"

 void free_list_token(t_token *token)
{
	t_token *t;

	while (token)
	{
		t = token->next;
		if (token)
			collect_malloc(token, DELETE);
		token = t;
	}
}

t_list	*parser(char *input)
{
	t_token	*token;
	t_list	*cmd;

	token = get_tokens(input);
	if (!token)
		return (NULL);
	if (check_valide_input(token))
		return (NULL);
	cmd = set_cmd(token);
	free_list_token(token);
	expand(cmd);
	return (cmd);
}
