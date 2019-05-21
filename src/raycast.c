/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 18:35:01 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/21 17:05:40 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "wolf3d.h"

void			pixel_to_img(t_mlx *mlx, int px, int py, int color)
{
	color = mlx_get_color_value(MLX_PTR, color);
	ft_memcpy(IMG_ADD + mlx->size_line * py + px * mlx->bits_per_pixel / 8,
				&color, sizeof(int));
}

static void		print_roof(t_mlx *mlx, t_casting casting)
{
	int		end;
	int		begin;
	double	current_dist;
	double	current_floor_x;
	double	current_floor_y;
	
	end = casting.lineheight / 2 + HEIGHT / 2;
	if (end < 0)
		end = HEIGHT;
	begin = end + 1;
	while (begin < HEIGHT)
	{
		current_dist = HEIGHT / (2.0 * begin - HEIGHT);
		current_floor_x = (current_dist) / (casting.per_wall_dist) * casting.topbot_wall_x
						+ (1.0 - (current_dist) / (casting.per_wall_dist)) * mlx->player->posx;
		current_floor_y = (current_dist) / (casting.per_wall_dist) * casting.topbot_wall_y
						+ (1.0 - (current_dist) / (casting.per_wall_dist)) * mlx->player->posy;
		ft_memcpy(IMG_ADD + mlx->size_line * (HEIGHT - begin) + mlx->cur_x * mlx->bits_per_pixel / 8,
					&mlx->map->textures->texture_data[38]
					[((int)(current_floor_y * 128) % 128) * mlx->map->textures->size_line[38]
					+ ((int)(current_floor_x * 128) % 128) * (mlx->map->textures->bits_per_pixel[38] / 8)],
					sizeof(int));
		begin++;
	}
}

static void		print_floor(t_mlx *mlx, t_casting casting)
{
	int	start;

	start = HEIGHT / 2 + casting.lineheight / 2;
	while (start < HEIGHT)
	{
		pixel_to_img(mlx, mlx->cur_x, start, 0x707070);
		start++;
	}
}

static void		init_raycasting(t_mlx *mlx, t_casting *casting)
{
	casting->camera_x = 2 * mlx->cur_x / (double)WIDTH - 1;
	casting->ray_dir_x = mlx->player->dirx + mlx->player->planex * casting->camera_x;
	casting->ray_dir_y = mlx->player->diry + mlx->player->planey * casting->camera_x;
	casting->map_x = (int)mlx->player->posx;
	casting->map_y = (int)mlx->player->posy;
	casting->delta_dist_x = fabs(1 / casting->ray_dir_x);
	casting->delta_dist_y = fabs(1 / casting->ray_dir_y);
	casting->hit = 0;
}

static void		determine_step_side(t_mlx *mlx, t_casting *casting)
{
	if (casting->ray_dir_x < 0)
	{
		casting->step_x = -1;
		casting->side_dist_x = (mlx->player->posx - casting->map_x) * casting->delta_dist_x;
	}
	else
	{
		casting->step_x = 1;
		casting->side_dist_x = (casting->map_x + 1 - mlx->player->posx) * casting->delta_dist_x;
	}
	if (casting->ray_dir_y < 0)
	{
		casting->step_y = -1;
		casting->side_dist_y = (mlx->player->posy - casting->map_y) * casting->delta_dist_y;
	}
	else
	{
		casting->step_y = 1;
		casting->side_dist_y = (casting->map_y + 1 - mlx->player->posy) * casting->delta_dist_y;
	}
}

static void		determine_side_hit(t_mlx *mlx, t_casting *casting)
{
	while (casting->hit == 0)
	{
		if (casting->side_dist_x < casting->side_dist_y)
		{
			casting->side_dist_x += casting->delta_dist_x;
			casting->map_x += casting->step_x;
			if (casting->step_x == 1)
				casting->side = 0;
			else
				casting->side = 2;
		}
		else
		{
			casting->side_dist_y += casting->delta_dist_y;
			casting->map_y += casting->step_y;
			if (casting->step_y == 1)
				casting->side = 1;
			else
				casting->side = 3;
		}
		if (mlx->map->level[casting->map_y][casting->map_x] > 0)
			casting->hit = 1;
	}
}

