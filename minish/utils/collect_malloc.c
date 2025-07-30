/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:46 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 05:52:46 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

static void	free_ptr(t_list **lst, void *ptr)
{
	t_list	*cur;
	t_list	*prev;

	if (!ptr)
		return ;
	prev = *lst;
	cur = prev;
	while (cur && cur->content != ptr)
	{
		prev = cur;
		cur = cur->next;
	}
	if (!cur)
		return ;
	if (prev == cur)
		*lst = cur->next;
	else
		prev->next = cur->next;
	ft_lstdelone(cur, free);
}

void	collect_malloc(void *ptr, int option)
{
	static t_list	*lst = NULL;
	t_list			*tmp;

	if (!ptr && option == CHECK)
	{
		ft_lstclear(&lst, free);
		print_err1("Memory allocation");
		exit(EXIT_FAILURE);
	}
	else if (option == CHECK)
	{
		tmp = ft_lstnew(ptr);
		if (!tmp)
		{
			ft_lstclear(&lst, free);
			print_err1("Memory allocation");
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(&lst, tmp);
	}
	else if (option == DELETE)
		free_ptr(&lst, ptr);
	else if (option == CLEAR)
		ft_lstclear(&lst, free);
}
