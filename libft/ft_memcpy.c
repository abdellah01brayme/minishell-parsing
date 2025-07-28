/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:18:09 by mouahman          #+#    #+#             */
/*   Updated: 2024/10/27 09:04:58 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dstp;
	unsigned char	*srcp;

	if (!dest && !src)
		return (dest);
	i = 0;
	dstp = (unsigned char *)dest;
	srcp = (unsigned char *)src;
	while (i < n)
	{
		dstp[i] = srcp[i];
		i++;
	}
	return (dest);
}
