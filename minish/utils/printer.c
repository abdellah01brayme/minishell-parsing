/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:54 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 05:53:36 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	print_err_syntax(char *msg)
{
	ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n", msg);
}

void	print_err1(char *msg)
{
	ft_printf_fd(2, "minishell: %s\n", msg);
}

void	print_err2(char *cmd, char *msg)
{
	ft_printf_fd(2, "minishell: %s: %s\n", cmd, msg);
}

void	print_err3(char *cmd, char *arg, char *msg)
{
	ft_printf_fd(2, "minishell: %s: %s: %s\n", cmd, arg, msg);
}
