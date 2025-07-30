/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:25:04 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 05:27:52 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	sigint_handler(int signum)
{
	if (SIGINT == signum)
	{
		access_exit_code(130, WRITE);
		rl_new_prompt();
		return ;
	}
}

void	handle_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
