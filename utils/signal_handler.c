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
