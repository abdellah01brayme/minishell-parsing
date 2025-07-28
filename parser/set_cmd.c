#include "../includes/parser.h"

void	add_to_args(t_list **args, t_token *token)
{
	t_list	*new;

	new = ft_lstnew(token->str);
	collect_malloc(new, CHECK);
	ft_lstadd_back(args, new);
}

static void	add_to_redirection(t_list **redir, t_token *token)
{
	t_list	*new;
	t_redir	*tmp;

	tmp = malloc (sizeof(t_redir));
	collect_malloc(tmp, CHECK);
	tmp->type = token->type;
	tmp->file = token->next->str;
	tmp->heredoc_fd = -1;
	new = ft_lstnew(tmp);
	collect_malloc(new, CHECK);
	collect_malloc(token->str, DELETE);
	ft_lstadd_back(redir, new);
}

int is_builtin(char *cmd)
{
    if (!ft_strcmp(cmd, "cd"))
		return (CD);
	else if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	else if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	else if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
	else if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	else if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	else if (!ft_strcmp(cmd, "env"))
        return (ENV);
    return (NOT);
}

static t_list	*add_next_cmd(t_list **cmd, t_token *token)
{
	t_cmd	*new_cmd;
	t_list	*new_noued;
	t_list	*tmp;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	collect_malloc(new_cmd, CHECK);
	new_cmd->is_builtin = NOT;
	new_noued = ft_lstnew(new_cmd);
	collect_malloc(new_noued, CHECK);
	if (!(*cmd))
	{
		*cmd = new_noued;
		return (new_noued);
	}
	collect_malloc(token->str, DELETE);
	tmp = *cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_noued;
	return (new_noued);
}

t_list	*set_cmd(t_token *token)
{
	t_list	*cmd;
	t_list	*tmp;

	cmd = NULL;
	tmp = add_next_cmd(&cmd, token);
	while (token)
	{
		if (token->type == WORD)
			add_to_args(&(((t_cmd *)tmp->content)->args), token);
		else if (token->type == PIPE)
		{
			tmp = add_next_cmd(&cmd, token);
		}
		else if (is_redirection(token))
		{
			add_to_redirection(&(((t_cmd *)tmp->content)->redir), token);
			token = token->next;
		}
		token = token->next;
	}
	return (cmd);
}
