/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:21:49 by mouahman          #+#    #+#             */
/*   Updated: 2024/10/27 09:11:36 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dstp;
	unsigned char	*srcp;

	if (!dest && !src)
		return (NULL);
	dstp = (unsigned char *)dest;
	srcp = (unsigned char *)src;
	if (dstp > srcp)
		while (n--)
			dstp[n] = srcp[n];
	else if (dstp < srcp)
		ft_memcpy(dest, src, n);
	return (dest);
}
