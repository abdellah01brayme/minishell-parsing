
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