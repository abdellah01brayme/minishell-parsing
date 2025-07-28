#include "../includes/minishell.h"
#include "../includes/parser.h"

void	print(t_list *cmd)
{
	t_list	*args;
	t_list	*red;
	t_redir	*r;

	while (cmd)
	{
		args = ((t_cmd *)(cmd->content))->args;
		red = ((t_cmd *)(cmd->content))->redir;
		while (args)
		{
			printf("%s\n", (char *)args->content);
			args = args->next;
		}
		printf("----------------------\n");
		while (red)
		{
			r = (t_redir *)red->content;
			printf("%d %s\t\t\n",r->type, r->file);
			red = red->next;
		}
		printf("===============================================\n");
		cmd = cmd->next;
	}
}

void	helper(char *input)
{
	t_list	*cmd;

	add_history(input);
	cmd = parser(input);
	if (cmd)
	{
		;
	}
	// access_exit_code(setup_execution(cmd), WRITE);
	print(cmd);
	collect_malloc(NULL, CLEAR);
}

int	main()
{
	char	*input;

	if (!isatty(STDOUT_FILENO) || !isatty(STDERR_FILENO))
		return (print_err1("file descriptor is not referring to a terminal"), 1);
	handle_signals();
	while (1)
	{
		input = readline("manishell$ ");
		if (!input)
			break ;
		if (input[0])
			helper(input);
		free (input);
	}
	return (EXIT_SUCCESS);
}
