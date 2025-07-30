/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:10:31 by mouahman          #+#    #+#             */
/*   Updated: 2024/10/23 21:51:50 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	size_t			j;
	char			*copy;

	i = 0;
	j = ft_strlen(s1) - 1;
	while (is_in_set(s1[i], set))
		i++;
	while (is_in_set(s1[j], set))
		j--;
	copy = ft_substr(s1, i, j - i + 1);
	return (copy);
}
