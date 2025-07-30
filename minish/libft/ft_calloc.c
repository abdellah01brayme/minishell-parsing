/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:49:52 by mouahman          #+#    #+#             */
/*   Updated: 2024/10/29 18:59:57 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total;
	void			*ptr;

	total = nmemb * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, '\0', total);
	return (ptr);
}