static void		determine_distance(t_mlx *mlx, t_casting *casting)
{
	if (casting->side % 2 == 0)
		casting->per_wall_dist = (casting->map_x - mlx->player->posx + (1 - casting->step_x) / 2) / casting->ray_dir_x;
	else
		casting->per_wall_dist = (casting->map_y - mlx->player->posy + (1 - casting->step_y) / 2) / casting->ray_dir_y;
}

static void		determine_wall_x(t_mlx *mlx, t_casting *casting)
{
	if (casting->side % 2 == 0)
		casting->wall_x = mlx->player->posy + casting->per_wall_dist * casting->ray_dir_y;
	else
		casting->wall_x = mlx->player->posx + casting->per_wall_dist * casting->ray_dir_x;
	casting->wall_x -= floor((casting->wall_x));
}

static void		determine_texture_x(t_casting *casting)
{
	casting->texture_x = (int)(casting->wall_x * (double)128);
	if(casting->side % 2 == 0 && casting->ray_dir_x > 0)
		casting->texture_x = 128 - casting->texture_x - 1;
	if(casting->side % 2 == 1 && casting->ray_dir_y < 0)
		casting->texture_x = 128 - casting->texture_x - 1;
	casting->texture_x = ft_abs(casting->texture_x);
}

static void		determine_begin_end(t_casting casting, int *begin, int *end)
{
	*begin = (HEIGHT / 2 - casting.lineheight / 2);
	if (*begin < 0)
		*begin = 0;
	*end = (HEIGHT / 2 - casting.lineheight / 2) + casting.lineheight;
	if (*end > HEIGHT)
		*end = HEIGHT;
}

static void		print_wall(t_mlx *mlx, t_casting casting)
{
	int	end;
	int	begin;
	int	wall_y;
	int	texture_y;
	int	wall_number;

	determine_begin_end(casting, &begin, &end);
	wall_number = mlx->map->level[casting.map_y][casting.map_x];
	while (begin < end)
	{
		if (begin < HEIGHT && begin >= 0)
		{
			wall_y = begin - HEIGHT * 0.5 + casting.lineheight * 0.5;
			texture_y = abs(((wall_y * 128) / casting.lineheight));
			if (mlx->screen->wall_side_textures == false)
				casting.side = 0;
			ft_memcpy(IMG_ADD + mlx->size_line * begin + mlx->cur_x * mlx->bits_per_pixel / 8,
					&mlx->map->textures->texture_data[(wall_number - 1 + casting.side) % AMOUNT_TEXTURES]
					[texture_y % 128 * mlx->map->textures->size_line[(wall_number - 1 + casting.side) % AMOUNT_TEXTURES]
					+ casting.texture_x % 128 * (mlx->map->textures->bits_per_pixel[(wall_number - 1 + casting.side) % AMOUNT_TEXTURES] / 8)],
					sizeof(int));
		}
		begin++;
	}
}

static void		determine_topbot(t_casting *casting)
{
	if(casting->side % 2 == 0)
	{
		casting->topbot_wall_y = casting->map_y + casting->wall_x;
		if (casting->ray_dir_x > 0)
			casting->topbot_wall_x = casting->map_x;
		else if (casting->ray_dir_x < 0)
			casting->topbot_wall_x = casting->map_x + 1.0;
	}
	else if(casting->side % 2 == 1)
	{
		casting->topbot_wall_x = casting->map_x + casting->wall_x;
		if (casting->ray_dir_y > 0)
			casting->topbot_wall_y = casting->map_y;
		else if (casting->ray_dir_y < 0)
			casting->topbot_wall_y = casting->map_y + 1.0;
	}
}

