/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 18:35:01 by jvisser        #+#    #+#                */
/*   Updated: 2019/04/25 11:44:19 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "wolf3d.h"

void	pixel_to_img(t_mlx *mlx, int px, int py, int color)
{
	color = mlx_get_color_value(MLX_PTR, color);
	ft_memcpy(IMG_ADD + mlx->size_line * py + px * mlx->bits_per_pixel / 8,
				&color, sizeof(int));
}

void    *raycasting(void *data)
{
	t_mlx		*mlx;
	t_casting	casting;

	mlx = (t_mlx*)data;
	while (mlx->cur_x < mlx->max_x)
	{
		casting.camera_x = 2 * mlx->cur_x / (double)WIDTH - 1;
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
			pixel_to_img(mlx, mlx->cur_x, start, 0x383838);
		int	index = mlx->map->level[casting.map_y][casting.map_x];
		int y = (HEIGHT / 2 - casting.lineheight / 2);
		if (y < 0)
			y = 0;
		int end = (HEIGHT / 2 - casting.lineheight / 2) + casting.lineheight;
		if (end > HEIGHT)
			end = HEIGHT;
		while (y < end)
		{
			if (y < HEIGHT && y >= 0)
			{
				int d = y - HEIGHT * 0.5 + casting.lineheight * 0.5;
				int texY = abs(((d * 128) / casting.lineheight));

					ft_memcpy(IMG_ADD + mlx->size_line * y + mlx->cur_x * mlx->bits_per_pixel / 8,
							&mlx->map->textures->texture_data[index - 1][ texY % 128 * mlx->map->textures->size_line[index - 1] + texX % 128 * (mlx->map->textures->bits_per_pixel[index - 1] / 8) ], 
							sizeof(int));
			}
			y++;
		}
		for(int start = (HEIGHT / 2 + casting.lineheight / 2); start < HEIGHT; start++)	
			pixel_to_img(mlx, mlx->cur_x, start, 0x707070);
		mlx->cur_x++;
	}
	return (data);
}

void	crosshair_to_img(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	j = 0;
	pixel_to_img(mlx, 500, 300, 0x25ff00);
	while (i < 5 && j < 5)
	{
		pixel_to_img(mlx, i + 490, 300, 0x25ff00);
		pixel_to_img(mlx, 506 + j, 300, 0x25ff00);
		pixel_to_img(mlx, 500, i + 290, 0x25ff00);
		pixel_to_img(mlx, 500, j + 306, 0x25ff00);
		i++;
		j++;
	}
}

void	create_image(t_mlx *mlx)
{
	int			i;
	t_mlx		tab[THREAD_AMOUNT];
	pthread_t	thread[THREAD_AMOUNT];

	i = 0;
	while (i < THREAD_AMOUNT)
	{
		ft_memcpy((void*)&tab[i], (void*)mlx, sizeof(t_mlx));
		tab[i].max_x = (i + 1) * (WIDTH / THREAD_AMOUNT);
		tab[i].cur_x = i * (WIDTH / THREAD_AMOUNT);
		pthread_create(&thread[i], NULL, &raycasting, &tab[i]);
		i++;
	}
	while (i)
	{
		pthread_join(thread[i - 1], NULL);
		i--;
	}
	crosshair_to_img(mlx);
}
