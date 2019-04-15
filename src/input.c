/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/28 13:51:14 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/15 17:35:09 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    malloc_map(t_map* map, char *filename)
{
	char *line;
	int fd;
	int ret;
	int	temp;

	fd = open(filename, O_RDONLY);
	ret = 1;
	if (fd == -1)
		exit_failure_errno();
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (map->size_x == 0)
			map->size_x = ft_wordcount(line, ' ');
		if (ret)
		{
			map->size_y++;
			free(line);
		}
	}
	map->level = (int**)malloc(sizeof(int*) * map->size_y);
	temp = map->size_y;
	while (temp)
	{
		map->level[temp - 1] = (int*)malloc(sizeof(int) * map->size_x);
		temp--;
	}
	close(fd);
}

void	fill_map(t_map* map, char *filename)
{
	int		i;
	int		x;
	int		y;
	int		fd;
	int		ret;
	char	*line;
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_failure_errno();
	line = NULL;
	ret = get_next_line(fd, &line);
	y = 0;
	while (ret)
	{	
		i = 0;
		x = 0;
		while (line[i])
		{
			while (line[i] == ' ')
				i++;
			if (ft_isdigit(line[i]))
				map->level[y][x] = ft_atoi(&line[i]);
			while (ft_isdigit(line[i]))
				i++;
			x++;
		}
		free(line);
		ret = get_next_line(fd, &line);
		y++;
	}
	close(fd);
}
