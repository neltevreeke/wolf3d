/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                       :+:    :+:           */
/*                                                     +:+                    */
/*   By: nvreeke <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 19:20:33 by nvreeke       #+#    #+#                 */
/*   Updated: 2019/01/09 19:20:34 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_lettercount(char const *s, char c)
{
	int counter;

	counter = 0;
	while (*s == c && *s != '\0')
		s++;
	while (*s != c && *s != '\0')
	{
		if (*s != c)
			counter++;
		s++;
	}
	return (counter);
}

static char		**ft_fillmdarr(char **arr, char const *s, int aw, char c)
{
	int		j;
	int		i;
	int		k;

	j = 0;
	k = 0;
	while (j < aw)
	{
		i = 0;
		if (!(arr[j] = (char*)malloc((ft_lettercount(&s[k], c) + 1))))
			return (NULL);
		while (s[k] == c)
			k++;
		while (s[k] != c && s[k])
			arr[j][i++] = s[k++];
		arr[j][i] = '\0';
		j++;
	}
	return (arr);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		amountwords;

	if (!s)
		return (NULL);
	amountwords = ft_wordcount(s, c);
	if (!(arr = (char**)malloc((amountwords + 1) * sizeof(char*))))
		return (NULL);
	arr[amountwords] = NULL;
	return (ft_fillmdarr(arr, s, amountwords, c));
}
