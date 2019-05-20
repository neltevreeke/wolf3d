/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/28 13:51:14 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/20 19:56:47 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			open_file(char *filename, int mode)
{
	int		fd;

	fd = open(filename, mode);
	if (fd == -1)
		exit_failure_errno();
	return (fd);
}

void		malloc_map(t_map *map, char *filename)
{
	char	*line;
	int		fd;
	int		ret;
	int		temp;

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

void		set_number(int *i, int *map_point, char *line)
{
	while (line[*i] == ' ')
		(*i)++;
	if (ft_isdigit(line[*i]) || line[*i] == '-')
		*map_point = ft_atoi(&line[*i]);
	while (ft_isdigit(line[*i]) || line[*i] == '-')
		(*i)++;
}

void		fill_map(t_map *map, char *filename)
{
	int		i;
	int		fd;
	int		ret;
	char	*line;
	t_coord	coord;

	fd = open_file(filename, O_RDONLY);
	line = NULL;
	ret = get_next_line(fd, &line);
	coord.y = 0;
	while (ret)
	{
		i = 0;
		coord.x = 0;
		while (line[i])
		{
			set_number(&i, &(map->level[coord.y][coord.x]), line);
			coord.x++;
		}
		free(line);
		ret = get_next_line(fd, &line);
		coord.y++;
	}
	close(fd);
}
