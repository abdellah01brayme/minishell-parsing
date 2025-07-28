#include "../includes/utils.h"

void	rl_after_fork(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	rl_new_prompt(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}