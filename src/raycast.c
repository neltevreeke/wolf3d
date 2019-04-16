/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 18:35:01 by jvisser        #+#    #+#                */
/*   Updated: 2019/04/16 18:52:34 by nvreeke       ########   odam.nl         */
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

		int texX = (int)(wallX * (double)64);
      if(casting.side == 0 && casting.ray_dir_x > 0)
	  	texX = 64 - texX - 1;
      if(casting.side == 1 && casting.ray_dir_y < 0)
	  	texX = 64 - texX - 1;

		// int color = 0;
		for(int start = 0; start < (HEIGHT / 2 - casting.lineheight / 2); start++)	
			pixel_to_img(mlx, x, start, 0x414141);

		for(int y = (HEIGHT / 2 - casting.lineheight / 2); y < casting.lineheight; y++)
		{
			if (y < HEIGHT && y >= 0)
			{  
				int d = y * 256 - HEIGHT * 128 + casting.lineheight * 128;
				int texY = abs(((d) / casting.lineheight) / 256);

					ft_memcpy(IMG_ADD + mlx->size_line * y + x * (mlx->bits_per_pixel / 8) ,
							&mlx->map->textures->texture_data[1][ texY % 64 * mlx->map->textures->size_line[1] + texX % 64 * (mlx->map->textures->bits_per_pixel[1] / 8) ], 
							sizeof(int));
			}
		}
			
		// for(int start = 1; start <= casting.lineheight; start++)
		// {
		// 	// if (mlx->map->level[casting.map_y][casting.map_x] == 1)
		// 	// 	color = 0xFFFFFF;
		// 	// else if (mlx->map->level[casting.map_y][casting.map_x] == 2)
		// 	// 	color = 0x00FF00;
		// 	// else if (mlx->map->level[casting.map_y][casting.map_x] == 3)
		// 	// 	color = 0xFF0000;
		// 	// else
		// 	// 	color = 0xF00F00;
		// 	if (start + (HEIGHT / 2 - casting.lineheight / 2) < HEIGHT && start + (HEIGHT / 2 - casting.lineheight / 2) >= 0)
		// 	{        
		// 		// ft_memcpy(IMG_ADD + mlx->size_line * (start + (HEIGHT / 2 - casting.lineheight / 2)) + x * (mlx->bits_per_pixel  / 8) ,
		// 		// &mlx->map->textures->texture_data[0] + mlx->map->textures->size_line[0] * yscale + (mlx->map->textures->bits_per_pixel[0] / 8) * xscale, 
		// 		// sizeof(int));
		// 	}
		// 	// if (start + (HEIGHT / 2 - casting.lineheight / 2) < HEIGHT && start + (HEIGHT / 2 - casting.lineheight / 2) >= 0)
		// 	// 	pixel_to_img(mlx, x, start + (HEIGHT / 2 - casting.lineheight / 2), color);
		// }
		x++;
	}
}
