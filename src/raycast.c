/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 18:35:01 by jvisser        #+#    #+#                */
/*   Updated: 2019/04/15 20:04:17 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    create_image(t_mlx *mlx)
{
	int	x;
	t_casting	casting;

	x = 0;
	while (x < WIDTH)
	{
		casting.camera_x = 2 * x / (double)WIDTH - 1;
		casting.ray_dir_x = mlx->player->dirx + mlx->player->planex * casting.camera_x;
		casting.ray_dir_y = mlx->player->diry + mlx->player->planey * casting.camera_x;

		casting.map_x = (int)mlx->player->posx;
		casting.map_y = (int)mlx->player->posy;

		casting.delta_dist_x = fabs(1 / casting.ray_dir_x);
		casting.delta_dist_y = fabs(1 / casting.ray_dir_y);

		casting.hit = 0;
		if (casting.ray_dir_x < 0)
		{
			casting.step_x = -1;
			casting.side_dist_x = (mlx->player->posx - casting.map_x) * casting.delta_dist_x;
		}
		else
		{
			casting.step_x = 1;
			casting.side_dist_x = (casting.map_x + 1 - mlx->player->posx) * casting.delta_dist_x;
		}
		if (casting.ray_dir_y < 0)
		{
			casting.step_y = -1;
			casting.side_dist_y = (mlx->player->posy - casting.map_y) * casting.delta_dist_y;
		}
		else
		{
			casting.step_y = 1;
			casting.side_dist_y = (casting.map_y + 1 - mlx->player->posy) * casting.delta_dist_y;
		}
		while (casting.hit == 0)
		{
			if (casting.side_dist_x < casting.side_dist_y)
			{
				casting.side_dist_x += casting.delta_dist_x;
				casting.map_x += casting.step_x;
				casting.side = 0;
			}
			else
			{
				casting.side_dist_y += casting.delta_dist_y;
				casting.map_y += casting.step_y;
				casting.side = 1;
			}
			if (mlx->map->level[casting.map_y][casting.map_x] > 0)
				casting.hit = 1;
		}
		
		if (casting.side == 0)
		{
			printf("0\n");
			casting.per_wall_dist = (casting.map_x - mlx->player->posx + (1 - casting.step_x) / 2) / casting.ray_dir_x;
		}
		else
		{
			printf("1\n");
			casting.per_wall_dist = (casting.map_y - mlx->player->posy + (1 - casting.step_y) / 2) / casting.ray_dir_y;
		}

		printf("wall dist: %lf\n", casting.per_wall_dist);
		printf("map y: %d\n", casting.map_x);
		printf("pos y: %lf\n", mlx->player->posx);
		printf("step y: %d\n", casting.step_x);
		printf("ray dir y: %lf\n", casting.ray_dir_x);
		printf("wall dist: %lf\n", casting.per_wall_dist);
		printf("map y: %d\n", casting.map_y);
		printf("pos y: %lf\n", mlx->player->posy);
		printf("step y: %d\n", casting.step_y);
		printf("ray dir y: %lf\n", casting.ray_dir_y);


		casting.lineheight = (int)(HEIGHT / casting.per_wall_dist);

		printf("lineheight: %d\n", casting.lineheight);
		int color;
		for(int start = 0; start < casting.lineheight; start++)
		{
			if (mlx->map->level[casting.map_y][casting.map_x] == 1)
				color = 0xFFFFFF;
			else if (mlx->map->level[casting.map_y][casting.map_x] == 2)
				color = 0x00FF00;
			else if (mlx->map->level[casting.map_y][casting.map_x] == 3)
				color = 0xFF0000;
			
			mlx_pixel_put(MLX_PTR, WIN_PTR, x, start + (HEIGHT / 2 - casting.lineheight / 2), color);
		}
		x++;
	}
	getchar();
}