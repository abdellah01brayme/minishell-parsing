/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:18:43 by mouahman          #+#    #+#             */
/*   Updated: 2025/02/01 12:02:15 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	len;

	if (!(*little))
		return ((char *)big);
	i = 0;
	len = ft_strlen(little);
	while (big[i] && i < n)
	{
		if (big[i] == *little)
		{
			if (!ft_strncmp(big + i, little, len))
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
