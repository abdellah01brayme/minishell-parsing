/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:55:11 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/14 06:42:25 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_dot(int n, char *s, int len, t_flags flags)
{
	int	i;
	int	count;

	count = 0;
	if (n >= 0 && flags.c && flags.w <= 0)
		count += ft_putchar(flags.fd, flags.c, 0, 0);
	if (flags.p <= len && flags.p > 0)
		return (write(flags.fd, s, len) + count);
	i = 0;
	while (i < flags.p - len)
	{
		count += ft_putchar(flags.fd, '0', 0, 0);
		i++;
	}
	if (flags.p == 0 && s[0] == '0')
		return (count);
	count += write(flags.fd, s, len);
	return (count);
}

static int	handle_space(int n, t_flags flags, int len)
{
	int		count;
	int		width;
	char	c;

	c = '0';
	count = 0;
	if (flags.p == 0 && n == 0)
		len--;
	if (n >= 0 && flags.c && flags.w > 0)
		count += ft_putchar(flags.fd, flags.c, 0, 0);
	width = flags.w;
	if (flags.w <= 0 || flags.p >= 0)
		c = ' ';
	if (flags.w == 0)
		width = flags.fw;
	if (width < 0)
		width *= -1;
	width -= ((n < 0) + flags.c != '\0');
	if (len >= flags.p)
		flags.p = len;
	while (width - (flags.p++) > 0)
		count += ft_putchar(flags.fd, c, 0, 0);
	if (n < 0 && c == ' ' && flags.w >= 0 && flags.p >= 0)
		count += ft_putchar(flags.fd, '-', 0, 0);
	return (count);
}

int	ft_putnbr(int n, t_flags flags)
{
	int				count;
	char			*s;
	int				len;
	unsigned int	nb;

	nb = n;
	count = 0;
	if (n < 0)
		nb = -n;
	s = ft_itoa_base(nb, "0123456789");
	if (!s)
		return (0);
	len = ft_strlen(s);
	if (n < 0
		&& ((flags.w != 0 && flags.p < 0) || (flags.w < 0 && flags.p >= 0)))
	{
		count += ft_putchar(flags.fd, '-', 0, 0);
		flags.c = '\0';
	}
	if (flags.w < 0)
		count += handle_dot(n, s, len, flags);
	count += handle_space(n, flags, len);
	if (flags.w >= 0)
		count += handle_dot(n, s, len, flags);
	return (free(s), count);
}
