/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 09:46:01 by mouahman          #+#    #+#             */
/*   Updated: 2025/02/01 21:25:47 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_size(size_t n, int blen)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		count++;
		n = n / blen;
	}
	return (count);
}

char	*ft_itoa_base(size_t n, char *base)
{
	int		size;
	int		blen;
	char	*ascii;

	blen = ft_strlen(base);
	size = num_size(n, blen);
	ascii = malloc(size * sizeof(char) + 1);
	if (!ascii)
		return (NULL);
	ascii[size] = '\0';
	while (size)
	{
		ascii[--size] = base[n % blen];
		n = n / blen;
	}
	return (ascii);
}
