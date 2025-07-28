/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:50:32 by mouahman          #+#    #+#             */
/*   Updated: 2025/02/01 21:22:40 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_precision(char *format)
{
	int	i;

	i = 0;
	while (!is_valid(format[i]) && format[i])
	{
		if (format[i] == '.')
			return (ft_atoi2(&format[i + 1]));
		i++;
	}
	return (-5);
}

static int	get_width(char *format)
{
	int		i;

	i = 0;
	while (format[i] && !is_valid(format[i]))
	{
		if (format[i] == '-')
			return (negative(ft_atoi2(&format[i])));
		i++;
	}
	i = 0;
	while (format[i] && format[i] != '.' && !is_valid(format[i]))
	{
		if (ft_isdigit(format[i]) && format[i] != '0' && !is_valid(format[i]))
			return (0);
		else if (format[i] == '0')
		{
			while (!ft_isdigit(format[i + 1]) && format[i])
				i++;
			return (ft_atoi2(&format[i + 1]));
		}
		i++;
	}
	return (0);
}

static int	get_field_width(char *format)
{
	int	i;
	int	field_width;

	i = 0;
	while (!ft_isdigit(format[i]) && format[i] != '.' && format[i]
		&& !is_valid(format[i]))
		i++;
	field_width = ft_atoi2(&format[i]);
	return (field_width);
}

static char	get_flag(char *format)
{
	char	*valid;
	int		i;

	valid = "# +";
	i = 0;
	while (format[i] && !is_valid(format[i]))
	{
		if (ft_strchr(valid, format[i]))
			return (format[i]);
		i++;
	}
	return ('\0');
}

t_flags	handle_flags(char *format)
{
	t_flags	flags;

	flags.c = get_flag(format);
	flags.p = get_precision(format);
	flags.w = get_width(format);
	flags.fw = get_field_width(format);
	return (flags);
}
