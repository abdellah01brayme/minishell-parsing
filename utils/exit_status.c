# include "../includes/utils.h"

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
