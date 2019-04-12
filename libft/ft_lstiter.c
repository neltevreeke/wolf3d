/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                         :+:    :+:          */
/*                                                     +:+                    */
/*   By: nvreeke <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 19:20:33 by nvreeke       #+#    #+#                 */
/*   Updated: 2019/01/09 19:20:34 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *current;

	if (!lst || !f)
		return ;
	current = lst->next;
	f(lst);
	while (current)
	{
		f(current);
		current = current->next;
	}
}
