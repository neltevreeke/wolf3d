/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   event_handlers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 12:06:06 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/23 18:17:54 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// void		ui_handlers(int key, t_mlx *mlx)
// {

// }

int			exit_x(void *nul)
{
	(void)nul;
	exit(EXIT_SUCCESS);
}


	//	oplossing 1:

	//	Hoeken hier apart berekenen? || groter maken want die bestaan in principe nog niet
	//	met behulp van pythagoras de hoeken uitrekenen voor triangles.
	//	dus je C^2 van a^2 + b^2 (je eind punt van (mlx->player->posy + mlx->player->diry / 5 - 0.15 ^ 2 + (mlx->player->posx + mlx->player->dirx / 5 - 0.15) ^ 2)
	//	Dan heb je je C^2 en dan moeten we die nog tekenen
	//	Dan met Sinus de hoek rond afwerken?

// int			check_left_right(t_mlx *mlx)
// {
// 	ft_printf("leftright start\n");
// 	if (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 - 0.15)]
// 	&& mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 - 0.15)])
// 		return (1);
// 	if (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 + 0.15)]
// 	&& mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 + 0.15)])
// 		return (1);
// 	return(0);
// s}

// int			check_top_bottom(t_mlx *mlx)
// {
// 	ft_printf("topbot start\n");

// 	if (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 + 0.15)]
// 	&& mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 - 0.15)])
// 		return (1);
// 	if (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 - 0.15)]
// 	&& mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 + 0.15)])
// 		return (1);
// 	return(0);
// }

// void		calculate_thing(t_mlx *mlx, double *distance, int *side)
// {
// 	t_casting casting;

// 	casting.ray_dir_x = mlx->player->dirx;
// 	casting.ray_dir_y = mlx->player->diry;

// 	casting.map_x = (int)mlx->player->posx;
// 	casting.map_y = (int)mlx->player->posy;

// 	casting.delta_dist_x = fabs(1 / casting.ray_dir_x);
// 	casting.delta_dist_y = fabs(1 / casting.ray_dir_y);

// 	casting.hit = 0;
// 	if (casting.ray_dir_x < 0)
// 	{
// 		casting.step_x = -1;
// 		casting.side_dist_x = (mlx->player->posx - casting.map_x) * casting.delta_dist_x;
// 	}
// 	else
// 	{
// 		casting.step_x = 1;
// 		casting.side_dist_x = (casting.map_x + 1 - mlx->player->posx) * casting.delta_dist_x;
// 	}
// 	if (casting.ray_dir_y < 0)
// 	{
// 		casting.step_y = -1;
// 		casting.side_dist_y = (mlx->player->posy - casting.map_y) * casting.delta_dist_y;
// 	}
// 	else
// 	{
// 		casting.step_y = 1;
// 		casting.side_dist_y = (casting.map_y + 1 - mlx->player->posy) * casting.delta_dist_y;
// 	}

// 	while (casting.hit == 0)
// 	{
// 		if (casting.side_dist_x < casting.side_dist_y)
// 		{
// 			casting.side_dist_x += casting.delta_dist_x;
// 			casting.map_x += casting.step_x;
// 			casting.side = 0;
// 		}
// 		else
// 		{
// 			casting.side_dist_y += casting.delta_dist_y;
// 			casting.map_y += casting.step_y;
// 			casting.side = 1;
// 		}
// 		if (mlx->map->level[casting.map_y][casting.map_x] > 0)
// 			casting.hit = 1;
// 	}
// 	if (casting.side == 0)
// 	{
// 		casting.per_wall_dist = (casting.map_x - mlx->player->posx + (1 - casting.step_x) / 2) / casting.ray_dir_x;
// 	}
// 	else
// 	{
// 		casting.per_wall_dist = (casting.map_y - mlx->player->posy + (1 - casting.step_y) / 2) / casting.ray_dir_y;
// 	}
// 	*distance = casting.per_wall_dist;
// 	*side = casting.side;
// }

// # include <float.h>

