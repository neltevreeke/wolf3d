/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 19:20:33 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 19:57:19 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

t_list				*ft_lstnew(void const *content, size_t content_size)
{
	t_list *newelem;

	if (!(newelem = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		newelem->content = NULL;
		newelem->content_size = 0;
	}
	else
	{
		if (!(newelem->content = (void*)malloc(sizeof(content_size))))
			return (NULL);
		ft_memcpy(newelem->content, content, content_size);
		newelem->content_size = content_size;
	}
	newelem->next = NULL;
	return (newelem);
}
