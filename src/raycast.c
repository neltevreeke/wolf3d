/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 18:35:01 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 19:20:47 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <pthread.h>

#include "../libft/libft.h"

#include "../includes/ui.h"
#include "../includes/xlm.h"
#include "../includes/map.h"
#include "../includes/player.h"
#include "../includes/sprites.h"
#include "../includes/raycast.h"

#include "../minilibx_macos/mlx.h"

/*
**	Prints the pixel to the image
*/

void				pixel_to_img(t_mlx *mlx, int px, int py, int color)
{
	color = mlx_get_color_value(MLX_PTR, color);
	ft_memcpy(IMG_ADD + mlx->size_line * py + px * mlx->bits_per_pixel / 8,
				&color, sizeof(int));
}

/*
**	initializes raycasting struct
*/

static void			init_raycasting(t_mlx *mlx, t_casting *casting)
{
	casting->camera_x = 2 * mlx->cur_x / (double)WIDTH - 1;
	casting->ray_dir_x = mlx->player->dirx
			+ mlx->player->planex * casting->camera_x;
	casting->ray_dir_y = mlx->player->diry
			+ mlx->player->planey * casting->camera_x;
	casting->map_x = (int)mlx->player->posx;
	casting->map_y = (int)mlx->player->posy;
	casting->delta_dist_x = fabs(1 / casting->ray_dir_x);
	casting->delta_dist_y = fabs(1 / casting->ray_dir_y);
	casting->hit = 0;
}

/*
**	Raycast function
*/

static void			*raycasting(void *data)
{
	t_mlx			*mlx;
	t_casting		casting;

	mlx = (t_mlx*)data;
	while (mlx->cur_x < mlx->max_x)
	{
		init_raycasting(mlx, &casting);
		determine_step_side(mlx, &casting);
		determine_side_hit(mlx, &casting);
		determine_distance(mlx, &casting);
		mlx->map->sprites->zbuffer[mlx->cur_x] = casting.per_wall_dist;
		casting.lineheight = (int)(HEIGHT / casting.per_wall_dist);
		determine_wall_x(mlx, &casting);
		determine_texture_x(&casting);
		print_wall(mlx, casting);
		determine_topbot(&casting);
		print_roof(mlx, casting);
		print_floor(mlx, casting);
		mlx->cur_x++;
	}
	return (data);
}

/*
**	Start of multithreading of raycasting
*/

void				create_image(t_mlx *mlx)
{
	int				i;
	t_mlx			tab[THREAD_AMOUNT];
	pthread_t		thread[THREAD_AMOUNT];

	i = 0;
	while (i < THREAD_AMOUNT)
	{
		ft_memcpy((void*)&tab[i], (void*)mlx, sizeof(t_mlx));
		tab[i].max_x = (i + 1) * (WIDTH / THREAD_AMOUNT);
		tab[i].cur_x = i * (WIDTH / THREAD_AMOUNT);
		pthread_create(&thread[i], NULL, raycasting, &tab[i]);
		i++;
	}
	while (i)
	{
		pthread_join(thread[i - 1], NULL);
		i--;
	}
	sprites_to_img(mlx);
	crosshair_to_img(mlx);
}
