/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_raycast.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 17:25:40 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 19:50:22 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#include "../includes/xlm.h"
#include "../includes/map.h"
#include "../includes/screen.h"
#include "../includes/player.h"
#include "../includes/raycast.h"
#include "../includes/textures.h"

/*
**	Puts the pixel of the roof to the image
*/

static void		roof_pixel_to_img(t_mlx *mlx, int begin, double x, double y)
{
	ft_memcpy(IMG_ADD + mlx->size_line * (HEIGHT - begin)
		+ mlx->cur_x * mlx->bits_per_pixel / 8,
		&mlx->map->textures->texture_data[38]
		[((int)(y * 128) % 128)
		* mlx->map->textures->size_line[38]
		+ ((int)(x * 128) % 128)
		* (mlx->map->textures->bits_per_pixel[38] / 8)],
		sizeof(int));
}

/*
**	Prints the roof
*/

void			print_roof(t_mlx *mlx, t_casting casting)
{
	int				end;
	int				begin;
	double			current_dist;
	double			current_floor_x;
	double			current_floor_y;

	end = casting.lineheight / 2 + HEIGHT / 2;
	if (end < 0)
		end = HEIGHT;
	begin = end + 1;
	while (begin < HEIGHT)
	{
		current_dist = HEIGHT / (2.0 * begin - HEIGHT);
		current_floor_x = (current_dist) / (casting.per_wall_dist)
						* casting.topbot_wall_x
						+ (1.0 - (current_dist) / (casting.per_wall_dist))
						* mlx->player->posx;
		current_floor_y = (current_dist) / (casting.per_wall_dist)
						* casting.topbot_wall_y
						+ (1.0 - (current_dist) / (casting.per_wall_dist))
						* mlx->player->posy;
		roof_pixel_to_img(mlx, begin, current_floor_x, current_floor_y);
		begin++;
	}
}

/*
**	Prints the floor
*/

void			print_floor(t_mlx *mlx, t_casting casting)
{
	int			start;

	start = HEIGHT / 2 + casting.lineheight / 2;
	while (start < HEIGHT)
	{
		pixel_to_img(mlx, mlx->cur_x, start, 0x707070);
		start++;
	}
}

/*
**	Puts the pixel of the wall on the image
*/

static void		wall_pixel_to_img(t_mlx *mlx,
				t_casting casting, int begin, int wall_number)
{
	ft_memcpy(IMG_ADD + mlx->size_line * begin
		+ mlx->cur_x * mlx->bits_per_pixel / 8,
		&mlx->map->textures->texture_data
		[(wall_number - 1 + casting.side) % AMOUNT_TEXTURES]
		[casting.texture_y % 128 * mlx->map->textures->size_line
		[(wall_number - 1 + casting.side) % AMOUNT_TEXTURES]
		+ casting.texture_x % 128 * (mlx->map->textures->bits_per_pixel
		[(wall_number - 1 + casting.side) % AMOUNT_TEXTURES] / 8)],
		sizeof(int));
}

/*
**	Prints the walls
*/

void			print_wall(t_mlx *mlx, t_casting casting)
{
	int			end;
	int			begin;
	int			wall_y;
	int			wall_number;

	determine_begin_end(casting, &begin, &end);
	wall_number = mlx->map->level[casting.map_y][casting.map_x];
	while (begin < end)
	{
		if (begin < HEIGHT && begin >= 0)
		{
			wall_y = begin - HEIGHT * 0.5 + casting.lineheight * 0.5;
			casting.texture_y = ft_abs(((wall_y * 128) / casting.lineheight));
			if (mlx->screen->wall_side_textures == false)
				casting.side = 0;
			wall_pixel_to_img(mlx, casting, begin, wall_number);
		}
		begin++;
	}
}
