/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ispunct.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/05 14:11:01 by jvisser        #+#    #+#                */
/*   Updated: 2019/03/05 14:13:54 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_ispunct(int c)
{
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64)
	|| (c >= 91 && c <= 96) || (c >= 123 && c <= 126))
		return (1);
	return (0);
}
