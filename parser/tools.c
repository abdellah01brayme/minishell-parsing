
#include "../includes/parser.h"

int	is_quote(char c)
{
	return (c == '"' ||
			c == '\'');
}

int	is_space(char c)
{
	return (c == ' ' ||
			c == '\n' ||
			c == '\t');
}

int	is_operator(char *input, size_t *i, int flag)
{
	char	*oper[] = {"|", ">>", "<<", ">", "<"};
	int		type[] = {PIPE, RED_APPOUT, RED_HERDOC, RED_OUT, RED_INP};
	int		len;
	int		j;

	j = 0;

	while (j < 5)
	{
		len = ft_strlen(oper[j]);
		
		if (ft_strncmp(oper[j], input + *i, len) == 0)
		{
			if (flag)
				*i += len;
			return (type[j]);
		}
		j++;
	}
	return (0);
}

int	is_redirection(t_token *token)
{
	return (token->type == RED_INP ||
			token->type == RED_OUT ||
			token->type == RED_APPOUT ||
			token->type == RED_HERDOC);
}

int	remove_quote(char *str)
{
	int		count;
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	count = 0;
	while (str[i + count])
	{
		if (is_quote(str[i + count]) && quote == str[i + count])
		{
			count++;
			quote = 0;
			continue ;
		}
		else if (is_quote(str[i + count]) && !quote)
		{
			quote = str[i + count];
			count++;
			continue ;
		}
		str[i] = str[i + count];
		i++;
	}
	return (str[i] = '\0', count);
}
