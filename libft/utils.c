/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:55:26 by mouahman          #+#    #+#             */
/*   Updated: 2025/02/01 21:22:49 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_valid(char c)
{
	char	*valid;

	valid = "diucsxXp%";
	return (ft_strchr(valid, c) != NULL);
}

int	negative(int n)
{
	if (n < 0)
		return (n);
	return (n * -1);
}
