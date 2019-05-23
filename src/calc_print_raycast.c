/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_print_raycast.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 17:23:19 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 19:59:05 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../includes/xlm.h"
#include "../includes/map.h"
#include "../includes/player.h"
#include "../includes/sprites.h"
#include "../includes/raycast.h"

/*
**	Calculates what direction the player is moving
*/

void			determine_step_side(t_mlx *mlx, t_casting *casting)
{
	if (casting->ray_dir_x < 0)
	{
		casting->step_x = -1;
		casting->side_dist_x =
			(mlx->player->posx - casting->map_x) * casting->delta_dist_x;
	}
	else
	{
		casting->step_x = 1;
		casting->side_dist_x =
			(casting->map_x + 1 - mlx->player->posx) * casting->delta_dist_x;
	}
	if (casting->ray_dir_y < 0)
	{
		casting->step_y = -1;
		casting->side_dist_y =
			(mlx->player->posy - casting->map_y) * casting->delta_dist_y;
	}
	else
	{
		casting->step_y = 1;
		casting->side_dist_y =
			(casting->map_y + 1 - mlx->player->posy) * casting->delta_dist_y;
	}
}

/*
**	Calculates what side of a wall has been hit by the raycast
*/

void			determine_side_hit(t_mlx *mlx, t_casting *casting)
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

/*
**	Calculates the distance to the walls
*/

void			determine_distance(t_mlx *mlx, t_casting *casting)
{
	if (casting->side % 2 == 0)
		casting->per_wall_dist = (casting->map_x - mlx->player->posx
					+ (1 - casting->step_x) / 2) / casting->ray_dir_x;
	else
		casting->per_wall_dist = (casting->map_y - mlx->player->posy
					+ (1 - casting->step_y) / 2) / casting->ray_dir_y;
}

/*
**	Calculates the x position on the current wall tile
*/

void			determine_wall_x(t_mlx *mlx, t_casting *casting)
{
	if (casting->side % 2 == 0)
		casting->wall_x = mlx->player->posy
		+ casting->per_wall_dist * casting->ray_dir_y;
	else
		casting->wall_x = mlx->player->posx
		+ casting->per_wall_dist * casting->ray_dir_x;
	casting->wall_x -= floor((casting->wall_x));
}

/*
**	Calculates starting and ending points to draw the walls
*/

void			determine_begin_end(t_casting casting, int *begin, int *end)
{
	*begin = (HEIGHT / 2 - casting.lineheight / 2);
	if (*begin < 0)
		*begin = 0;
	*end = (HEIGHT / 2 - casting.lineheight / 2) + casting.lineheight;
	if (*end > HEIGHT)
		*end = HEIGHT;
}
