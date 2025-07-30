/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:52:17 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/14 06:35:51 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_space(int fd, int width, int fwidth)
{
	int	count;
	int	i;

	if (width < 0)
		width *= -1;
	if (width == 0)
		width = fwidth;
	i = 0;
	count = 0;
	while (i < width - 1)
	{
		count += write(fd, " ", 1);
		i++;
	}
	return (count);
}

int	ft_putchar(int fd, char c, int width, int fwidth)
{
	int	count;

	count = 0;
	if (width < 0)
		count += write(fd, &c, 1);
	count += handle_space(fd, width, fwidth);
	if (width >= 0)
		count += write(fd, &c, 1);
	return (count);
}
