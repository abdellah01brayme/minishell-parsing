/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:08:22 by mouahman          #+#    #+#             */
/*   Updated: 2024/10/25 09:06:50 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*copy;
	unsigned char	cc;

	i = 0;
	copy = (unsigned char *)s;
	cc = (unsigned char)c;
	while (i < n)
	{
		copy[i] = cc;
		i++;
	}
	return (s);
}
