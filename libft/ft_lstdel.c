/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdel.c                                          :+:    :+:          */
/*                                                     +:+                    */
/*   By: nvreeke <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 19:20:33 by nvreeke       #+#    #+#                 */
/*   Updated: 2019/01/09 19:20:34 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *current;
	t_list *tmp;

	if (!alst || !del)
		return ;
	tmp = *alst;
	while (tmp)
	{
		current = tmp->next;
		del(tmp->content, tmp->content_size);
		free(tmp);
		tmp = current;
	}
	*alst = NULL;
}
