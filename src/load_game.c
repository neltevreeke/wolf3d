/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_game.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/20 17:49:50 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 19:52:31 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "../libft/libft.h"

#include "../includes/xlm.h"
#include "../includes/map.h"
#include "../includes/error.h"
#include "../includes/player.h"

static int		get_load_info_int(int fd)
{
	int			ret;
	int			result;
	char		*line;

	ret = get_next_line(fd, &line);
	if (ret < 0)
		exit_failure_errno();
	result = ft_atoi(line);
	free(line);
	return (result);
}

static float	get_load_info_float(int fd)
{
	int			ret;
	float		result;
	char		*line;

	ret = get_next_line(fd, &line);
	if (ret < 0)
		exit_failure_errno();
	result = atof(line);
	free(line);
	return (result);
}

void			load_game(t_mlx *mlx)
{
	int			fd;

	fd = open_file("src/gamesaves/save1", 00);
	mlx->player->ammo = get_load_info_int(fd);
	mlx->player->dirx = get_load_info_float(fd);
	mlx->player->diry = get_load_info_float(fd);
	mlx->player->ms = get_load_info_float(fd);
	mlx->player->planex = get_load_info_float(fd);
	mlx->player->planey = get_load_info_float(fd);
	mlx->player->posx = get_load_info_float(fd);
	mlx->player->posy = get_load_info_float(fd);
	close(fd);
	fill_map(mlx->map, "src/gamesaves/save_map");
}
