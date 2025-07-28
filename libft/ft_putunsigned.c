/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 09:55:37 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/14 06:45:42 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_dot(int fd, char *s, int precision, int len)
{
	int	count;
	int	i;

	if (precision <= len)
		return (write(fd, s, len));
	count = 0;
	i = 0;
	while (i < precision - len)
	{
		count += ft_putchar(fd, '0', 0, 0);
		i++;
	}
	if (precision == 0 && s[0] == '0')
		return (count);
	count += write(fd, s, len);
	return (count);
}

static int	handle_space(t_flags flags, int len)
{
	int		count;
	char	c;

	c = '0';
	if (flags.w <= 0 || (flags.w >= 0 && flags.p >= 0))
		c = ' ';
	if (flags.w == 0)
		flags.w = flags.fw;
	if (flags.w < 0)
		flags.w *= -1;
	if (len >= flags.p)
		flags.p = len;
	if (flags.p > flags.w)
		return (0);
	count = 0;
	while (flags.w - flags.p)
	{
		count += ft_putchar(flags.fd, c, 0, 0);
		flags.p++;
	}
	return (count);
}

int	ft_putunsigned(unsigned int n, t_flags flags)
{
	int		count;
	char	*s;
	int		len;

	if (n == 0 && flags.p == 0)
		s = ft_strdup("");
	else
		s = ft_itoa_base(n, "0123456789");
	if (!s)
		return (0);
	count = 0;
	len = ft_strlen(s);
	if (flags.w < 0)
		count += handle_dot(flags.fd, s, flags.p, len);
	count += handle_space(flags, len);
	if (flags.w >= 0)
		count += handle_dot(flags.fd, s, flags.p, len);
	free(s);
	return (count);
}
