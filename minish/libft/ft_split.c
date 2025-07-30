/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:27:28 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/09 12:02:49 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_all(char **vector)
{
	int	i;

	i = 0;
	while (vector[i])
	{
		free(vector[i]);
		i++;
	}
	free(vector);
}

int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((i == 0 && str[i] != c) || (str[i] != c && str[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static char	*copy_strs(char const *str, int *i, char c)
{
	int		j;
	int		len;
	char	*res;

	len = 0;
	while (str[*i] == c)
		(*i)++;
	while (str[*i + len] && str[*i + len] != c)
		len++;
	res = malloc(len * sizeof(char) + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (j < len && str[*i])
	{
		res[j] = str[*i];
		j++;
		(*i)++;
	}
	res[j] = '\0';
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		wc;
	char	**vector;

	i = 0;
	wc = count_words(s, c);
	vector = malloc((wc + 1) * sizeof(char *));
	if (!vector)
		return (NULL);
	j = 0;
	while (j < wc)
	{
		vector[j] = copy_strs(s, &i, c);
		if (!vector[j])
			free_all(vector);
		j++;
	}
	vector[j] = NULL;
	return (vector);
}
