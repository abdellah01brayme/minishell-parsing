/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:24:49 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/14 06:40:06 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skkipp(char *format)
{
	int		skipp;
	int		i;

	i = 0;
	skipp = 2;
	while (format[i] && !is_valid(format[i]))
	{
		skipp++;
		i++;
	}
	return (skipp);
}

static char	find_format(char *format)
{
	int	i;

	i = 0;
	while (!is_valid(format[i]) && format[i])
		i++;
	return (format[i]);
}

static int	print(int fd, char *format, va_list ap)
{
	int		printed;
	char	c;
	t_flags	flags;

	printed = 0;
	flags = handle_flags(format);
	flags.fd = fd;
	c = find_format(format);
	if (c == 'c')
		printed += ft_putchar(fd, va_arg(ap, int), flags.w, flags.fw);
	else if (c == 'd' || c == 'i')
		printed += ft_putnbr(va_arg(ap, int), flags);
	else if (c == 'X')
		printed += ft_putnbr_up(va_arg(ap, int), flags);
	else if (c == 'x')
		printed += ft_putnbr_low(va_arg(ap, int), flags);
	else if (c == 'u')
		printed += ft_putunsigned(va_arg(ap, unsigned int), flags);
	else if (c == 's')
		printed += ft_putstr(va_arg(ap, char *), flags);
	else if (c == 'p')
		printed += ft_putaddress(va_arg(ap, void *), flags);
	return (printed);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	int		printed;
	int		i;
	va_list	ap;

	va_start(ap, format);
	i = 0;
	printed = 0;
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == '%')
		{
			printed += ft_putchar(fd, '%', 0, 0);
			i += 2;
		}
		else if (format[i] == '%')
		{
			printed += print(fd, (char *)&format[i + 1], ap);
			i += skkipp((char *)&format[i + 1]);
		}
		else
			printed += ft_putchar(fd, format[i++], 0, 0);
	}
	return (va_end(ap), printed);
}
