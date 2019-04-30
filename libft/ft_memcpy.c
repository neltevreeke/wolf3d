/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 19:20:33 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/30 18:27:06 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	cpy_8(long *a, long *b)
{
	*a = *b;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		k;
	char*	a;
	char*	b;

	a = (char*)dst;
	b = (char*)src;
	k = strlen(src) / 8;
	n -= k * 8;
	while (k)
	{
		cpy_8((long*)a, (long*)b);
		a += 8;
		b += 8;
	}
	while (n)
	{
		*a = *b;
		a++;
		b++;
		n--;
	}
	return (dst);
}
