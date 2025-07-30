/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:23:55 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 06:45:41 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

// static int	is_builtin(char *cmd)
// {
// 	if (!ft_strcmp(cmd, "cd"))
// 		return (CD);
// 	else if (!ft_strcmp(cmd, "pwd"))
// 		return (PWD);
// 	else if (!ft_strcmp(cmd, "exit"))
// 		return (EXIT);
// 	else if (!ft_strcmp(cmd, "echo"))
// 		return (ECHO);
// 	else if (!ft_strcmp(cmd, "export"))
// 		return (EXPORT);
// 	else if (!ft_strcmp(cmd, "unset"))
// 		return (UNSET);
// 	else if (!ft_strcmp(cmd, "env"))
// 		return (ENV);
// 	return (NOT);
// }

static int	expand_redir(t_list *list_redir)
{
	t_list	*tmp;
	t_redir	*redir;
	t_token	*tokens;

	tmp = list_redir;
	tokens = NULL;
	while (tmp)
	{
		redir = (t_redir *)tmp->content;
		if (redir->type == RED_HERDOC)
		{
			tmp = tmp->next;
			continue ;
		}
		tokens = split_token(redir->file);
		expand_tokens(tokens);
		split_after_expand(tokens);
		join_tokens_redir(redir, tokens);
		free_list_token(tokens);
		tmp = tmp->next;
	}
	return (0);
}

static int	expand_args(t_list *list_args)
{
	t_list	*tmp;
	t_token	*tokens;
	int		export;

	tmp = list_args;
	tokens = NULL;
	export = 0;
	if (list_args && ft_strcmp(list_args->content, "export") == 0)
		export = 1;
	while (tmp)
	{
		tokens = split_token((char *)tmp->content);
		expand_tokens(tokens);
		if (!export || !check_valid_variable((char *)tmp->content))
			split_after_expand(tokens);
		tmp = join_tokens_args(&tmp, tokens);
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

///////// to export 
int	check_valid_variable(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	if (ft_isalpha(*str) || *str == '_')
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && str[i] != '=')
			i++;
		if (str[i] != '=' && str[i] != '\0')
			return (0);
		return (1);
	}
	return (0);
}
/*
manishell$ exho a$a
exho
a
1
2
3
*/