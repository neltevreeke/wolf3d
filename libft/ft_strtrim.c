/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 19:20:33 by nvreeke       #+#    #+#                 */
/*   Updated: 2019/01/09 19:20:34 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_beginstr(char const *s)
{
	int i;

	i = 0;
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && s[i])
	{
		i++;
	}
	return (i);
}

static int		ft_endstr(char const *s)
{
	int i;
	int k;

	k = 0;
	i = ft_strlen(s) - 1;
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && i >= 0)
	{
		i--;
		k++;
	}
	return (k);
}

char			*ft_strtrim(char const *s)
{
	size_t		start;
	size_t		end;
	char		*str;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	start = ft_beginstr(s);
	if (s[start + 1] == '\0')
		return (ft_strnew(0));
	end = ft_endstr(s);
	if (start == ft_strlen(s))
		return (ft_strnew(0));
	if (!(str = (char*)malloc(sizeof(char) *
	(ft_strlen(s) - end - start + 1))))
		return (NULL);
	while (start < ft_strlen(s) - end)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
