/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/28 13:51:14 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/15 15:53:26 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Mallocs 2d int array
*/

void		ft_malloc_tab2(int row, int col, t_map *map, int fd)
{
	map->map = (int**)malloc(sizeof(int*) * row);
	while (row > 0)
	{
		row--;
		map->map[row] = (int*)malloc(sizeof(int) * col);
	}
	close(fd);
}

void		malloc_map(t_map *map, char *filename)
{
	char	*line;
    char    *tmp;
	int		fd;
	int		col;
	int		row;

	col = 0;
	row = 0;
	fd = open(filename, O_RDONLY);
	// if (fd < 0)
	// 	error
	while (get_next_line(fd, &line))
	{
        tmp = line;
		if (!col)
			col = ft_wordcount(line, ' ');
		row++;
		free(tmp);
	}
	free(line);
	map->size_x = col;
	map->size_y = row;
	ft_malloc_tab2(row, col, map, fd);
}

/*
** Checks if input is a negative number
*/

int			isnegnumber(char *line)
{
	if (*line == '-')
	{
		line++;
		if (ft_isdigit(*line) == 1)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

/*
** Fills the 2d array with the input
*/

void		while_fill(char *line, int j, int i, t_map *map)
{
	while (*line)
	{
		if (ft_isdigit(*line) == 1 || isnegnumber(line) == 1)
		{
			map->map[j][i] = ft_atoi(line);
			i++;
		}
		while (*line != ' ' && *line != '\n' && *line != '\t')
			line++;
		line = *line ? line + 1 : line;
	}
}

void		fill_map(t_map *map, char *filename)
{
	char	*line;
	char	*tmp;
	int		fd;
	int		i;
	int		j;

	j = 0;
	fd = open(filename, O_RDONLY);
    // if (fd < 0)
        // error
	while (get_next_line(fd, &line))
	{
		tmp = line;
		i = 0;
		while_fill(line, j, i, map);
		j++;
		free(tmp);
	}
	free(line);
	close(fd);
}
