/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:44:58 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/05 17:58:06 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	slen;
	size_t	dstlen;

	i = 0;
	if (!src || !dst)
		return (0);
	slen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (size <= dstlen)
		return (slen + size);
	while (src[i] && i < (size - dstlen - 1))
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (slen + dstlen);
}
