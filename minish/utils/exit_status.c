/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:51 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 05:51:20 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

int	access_exit_code(int new_val, int mode)
{
	static int	exit_code;

	if (mode == READ)
		return (exit_code);
	if (mode == WRITE)
		exit_code = new_val;
	return (exit_code);
}

int	error(int c, int mode)
{
	static int	err;

	if (READ == mode)
	{
		return (err);
	}
	err = c;
	return (err);
}
