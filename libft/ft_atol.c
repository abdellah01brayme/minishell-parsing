/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:47:37 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/24 15:49:49 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atol(char *s)
{
	long	result;
	long	sign;
	size_t	i;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(s[i]) && s[i])
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(s[i]) && s[i])
	{
		if (result > INT_MAX || (result * sign) < INT_MIN)
			return (2147483648);
		result = result * 10 + s[i] - 48;
		i++;
	}
	return (result * sign);
}
