/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstcmp.c                                          :+:    :+:          */
/*                                                     +:+                    */
/*   By: nvreeke <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 19:20:33 by nvreeke       #+#    #+#                 */
/*   Updated: 2019/01/09 19:20:34 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstcmp(t_list *list1, t_list *list2)
{
	int i;

	while (list1 && list2)
	{
		i = ft_strcmp(list1->content, list2->content);
		if (i != 0)
			return (i);
		list1 = list1->next;
		list2 = list2->next;
	}
	if (!list1 && list2)
		return (-(int)((unsigned char*)(list2->content))[0]);
	if (!list2 && list1)
		return ((int)((unsigned char*)(list1->content))[0]);
	return (0);
}
