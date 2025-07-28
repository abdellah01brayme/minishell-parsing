/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 10:03:48 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/14 06:46:40 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_space(int fd, int width, int len)
{
	int	count;

	count = 0;
	if (width < 0)
		width *= -1;
	if (len > width)
		return (0);
	while (width - len)
	{
		count += ft_putchar(fd, ' ', 0, 0);
		len++;
	}
	return (count);
}

static int	print_addr(int fd, char *s, int len)
{
	int	count;

	count = write(fd, "0x", 2);
	count += write(fd, s, len);
	return (count);
}

int	ft_putaddress(void *addr, t_flags flags)
{
	size_t	n;
	char	*s;
	int		len;
	int		count;

	if (!addr)
	{
		flags.p = -1;
		return (ft_putstr("(nil)", flags));
	}
	n = (unsigned long)addr;
	s = ft_itoa_base(n, "0123456789abcdef");
	if (!s)
		return (0);
	len = ft_strlen(s);
	count = 0;
	if (flags.w == 0)
		flags.w = flags.fw;
	if (flags.w < 0)
		count += print_addr(flags.fd, s, len);
	count += handle_space(flags.fd, flags.w, len + 2);
	if (flags.w >= 0)
		count += print_addr(flags.fd, s, len);
	free(s);
	return (count);
}