void		check_player_move(t_mlx *mlx)
{
	if (mlx->keys->key_w == true)
	{
		// // ft_printf("Wstart\n");
		// if (
		// // 	// (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5)] == 0
		// // && mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5)] == 0)

		// // 3
		// (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 - 0.15)] == 0
		// // 1
		// && mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 - 0.15)] == 0)

		// // 2
		// || (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 + 0.15)] == 0
		// // 4
		// && mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 + 0.15)] == 0))
		// {
		// 	mlx->player->posy += mlx->player->diry / 5;
		// }
			
		// if (
		// // 	(mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5)][(int)(mlx->player->posx + mlx->player->dirx / 5 - 0.15)] == 0
		// // && mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5)][(int)(mlx->player->posx + mlx->player->dirx / 5 + 0.15)] == 0)
		// (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 + 0.15)] == 0
		// && mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 - 0.15)] == 0)
		// && (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 - 0.15)] == 0
		// && mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 + 0.15)] == 0))
		// {
		// 	// ft_printf("normal\n");
		// 	mlx->player->posx += mlx->player->dirx / 5;
		// }
		// // ft_printf("Wdone\n");


		// double	distance;
		// int side;

		// calculate_thing(mlx, &distance, &side);
		// ft_printf("%f\n", distance);
		// if (distance <= 0.15 && distance >= 0.1)
		// {
		// 	if (side == 0)
		// 	{
		// 		ft_printf("side 1\n");
		// 		mlx->player->posy += mlx->player->diry / 5;
		// 	}
		// 	else
		// 	{
		// 		ft_printf("side 0\n");
		// 		mlx->player->posx += mlx->player->dirx / 5;
		// 	}
		// }
		// else
		// {
		// 	ft_printf("else\n");
		// 	mlx->player->posy += mlx->player->diry / 5;
		// 	mlx->player->posx += mlx->player->dirx / 5;
		// }
		if (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5)] == 0
		&& mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5)] == 0)
		{
			mlx->player->posy += mlx->player->diry / 5;
		}

		if (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5)][(int)(mlx->player->posx + mlx->player->dirx / 5 - 0.15)] == 0
		&& mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5)][(int)(mlx->player->posx + mlx->player->dirx / 5 + 0.15)] == 0)
		{
			mlx->player->posx += mlx->player->dirx / 5;
		}
	}
	if (mlx->keys->key_s == true)
	{
		if (mlx->map->level[(int)(mlx->player->posy - mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx - mlx->player->dirx / 5)] == 0
		&& mlx->map->level[(int)(mlx->player->posy - mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx - mlx->player->dirx / 5)] == 0)
		{
			mlx->player->posy -= mlx->player->diry / 5;
		}
		if (mlx->map->level[(int)(mlx->player->posy - mlx->player->diry / 5)][(int)(mlx->player->posx - mlx->player->dirx / 5 - 0.15)] == 0
		&& mlx->map->level[(int)(mlx->player->posy - mlx->player->diry / 5)][(int)(mlx->player->posx - mlx->player->dirx / 5 + 0.15)] == 0)
		{
			mlx->player->posx -= mlx->player->dirx / 5;
		}
	}
	if (mlx->keys->key_a == true)
	{
		double x_save = mlx->player->dirx;
		mlx->player->dirx = x_save * cos(-3 * M_PI * 0.0055) - mlx->player->diry * sin(-3 * M_PI * 0.0055);
		mlx->player->diry = x_save * sin(-3 * M_PI * 0.0055) + mlx->player->diry * cos(-3 * M_PI * 0.0055);
		x_save = mlx->player->planex;
		mlx->player->planex = x_save * cos(-3 * M_PI * 0.0055) - mlx->player->planey * sin(-3 * M_PI * 0.0055);
		mlx->player->planey = x_save * sin(-3 * M_PI * 0.0055) + mlx->player->planey * cos(-3 * M_PI * 0.0055);
	}
	if (mlx->keys->key_d == true)
	{
		double x_save = mlx->player->dirx;
		mlx->player->dirx = x_save * cos(3 * M_PI * 0.0055) - mlx->player->diry * sin(3 * M_PI * 0.0055);
		mlx->player->diry = x_save * sin(3 * M_PI * 0.0055) + mlx->player->diry * cos(3 * M_PI * 0.0055);
		x_save = mlx->player->planex;
		mlx->player->planex = x_save * cos(3 * M_PI * 0.0055) - mlx->player->planey * sin(3 * M_PI * 0.0055);
		mlx->player->planey = x_save * sin(3 * M_PI * 0.0055) + mlx->player->planey * cos(3 * M_PI * 0.0055);
	}
}

int			deal_key_press(int key, t_mlx *mlx)
{
	if (KEY_ESC == key)
	{
		mlx_destroy_image(MLX_PTR, IMG_PTR);
		if (mlx->screen->main_game == false)
		{
			IMG_PTR = mlx_new_image(MLX_PTR, WIDTH, HEIGHT);
			IMG_ADD = mlx_get_data_addr(IMG_PTR, &(mlx->bits_per_pixel), &(mlx->size_line), &(mlx->endian));
			mlx->screen->main_game = true;
			mlx->screen->menu = false;
		}
		else
		{
			mlx->screen->main_game = false;
			mlx->screen->menu = true;
		}
	}
	else if (mlx->screen->main_game == true)
	{
		if (key == KEY_W)
			mlx->keys->key_w = true;
		else if (key == KEY_S)
			mlx->keys->key_s = true;
		else if (key == KEY_A)
			mlx->keys->key_a = true;
		else if (key == KEY_D)
			mlx->keys->key_d = true;
	}
	return (0);
}

int			deal_key_release(int key, t_mlx *mlx)
{
	if (mlx->screen->main_game == true)
	{
		if (key == KEY_W)
			mlx->keys->key_w = false;
		else if (key == KEY_S)
			mlx->keys->key_s = false;
		else if (key == KEY_A)
			mlx->keys->key_a = false;
		else if (key == KEY_D)
			mlx->keys->key_d = false;
	}
	return (0);
}

int			deal_mouse(int mousebutton, int x, int y, t_mlx *mlx)
{
	(void)mlx;
	(void)mousebutton;
	if (mlx->screen->menu == true)
	{
		// 35 high
		// from 160 till 510
		if (x >= 350 && x <= 750)
		{
			if (y >= 475 && y < 510)
				exit_x(NULL);
			else if (y >= 370 && y < 405)
				system("open README.md");
		}
	}
	return (0);
}