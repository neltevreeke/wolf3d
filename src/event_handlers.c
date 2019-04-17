/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   event_handlers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 12:06:06 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/17 18:25:45 by nvreeke       ########   odam.nl         */
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

void		put_menu(t_mlx *mlx)
{
	mlx_string_put(mlx->init, mlx->win, 200, 200, 0xFFFFFF, "DIT IS HET MENU");
}

void		check_player_move(t_mlx *mlx)
{
	if (mlx->keys->key_w == true)
	{
		// if(mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 - 0.15)] == 1
		// || mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 - 0.15)] == 1
		// || mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 + 0.15)] == 1
		// || mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5 + 0.15)] == 1)
		// {
		// 	if (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5)] == 0
		// 	|| mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx + mlx->player->dirx / 5)] == 0)
		// 		mlx->player->posx -= mlx->player->dirx / 5;
		// 	if (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5)][(int)(mlx->player->posx + mlx->player->dirx / 5 - 0.15)] == 0
		// 	|| mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5)][(int)(mlx->player->posx + mlx->player->dirx / 5 + 0.15)] == 0)
		// 		mlx->player->posy -= mlx->player->diry / 5;
		// }
		// else
		// {
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
		// }
	}
	if (mlx->keys->key_s == true)
	{
		// if(mlx->map->level[(int)(mlx->player->posy - mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx - mlx->player->dirx / 5 - 0.15)] == 1
		// || mlx->map->level[(int)(mlx->player->posy - mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx - mlx->player->dirx / 5 - 0.15)] == 1
		// || mlx->map->level[(int)(mlx->player->posy - mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx - mlx->player->dirx / 5 + 0.15)] == 1
		// || mlx->map->level[(int)(mlx->player->posy - mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx - mlx->player->dirx / 5 + 0.15)] == 1)
		// {
		// 	if (mlx->map->level[(int)(mlx->player->posy - mlx->player->diry / 5 - 0.15)][(int)(mlx->player->posx - mlx->player->dirx / 5)] == 1
		// 	|| mlx->map->level[(int)(mlx->player->posy - mlx->player->diry / 5 + 0.15)][(int)(mlx->player->posx - mlx->player->dirx / 5)] == 1)
		// 		mlx->player->posx -= mlx->player->dirx / 5;
		// 	if (mlx->map->level[(int)(mlx->player->posy - mlx->player->diry / 5)][(int)(mlx->player->posx - mlx->player->dirx / 5 - 0.15)] == 1
		// 	|| mlx->map->level[(int)(mlx->player->posy - mlx->player->diry / 5)][(int)(mlx->player->posx - mlx->player->dirx / 5 + 0.15)] == 1)
		// 		mlx->player->posy -= mlx->player->diry / 5;
		// }
		// else
		// {
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
		// }
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
		put_menu(mlx);
	else if (key == KEY_W)
		mlx->keys->key_w = true;
	else if (key == KEY_S)
		mlx->keys->key_s = true;
	else if (key == KEY_A)
		mlx->keys->key_a = true;
	else if (key == KEY_D)
		mlx->keys->key_d = true;
	return (0);
}

int			deal_key_release(int key, t_mlx *mlx)
{
	if (key == KEY_W)
		mlx->keys->key_w = false;
	else if (key == KEY_S)
		mlx->keys->key_s = false;
	else if (key == KEY_A)
		mlx->keys->key_a = false;
	else if (key == KEY_D)
		mlx->keys->key_d = false;
	return (0);
}

int			deal_mouse(int mousebutton, t_mlx *mlx)
{
	(void)mlx;
	(void)mousebutton;
	return (0);
}