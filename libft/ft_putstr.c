/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 09:01:13 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/04 15:52:01 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_dot(int fd, int precision, char *s)
{
	int	len;
	int	count;
	int	i;

	len = ft_strlen(s);
	if (precision >= len || precision < 0)
		precision = len;
	i = 0;
	count = 0;
	while (i < precision)
	{
		count += ft_putchar(fd, s[i], 0, 0);
		i++;
	}
	return (count);
}

static int	handle_space(t_flags flags, int len)
{
	int	count;
	int	i;

	if (flags.w < 0)
		flags.w *= -1;
	if (flags.w == 0)
		flags.w = flags.fw;
	if (flags.p >= len || flags.p < 0)
		flags.p = len;
	i = 0;
	count = 0;
	while (i < flags.w - flags.p)
	{
		count += ft_putchar(flags.fd, ' ', 0, 0);
		i++;
	}
	return (count);
}

int	ft_putstr(char *s, t_flags flags)
{
	int	count;
	int	len;

	if (!s && flags.p < 6 && flags.p >= 0)
		return (ft_putstr("", flags));
	if (!s)
		return (ft_putstr("(null)", flags));
	count = 0;
	len = ft_strlen(s);
	if (flags.w < 0)
		count += handle_dot(flags.fd, flags.p, s);
	count += handle_space(flags, len);
	if (flags.w >= 0)
		count += handle_dot(flags.fd, flags.p, s);
	return (count);
}