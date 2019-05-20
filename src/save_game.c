/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_game.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/20 17:54:34 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/20 19:56:44 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	save_map_state(FILE *save, t_mlx *mlx)
{
	int x;
	int y;

	y = 0;
	while (y < mlx->map->size_y)
	{
		x = 0;
		while (x < mlx->map->size_x)
		{
			fprintf(save, "%d ", mlx->map->level[y][x]);
			x++;
		}
		fprintf(save, "%c", '\n');
		y++;
	}
}

void		save_game(t_mlx *mlx)
{
	FILE	*save;
	FILE	*save_map;

	save = fopen("src/gamesaves/save1", "w");
	save_map = fopen("src/gamesaves/save_map", "w");
	fprintf(save, "%d\n", mlx->player->ammo);
	fprintf(save, "%lf\n", mlx->player->dirx);
	fprintf(save, "%lf\n", mlx->player->diry);
	fprintf(save, "%lf\n", mlx->player->ms);
	fprintf(save, "%lf\n", mlx->player->planex);
	fprintf(save, "%lf\n", mlx->player->planey);
	fprintf(save, "%lf\n", mlx->player->posx);
	fprintf(save, "%lf\n", mlx->player->posy);
	save_map_state(save_map, mlx);
	fclose(save);
	fclose(save_map);
}
