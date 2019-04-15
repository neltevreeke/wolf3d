/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 17:33:06 by jvisser        #+#    #+#                */
/*   Updated: 2019/03/27 13:48:26 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static void		save_new_line(t_list *list, char **line)
{
	size_t	index;

	index = 0;
	while (((char*)list->content)[index] != '\n'
	&& ((char*)list->content)[index] != '\0')
		index++;
	*line = ft_strsub((char*)list->content, 0, index);
	if (((char*)list->content)[index] == '\n')
		list->content = ft_strsub(list->content, index + 1,
									ft_strlen(list->content) - index);
	else
		list->content = ft_strnew(1);
}

static t_list	*get_curr_file(const int fd, t_list **list)
{
	t_list	*cpy_lst;

	cpy_lst = *list;
	while (cpy_lst)
	{
		if ((int)cpy_lst->content_size == fd)
			return (cpy_lst);
		cpy_lst = cpy_lst->next;
	}
	cpy_lst = ft_lstnew("\0", fd);
	ft_lstadd(list, cpy_lst);
	return (cpy_lst);
}

static void		set_current_content(void **content, char *str, char **tmp)
{
	*tmp = ft_strjoin(*content, str);
	free(*content);
	*content = *tmp;
}

int				get_next_line(const int fd, char **line)
{
	ssize_t			ret;
	char			*tmp;
	char			buf[BUFF_SIZE + 1];
	t_list			*current_file;
	static t_list	*list;

	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	tmp = NULL;
	current_file = get_curr_file(fd, &list);
	ret = 1;
	while (!(ft_strchr(current_file->content, '\n')) && (ret))
	{
		ret = read(fd, buf, BUFF_SIZE);
		buf[ret] = '\0';
		set_current_content(&(current_file->content), buf, &tmp);
	}
	if (ft_strchr(current_file->content, '\n'))
		set_current_content(&(current_file->content), "\0", &tmp);
	if (ret < BUFF_SIZE && !ft_strlen(current_file->content))
		return (0);
	save_new_line(current_file, line);
	if (tmp)
		free(tmp);
	return (1);
}
