/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_print_sprites.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 17:05:44 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/24 15:52:59 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#include "../includes/xlm.h"
#include "../includes/map.h"
#include "../includes/player.h"
#include "../includes/sprites.h"
#include "../includes/raycast.h"

/*
**	Sorts the sprites accoring to distance (prints closest sprite last)
*/

void			sort_sprites(t_spritecast *spritecast)
{
	int			i;
	int			i2;
	int			i3;
	int			temp;

	i = 0;
	while (i < spritecast->amount - 1)
	{
		i2 = 0;
		i3 = 0;
		while (spritecast->sprite_order[i2] != i)
			i2++;
		while (spritecast->sprite_order[i3] != i + 1)
			i3++;
		if (spritecast->sprite_distance[i2] < spritecast->sprite_distance[i3])
		{
			temp = spritecast->sprite_order[i2];
			spritecast->sprite_order[i2] = spritecast->sprite_order[i3];
			spritecast->sprite_order[i3] = temp;
			i = 0;
		}
		else
			i++;
	}
}

/*
**	Calculates the starting and ending draw points for the sprites
*/

void			determine_draw_start_end(t_spritecast *spritecast)
{
	spritecast->draw_start_y = -spritecast->sprite_height / 2 + HEIGHT / 2;
	if (spritecast->draw_start_y < 0)
		spritecast->draw_start_y = 0;
	spritecast->draw_end_y = spritecast->sprite_height / 2 + HEIGHT / 2;
	if (spritecast->draw_end_y >= HEIGHT)
		spritecast->draw_end_y = HEIGHT - 1;
	spritecast->draw_start_x = -spritecast->sprite_width / 2
							+ spritecast->sprite_screen_x;
	if (spritecast->draw_start_x < 0)
		spritecast->draw_start_x = 0;
	spritecast->draw_end_x = spritecast->sprite_width / 2
							+ spritecast->sprite_screen_x;
	if (spritecast->draw_end_x >= WIDTH)
		spritecast->draw_end_x = WIDTH - 1;
}

/*
**	Calculates the dimensions for the sprites
*/

void			determine_sprite_dimensions(
					t_mlx *mlx, t_spritecast *spritecast, int i)
{
	spritecast->sprite_x = mlx->map->sprites->x[i] + 0.5 - mlx->player->posx;
	spritecast->sprite_y = mlx->map->sprites->y[i] + 0.5 - mlx->player->posy;
	spritecast->inverse = 1.0 / (mlx->player->planex
				* mlx->player->diry - mlx->player->dirx * mlx->player->planey);
	spritecast->transform_x = spritecast->inverse
				* (mlx->player->diry * spritecast->sprite_x
				- mlx->player->dirx * spritecast->sprite_y);
	spritecast->transform_y = spritecast->inverse
				* (-mlx->player->planey * spritecast->sprite_x
				+ mlx->player->planex * spritecast->sprite_y);
	spritecast->sprite_width = ft_abs(
							(int)(HEIGHT / (spritecast->transform_y)));
	spritecast->sprite_screen_x = (int)((WIDTH / 2)
				* (1 + spritecast->transform_x / spritecast->transform_y));
	spritecast->sprite_height = ft_abs(
							(int)(HEIGHT / (spritecast->transform_y)));
}

/*
**	Calculates top and bottom of non-wall tile
*/

void			determine_topbot(t_casting *casting)
{
	if (casting->side % 2 == 0)
	{
		casting->topbot_wall_y = casting->map_y + casting->wall_x;
		if (casting->ray_dir_x > 0)
			casting->topbot_wall_x = casting->map_x;
		else if (casting->ray_dir_x < 0)
			casting->topbot_wall_x = casting->map_x + 1.0;
	}
	else if (casting->side % 2 == 1)
	{
		casting->topbot_wall_x = casting->map_x + casting->wall_x;
		if (casting->ray_dir_y > 0)
			casting->topbot_wall_y = casting->map_y;
		else if (casting->ray_dir_y < 0)
			casting->topbot_wall_y = casting->map_y + 1.0;
	}
}

/*
**	Calculates the x position for the texture
*/

void			determine_texture_x(t_casting *casting)
{
	casting->texture_x = (int)(casting->wall_x * (double)128);
	if (casting->side % 2 == 0 && casting->ray_dir_x > 0)
		casting->texture_x = 128 - casting->texture_x - 1;
	if (casting->side % 2 == 1 && casting->ray_dir_y < 0)
		casting->texture_x = 128 - casting->texture_x - 1;
	casting->texture_x = ft_abs(casting->texture_x);
}
