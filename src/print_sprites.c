/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_sprites.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 17:00:15 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 19:49:54 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#include "../includes/xlm.h"
#include "../includes/map.h"
#include "../includes/player.h"
#include "../includes/sprites.h"

/*
**	Sets the sprite distance accoring to sprite and player position
*/

void		set_sprite_coordinates(
				t_mlx *mlx, t_spritecast *spritecast, int i)
{
	spritecast->sprite_order[i] = i;
	spritecast->sprite_distance[i] = (
		(mlx->player->posx - mlx->map->sprites->x[i])
		* (mlx->player->posx - mlx->map->sprites->x[i])
		+ (mlx->player->posy - mlx->map->sprites->y[i])
		* (mlx->player->posy - mlx->map->sprites->y[i]));
}

/*
**	Calculates the distance to the next sprite
*/

void		init_sprite_order_distance(
				t_mlx *mlx, t_spritecast *spritecast)
{
	int				i;
	int				x;
	int				y;

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
				set_sprite_coordinates(mlx, spritecast, i);
				i++;
			}
			x++;
		}
		y++;
	}
	spritecast->amount = i;
}

/*
**	Prints the sprites
*/

static void	print_sprite(t_mlx *mlx, t_spritecast spritecast)
{
	int				d;
	int				color;

	d = 0;
	color = 0;
	while (spritecast.draw_start_y < spritecast.draw_end_y)
	{
		d = (spritecast.draw_start_y) * 256 -
			HEIGHT * 128 + spritecast.sprite_height * 128;
		spritecast.texture_y = ((d * 128) / spritecast.sprite_height) / 256;
		color = 0;
		ft_memcpy(&color, &mlx->map->sprites->sprite_data
							[ft_abs(spritecast.sprite_texture) - 1]
		[spritecast.texture_y % 128 * mlx->map->sprites->size_line
							[ft_abs(spritecast.sprite_texture) - 1]
		+ spritecast.texture_x % 128 * (mlx->map->sprites->bits_per_pixel
				[ft_abs(spritecast.sprite_texture) - 1] / 8)], sizeof(int));
		if ((color & 0x00FFFFFF) != 0)
			memcpy(IMG_ADD + mlx->size_line * spritecast.draw_start_y
					+ spritecast.draw_start_x * mlx->bits_per_pixel / 8,
					&color, sizeof(int));
		spritecast.draw_start_y++;
	}
}

/*
**	Prints the sprites
*/

static void	draw_sprite(t_mlx *mlx, t_spritecast *spritecast)
{
	while (spritecast->draw_start_x < spritecast->draw_end_x)
	{
		spritecast->texture_x = (int)(256 * (spritecast->draw_start_x
								- (-spritecast->sprite_width / 2
								+ spritecast->sprite_screen_x)) * 128
								/ spritecast->sprite_width) / 256;
		if (spritecast->transform_y > 0 && spritecast->draw_start_x > 0
		&& spritecast->draw_start_x < WIDTH
		&& spritecast->transform_y < mlx->map->sprites->zbuffer
									[spritecast->draw_start_x])
			print_sprite(mlx, *spritecast);
		spritecast->draw_start_x++;
	}
}

/*
**	Determines what sprite is going to be printed
*/

void		sprites_to_img(t_mlx *mlx)
{
	int				i;
	t_spritecast	spritecast;

	init_sprite_order_distance(mlx, &spritecast);
	sort_sprites(&spritecast);
	spritecast.frunk = 0;
	while (spritecast.frunk < spritecast.amount)
	{
		i = 0;
		while (spritecast.sprite_order[i] != spritecast.frunk
				&& i < spritecast.amount)
			i++;
		determine_sprite_dimensions(mlx, &spritecast, i);
		determine_draw_start_end(&spritecast);
		spritecast.sprite_texture = mlx->map->level
		[(int)mlx->map->sprites->y[i]][(int)mlx->map->sprites->x[i]];
		draw_sprite(mlx, &spritecast);
		spritecast.frunk++;
	}
}
