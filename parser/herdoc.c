# include "../includes/parser.h"
# include "../includes/minishell.h"
#include "../includes/utils.h"

# define LENGHT 20

static void	create_heredoc_name(char *file_name)
{
	char	random_c[LENGHT + 1];
	int		i;
	int		fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		print_err1(strerror(errno));
		collect_malloc(NULL, CLEAR);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < LENGHT)
	{
		read (fd, random_c, LENGHT);
		file_name[i] = random_c[i];
		i++;
	}
	file_name[i] = '\0';
	close(fd);
}

static void	herdoc_exit(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			rl_after_fork();
			error(1, WRITE);
			access_exit_code(130, WRITE);
		}
	}
	signal(SIGINT, sigint_handler);
}

int	parser_heredoc(char *delim)
{
	char	file[LENGHT + 1];
	pid_t	pid;
	int		fd;
	int		read_fd;

	create_heredoc_name(file);
	file[0] = 'a';
	file[1] = 'a';
	file[2] = 'a';
	file[3] = 'a';
	file[4] = '\0';
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return(print_err2(file, strerror(errno)), collect_malloc(NULL, CLEAR), exit(EXIT_FAILURE), -1);
	read_fd = open(file, O_RDONLY);
	if (read_fd < 0)
		return(print_err1(strerror(errno)), collect_malloc(NULL, CLEAR),
				exit(EXIT_FAILURE), close(fd), -1);
	// unlink(file);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		read_herdoc(delim, fd);
		close(fd);
		exit(0);
	}
	
	return (close(fd), herdoc_exit(pid), read_fd);
}
