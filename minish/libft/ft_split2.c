/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:46:48 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/02 10:03:43 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
int printf(const char*, ...);
static int	is_sep(char, char *);

static int	word_count(char *s, char *charset)
{
	int	wc;
	int	i;
	int	j;

	wc = 0;
	i = 0;
	j = 0;
	while (s[j + 1])
		j++;
	while (s[i] && is_sep(s[i], charset))
		i++;
	while (is_sep(s[j], charset) && j >= 0)
		j--;
	if (!s[i] || !j)
		return (0);
	while (i <= j)
	{
		if ((!i && !is_sep(s[i], charset))
			|| (!is_sep(s[i], charset) && is_sep(s[i - 1], charset)))
			wc++;
		i++;
	}
	return (wc);
}

static int	is_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	**ft_split2(char *str, char *charset)
{
	char	**split;
	int		wc;
	int		i;
	int		j;
	int		k;

	wc = word_count(str, charset);
	split = malloc((wc + 1) * sizeof(*split));
	if (!split)
		return (NULL);
	i = 0;
	k = 0;
	while (k < wc)
	{
		while (str[i] && is_sep(str[i], charset))
			i++;
		j = i;
		while (str[i] && !is_sep(str[i], charset))
			i++;
		split[k] = ft_substr(str, j, i - j);
		k++;
	}
	split[k] = NULL;
	return (split);
}


// int main(int x, char **y)
// {
// 	char **so = ft_split2(y[1], " \t\n\r\v\f");
	
// 	while (*so)
// 	{
// 		printf("%s\n", *so);
// 		so++;
// 	}

// }