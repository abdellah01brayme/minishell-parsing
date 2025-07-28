/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:13:30 by mouahman          #+#    #+#             */
/*   Updated: 2024/10/25 09:04:07 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	cc;

	i = 0;
	ptr = (unsigned char *)s;
	cc = (unsigned char)c;
	while (i < n)
	{
		if (ptr[i] == cc)
			return ((void *)(ptr + i));
		i++;
	}
	return (0);
}
