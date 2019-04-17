/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 18:35:01 by jvisser        #+#    #+#                */
/*   Updated: 2019/04/17 12:04:22 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	pixel_to_img(t_mlx *mlx, int px, int py, int color)
{
	color = mlx_get_color_value(MLX_PTR, color);
	ft_memcpy(IMG_ADD + mlx->size_line * py + px * mlx->bits_per_pixel / 8,
				&color, sizeof(int));
}

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
			casting.per_wall_dist = (casting.map_x - mlx->player->posx + (1 - casting.step_x) / 2) / casting.ray_dir_x;
		}
		else
		{
			casting.per_wall_dist = (casting.map_y - mlx->player->posy + (1 - casting.step_y) / 2) / casting.ray_dir_y;
		}
		casting.lineheight = (int)(HEIGHT / casting.per_wall_dist);


		double wallX;
     	if (casting.side == 0)
	  		wallX = mlx->player->posy + casting.per_wall_dist * casting.ray_dir_y;
		else
	  		wallX = mlx->player->posx + casting.per_wall_dist * casting.ray_dir_x;
      	wallX -= floor((wallX));

		int texX = (int)(wallX * (double)128);
		if(casting.side == 0 && casting.ray_dir_x > 0)
	  		texX = 128 - texX - 1;
		if(casting.side == 1 && casting.ray_dir_y < 0)
	  		texX = 128 - texX - 1;
		texX = abs(texX);

		for(int start = 0; start < (HEIGHT / 2 - casting.lineheight / 2); start++)	
			pixel_to_img(mlx, x, start, 0x191970);
		int	index = mlx->map->level[casting.map_y][casting.map_x];
		for(int y = (HEIGHT / 2 - casting.lineheight / 2); y < (HEIGHT / 2 - casting.lineheight / 2) + casting.lineheight; y++)
		{
			if (y < HEIGHT && y >= 0)
			{
				int d = y - HEIGHT * 0.5 + casting.lineheight * 0.5;
				int texY = abs(((d * 128) / casting.lineheight));

					ft_memcpy(IMG_ADD + mlx->size_line * y + x * mlx->bits_per_pixel / 8,
							&mlx->map->textures->texture_data[index - 1][ texY % 128 * mlx->map->textures->size_line[index - 1] + texX % 128 * (mlx->map->textures->bits_per_pixel[index - 1] / 8) ], 
							sizeof(int));
			}
		}
		x++;
	}
}
