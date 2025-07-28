
#include "../includes/parser.h"
void	print_args(t_list *arg)
{
	printf("|||||||||||||args||||||||||||||||||\n");
	while (arg)
	{
		printf("|%s|\n", (char *)arg->content);
		arg = arg->next;
	}
	printf("|||||||||||||||||||||||||||||||||||\n");
}

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

t_token	*prepar_args(t_list	**arg, t_token *tokens)
{
	t_list	*new;
	char	*new_arg;
	int		count;
	int		split;

	split = check_last_token_unexpanded(tokens);
	count = 0;
	new_arg = NULL;
	// print_tokens(tokens);
	while (tokens && !(tokens->type == SPLIT && split))
	{
		count++;
		new_arg = ft_join1(new_arg, 1, tokens->str, 1);
		if (tokens->next && tokens->next->type == SPLIT && split)
			break ;
		tokens = tokens->next;
	}
	if (count == 0 && tokens && tokens->type == SPLIT)
		new_arg = ft_join1(new_arg, 1, tokens->str, 1);
	new = ft_lstnew(new_arg);
	// printf("====%d=======>%s\n",count, (char *)new->content);
	collect_malloc(new, CHECK);
	ft_lstadd_back(arg, new);
	if (tokens)
		return (tokens->next);
	return (tokens);
}

t_list	*join_tokens_args(t_list **arg, t_token *tokens)
{
	t_list	*new_arg;
	t_list	*tmp_arg;
	t_list	*tmp_free;
	t_token	*tmp;

	tmp = tokens;
	new_arg = NULL;
	while (tmp)
		tmp = prepar_args(&new_arg, tmp);
	collect_malloc((*arg)->content, DELETE);
	(*arg)->content = new_arg->content;
	tmp_arg = (*arg)->next;
	tmp_free = new_arg;
	if (new_arg->next)
	{
		(*arg)->next = new_arg->next;
		while (new_arg->next)
			new_arg = new_arg->next;
		new_arg->next = tmp_arg;
		collect_malloc(tmp_free, DELETE);
		return (new_arg);
	}
	collect_malloc(tmp_free, DELETE);
	return (*arg);
}

int	expand_args(t_list *list_args)
{
	t_list	*tmp;
	t_token	*tokens;

	tmp = list_args;
	tokens = NULL;
	while (tmp)
	{
		tokens = split_token((char *)tmp->content);
		expand_tokens(tokens);
		split_after_expand(tokens);
		tmp = join_tokens_args(&tmp, tokens);
		// cmd->is_builtin = is_builtin(tokens->str);//////////
		free_list_token(tokens);
		tmp = tmp->next;
	}
	return (0);
} 

int	expand(t_list *list_cmd)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = list_cmd;
	while (tmp)
	{
		cmd = (t_cmd *)tmp->content;
		if (expand_redir(cmd->redir))
			return (1);
		if (expand_args(cmd->args))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
