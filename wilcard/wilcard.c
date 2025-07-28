/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcard.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:37:47 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/05 15:04:26 by aid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static int	is_match(char *from, char *srch);

static int	boucl(char *from, int *i, char *srch, int *j)
{
	if (from[*i] == srch[*j] && from[*i] != '*')
	{
		(*i)++;
		(*j)++;
	}
	else if (srch[*j] == '*' && srch[*j + 1] == '*')
		(*j)++;
	else if (srch[*j] == '*' && srch[*j + 1] == from[*i])
	{
		if (is_match(&from[*i], &srch[(*j) + 1]))
			return (1);
		(*i)++;
	}
	else if (srch[*j] == '*')
		(*i)++;
	else if (from[*i] != srch[*j])
		return (0);
	return (2);
}

static int	is_match(char *from, char *srch)
{
	int	i;
	int	j;
	int	stat;

	i = 0;
	j = 0;
	while (from[i] && srch[j])
	{
		stat = boucl(from, &i, srch, &j);
		if (stat == 1)
			return (1);
		else if (stat == 0)
			return (0);
	}
	while (srch[j] == '*')
		j++;
	if (from[i] == srch[j] && !srch[j])
		return (1);
	return (0);
}

static int	add_to_list(t_list **lst, char *from, char *srch)
{
	t_list	*new;

	new = NULL;
	if (is_match(from, srch))
	{
		if (from[0] == '.')
			return (0);
		new = ft_lstnew(ft_strdup(from));
		if (!new)
		{
			ft_putstr_fd("Error: memory allocation\n", 2);
			ft_lstclear(lst, free);
			return (1);
		}
		ft_lstadd_back(lst, new);
	}
	return (0);
}

int main(int ac, char **srch)
{
	DIR				*dir;
	struct dirent	*_readdir;
	t_list			*list;

	list = NULL;
	dir = opendir(".");
	_readdir = readdir(dir);
	while (_readdir)
	{
		if (add_to_list(&list, _readdir->d_name, srch[1]))
			break ;
		_readdir = readdir(dir);
	}
	while (list)
	{
		printf("%s\n", (char *)list->content);
		list = list->next;
	}
	closedir(dir);
	return (0);
}
