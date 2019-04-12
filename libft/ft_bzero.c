/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                          :+:    :+:           */
/*                                                     +:+                    */
/*   By: nvreeke <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 19:20:33 by nvreeke       #+#    #+#                 */
/*   Updated: 2019/01/09 19:20:34 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_bzero(void *s, size_t n)
{
	if (n == 0)
		return ;
	ft_memset(s, '\0', n);
}