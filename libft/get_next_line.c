/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/29 15:33:05 by nvreeke        #+#    #+#                */
/*   Updated: 2019/02/02 12:18:50 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char			*ft_strjoinchar(char *s, char c)
{
	int				i;
	int				j;
	char			*str;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	j = 0;
	str = ft_strnew(i + 1);
	if (!str)
		return (NULL);
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s);
	return (str);
}

static int			ft_copytill(char **line, char *src, char c)
{
	int				i;
	int				j;
	int				pos;

	i = 0;
	while (src[i])
	{
		if (src[i] == c)
			break ;
		i++;
	}
	pos = i;
	j = 0;
	while (src[j] != c && src[j])
	{
		*line = ft_strjoinchar(*line, src[j]);
		j++;
	}
	return (pos);
}

t_list				*ft_get_cur(t_list **list, const int fd)
{
	t_list			*tmp;

	tmp = *list;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", 1);
	tmp->content_size = fd;
	ft_lstadd(list, tmp);
	return (tmp);
}

static int			ft_read(const int fd, t_list *cur)
{
	int				ret;
	char			*tmp;
	char			buf[BUFF_SIZE + 1];

	ret = 1;
	while (ret)
	{
		ret = read(fd, buf, BUFF_SIZE);
		buf[ret] = '\0';
		tmp = cur->content;
		cur->content = ft_strjoin(tmp, buf);
		if (!cur->content)
			return (-1);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (ret);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*list;
	char			buf[BUFF_SIZE + 1];
	int				ret;
	t_list			*cur;
	char			*tmp;

	if (fd < 0 || line == NULL || (read(fd, buf, 0) < 0))
		return (-1);
	cur = ft_get_cur(&list, fd);
	*line = ft_strnew(0);
	if (!*line)
		return (-1);
	ret = ft_read(fd, cur);
	if (ret < BUFF_SIZE && ft_strlen(cur->content) == 0)
		return (0);
	ret = ft_copytill(line, cur->content, '\n');
	if (ret < (int)ft_strlen(cur->content))
	{
		tmp = cur->content;
		cur->content = ft_strdup(cur->content + ret + 1);
		free(tmp);
	}
	else
		ft_strclr(cur->content);
	return (1);
}
