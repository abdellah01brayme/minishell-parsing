/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:30:32 by mouahman          #+#    #+#             */
/*   Updated: 2024/10/26 19:12:03 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strrev(char *str)
{
	int		l;
	int		r;
	char	tmp;

	l = 0;
	r = (int)ft_strlen(str) - 1;
	while (l < r)
	{
		tmp = str[l];
		str[l] = str[r];
		str[r] = tmp;
		l++;
		r--;
	}
	return (str);
}

static int	get_size(int n)
{
	int				size;
	unsigned int	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	if (nb == 0)
		return (1);
	size = 0;
	while (nb)
	{
		size++;
		nb = nb / 10;
	}
	return (size);
}

static void	fill(char *res, unsigned int nb, int size)
{
	int	i;

	i = 0;
	if (nb == 0)
		res[i++] = '0';
	while (nb)
	{
		res[i] = nb % 10 + 48;
		nb = nb / 10;
		i++;
	}
	if (i < size)
		res[i++] = '-';
	res[i] = '\0';
}

char	*ft_itoa(int n)
{
	int				size;
	char			*res;
	unsigned int	nb;
	int				less;

	size = get_size(n);
	if (n < 0)
	{
		res = malloc((size + 1) * sizeof(char) + 1);
		nb = -n;
		less = 1;
	}
	else
	{
		res = malloc(size * sizeof(char) + 1);
		nb = n;
		less = 0;
	}
	if (!res)
		return (NULL);
	fill(res, nb, size + less);
	res = ft_strrev(res);
	return (res);
}
