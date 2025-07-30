/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:33:36 by mouahman          #+#    #+#             */
/*   Updated: 2025/01/04 10:24:24 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*tmp;

	ptr = *lst;
	tmp = NULL;
	while (ptr)
	{
		tmp = ptr->next;
		ft_lstdelone(ptr, del);
		ptr = tmp;
	}
	*lst = NULL;
}
