/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                        :+:    :+:           */
/*                                                     +:+                    */
/*   By: nvreeke <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 19:20:33 by nvreeke       #+#    #+#                 */
/*   Updated: 2019/01/09 19:20:34 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (!(needle[j]))
		return ((char*)haystack);
	while (haystack[i] && i < len)
	{
		k = i;
		j = 0;
		while (haystack[k] == needle[j] && haystack[k] && k < len)
		{
			j++;
			k++;
		}
		if (!(needle[j]))
			return ((char*)&haystack[i]);
		i++;
	}
	return (NULL);
}
