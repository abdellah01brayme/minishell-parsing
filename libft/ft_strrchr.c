/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:03:37 by mouahman          #+#    #+#             */
/*   Updated: 2024/10/27 09:24:48 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	last_index(const char *s, char c)
{
	int	index;

	index = (int)ft_strlen(s);
	while (index >= 0)
	{
		if (s[index] == c)
			return (index);
		index--;
	}
	return (-1);
}

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = last_index(s, (char)c);
	if (i != -1)
		return ((char *)&s[i]);
	return (0);
}
