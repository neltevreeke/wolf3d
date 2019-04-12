/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                            :+:    :+:          */
/*                                                     +:+                    */
/*   By: nvreeke <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 19:20:33 by nvreeke       #+#    #+#                 */
/*   Updated: 2019/01/09 19:20:34 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int		ft_isnegative(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

static int			ft_len(int n)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (n == 0)
		len++;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char				*ft_itoa(int n)
{
	char	*substr;
	int		len;

	len = ft_len(n);
	if (!(substr = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	substr[len] = '\0';
	len--;
	if (n == 0)
		substr[len] = '0';
	if (n < 0)
	{
		substr[0] = '-';
		n = n * -1;
	}
	while (n)
	{
		substr[len] = ft_isnegative(n % 10) + '0';
		n = ft_isnegative(n / 10);
		len--;
	}
	return (substr);
}
