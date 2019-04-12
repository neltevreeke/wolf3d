/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strequ.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 19:20:33 by nvreeke       #+#    #+#                 */
/*   Updated: 2019/01/09 19:20:34 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	size_t	i;
	char	*str;
	char	*str2;

	str = (char*)s1;
	str2 = (char*)s2;
	i = 0;
	if (!s1 || !s2)
		return (0);
	while (str[i] && str2[i])
	{
		if (str[i] != str2[i])
		{
			return (0);
		}
		i++;
	}
	if (str[i] != str2[i])
	{
		return (0);
	}
	return (1);
}
