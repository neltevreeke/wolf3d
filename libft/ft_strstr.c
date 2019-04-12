/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 19:20:33 by nvreeke       #+#    #+#                 */
/*   Updated: 2019/01/09 19:20:34 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;
	int k;

	i = 0;
	if (ft_strlen(needle) == 0)
	{
		return ((char*)haystack);
	}
	while (haystack[i])
	{
		j = 0;
		k = i;
		while (needle[j] == haystack[k] && needle[j] && haystack[k])
		{
			j++;
			k++;
		}
		if (needle[j] == '\0')
		{
			return ((char*)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