void			*raycasting(void *data)
{
	t_mlx		*mlx;
	t_casting	casting;

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

static void	sort_sprites(t_spritecast *spritecast)
{
	int i;
	int temp;
	int	temp2;

	i = 0;
	while (i < spritecast->amount - 1)
	{
		if (spritecast->sprite_distance[i] < spritecast->sprite_distance[i + 1])
		{
			temp = spritecast->sprite_distance[i];
			spritecast->sprite_distance[i] = spritecast->sprite_distance[i + 1];
			spritecast->sprite_distance[i + 1] = temp;

			temp2 = spritecast->sprite_order[i];
			spritecast->sprite_order[i] = spritecast->sprite_order[i + 1];
			spritecast->sprite_order[i + 1] = temp2;
			i = 0;
		}
		else
			i++;
	}
}

void	init_sprite_order_distance(t_mlx *mlx, t_spritecast *spritecast)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (y < mlx->map->size_y)
	{
		x = 0;
		while (x < mlx->map->size_x)
		{
			if (mlx->map->level[y][x] < 0)
			{
				mlx->map->sprites->x[i] = x;
				mlx->map->sprites->y[i] = y;
     			spritecast->sprite_order[i] = i;
     			spritecast->sprite_distance[i] = ((mlx->player->posx - mlx->map->sprites->x[i]) * (mlx->player->posx - mlx->map->sprites->x[i]) + (mlx->player->posy - mlx->map->sprites->y[i]) * (mlx->player->posy - mlx->map->sprites->y[i]));
				i++;
			}
			x++;
		}
		y++;
	}
	spritecast->amount = i;
}

void	sprites_to_img(t_mlx *mlx)
{
		// Sprite casting
	int	i;

	t_spritecast	spritecast;

	init_sprite_order_distance(mlx, &spritecast);
	sort_sprites(&spritecast);

	spritecast.frunk = 0;
	while (spritecast.frunk < spritecast.amount)
	{
		i = 0;
		while (spritecast.sprite_order[i] != spritecast.frunk && i < spritecast.amount)
			i++;
    	spritecast.sprite_x = mlx->map->sprites->x[i] + 0.5 - mlx->player->posx;
    	spritecast.sprite_y = mlx->map->sprites->y[i] + 0.5 - mlx->player->posy;
		spritecast.inverse = 1.0 / (mlx->player->planex * mlx->player->diry - mlx->player->dirx * mlx->player->planey);
		spritecast.transform_x = spritecast.inverse * (mlx->player->diry * spritecast.sprite_x - mlx->player->dirx * spritecast.sprite_y);
		spritecast.transform_y = spritecast.inverse * (-mlx->player->planey * spritecast.sprite_x + mlx->player->planex * spritecast.sprite_y);

		int spriteScreenX = (int)((WIDTH / 2) * (1 + spritecast.transform_x / spritecast.transform_y));
		int spriteHeight = abs((int)(HEIGHT / (spritecast.transform_y)));
		int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + HEIGHT / 2;
		if(drawEndY >= HEIGHT)
			drawEndY = HEIGHT - 1;
		int spriteWidth = abs( (int)(HEIGHT / (spritecast.transform_y)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= WIDTH)
			drawEndX = WIDTH - 1;
		int	sprite_texture = mlx->map->level[(int)mlx->map->sprites->y[i]][(int)mlx->map->sprites->x[i]];
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 128 / spriteWidth) / 256;
			if(spritecast.transform_y > 0 && stripe > 0 && stripe < WIDTH && spritecast.transform_y < mlx->map->sprites->zbuffer[stripe])
			{
				for(int y = drawStartY; y < drawEndY; y++)
				{
					int d = (y) * 256 - HEIGHT * 128 + spriteHeight * 128;
					int texY = ((d * 128) / spriteHeight) / 256;
					int color = 0;
					memcpy( &color, &mlx->map->sprites->sprite_data[ft_abs(sprite_texture) - 1]
					[ texY % 128 * mlx->map->sprites->size_line[ft_abs(sprite_texture) - 1]
					+ texX % 128 * (mlx->map->sprites->bits_per_pixel[ft_abs(sprite_texture) - 1] / 8)], sizeof(int));
					if((color & 0x00FFFFFF) != 0)
						memcpy(IMG_ADD + mlx->size_line * y + stripe * mlx->bits_per_pixel / 8,
								&color, sizeof(int));
				}
			}
		}
		spritecast.frunk++;
	}
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
