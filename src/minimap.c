/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 13:48:33 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 19:48:33 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#include "../includes/xlm.h"
#include "../includes/map.h"
#include "../includes/player.h"
#include "../includes/minimap.h"

#include "../minilibx_macos/mlx.h"

/*
**	Colors the border for minimap
*/

static void		color_border(t_mlx *mlx)
{
	int			y;
	int			x;
	int			color;

	y = 0;
	color = 0x0000FF;
	while (y < 200)
	{
		x = 0;
		while (x < 200)
		{
			if ((y < 5 || y >= 195) || (x < 5 || x >= 195))
			{
				color = mlx_get_color_value(MLX_PTR, color);
				ft_memcpy(MINIMAP_ADD + mlx->mm_size_line * y +
						x * mlx->mm_bits_per_pixel / 8, &color, sizeof(int));
			}
			x++;
		}
		y++;
	}
}

/*
**	Colors the block in the minimap with the according color
*/

static void		fill_block(t_mlx *mlx, int y, int x, int color)
{
	int			x2;
	int			y2;

	y2 = 0;
	while (y2 < 10)
	{
		x2 = 0;
		while (x2 < 10)
		{
			ft_memcpy(MINIMAP_ADD + mlx->mm_size_line * (y * 10 + y2 + 5) +
			(x * 10 + x2 + 5) * mlx->mm_bits_per_pixel / 8,
			&color, sizeof(int));
			x2++;
		}
		y2++;
	}
}

/*
**	Checks the blocks of the minimap (items, player, walls etc)
*/

static void		check_type_block(t_mlx *mlx, int y, int x)
{
	if (y - (int)mlx->player->posy + 9 == 9
	&& x - (int)mlx->player->posx + 9 == 9)
		fill_block(mlx, y - (int)mlx->player->posy + 9,
						x - (int)mlx->player->posx + 9, 0xff0000);
	else if (mlx->map->level[y][x] != 0)
	{
		if (mlx->map->level[y][x] == -18)
			fill_block(mlx, y - (int)mlx->player->posy + 9,
							x - (int)mlx->player->posx + 9, 0x4f74af);
		else if (mlx->map->level[y][x] == -16)
			fill_block(mlx, y - (int)mlx->player->posy + 9,
							x - (int)mlx->player->posx + 9, 0xff7f7f);
		else if (mlx->map->level[y][x] == -17)
			fill_block(mlx, y - (int)mlx->player->posy + 9,
							x - (int)mlx->player->posx + 9, 0xff7f7f);
		else if (mlx->map->level[y][x] > 0)
			fill_block(mlx, y - (int)mlx->player->posy + 9,
							x - (int)mlx->player->posx + 9, 0x707070);
		else
			fill_block(mlx, y - (int)mlx->player->posy + 9,
							x - (int)mlx->player->posx + 9, 0x00ff00);
	}
}

/*
**	creates the minimap
*/

void			create_minimap(t_mlx *mlx)
{
	int			y;
	int			x;

	ft_bzero(MINIMAP_ADD, sizeof(int) * 200 * 200);
	color_border(mlx);
	y = 0;
	while (y < 19)
	{
		x = 0;
		if ((int)mlx->player->posy - 9 + y >= 0
		&& (int)mlx->player->posy - 9 + y < mlx->map->size_y)
		{
			while (x < 19)
			{
				if ((int)mlx->player->posx - 9 + x >= 0
				&& (int)mlx->player->posx - 9 + x < mlx->map->size_x)
					check_type_block(mlx, (int)mlx->player->posy - 9 + y,
									(int)mlx->player->posx - 9 + x);
				x++;
			}
		}
		y++;
	}
}
