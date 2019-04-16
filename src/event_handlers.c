/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   event_handlers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 12:06:06 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/16 18:55:18 by jvisser       ########   odam.nl         */
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

int			deal_key(int key, t_mlx *mlx)
{
	if (KEY_ESC == key)
		put_menu(mlx);
	else if (key == KEY_W)
	{
		if (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry / 5)][(int)(mlx->player->posx + mlx->player->dirx / 5)] == 0)
		{
			mlx->player->posx += mlx->player->dirx / 5;
			mlx->player->posy += mlx->player->diry / 5;
		}
	}
	else if (key == KEY_S)
	{
		if (mlx->map->level[(int)(mlx->player->posy - mlx->player->diry / 5)][(int)(mlx->player->posx - mlx->player->dirx / 5)] == 0)
		{
			mlx->player->posx -= mlx->player->dirx / 5;
			mlx->player->posy -= mlx->player->diry / 5;
		}
	}
	else if (key == KEY_A)
	{
		double x_save = mlx->player->dirx;
		mlx->player->dirx = x_save * cos(-2 * M_PI / 180) - mlx->player->diry * sin(-2 * M_PI / 180);
		mlx->player->diry = x_save * sin(-2 * M_PI / 180) + mlx->player->diry * cos(-2 * M_PI / 180);
		x_save = mlx->player->planex;
		mlx->player->planex = x_save * cos(-2 * M_PI / 180) - mlx->player->planey * sin(-2 * M_PI / 180);
		mlx->player->planey = x_save * sin(-2 * M_PI / 180) + mlx->player->planey * cos(-2 * M_PI / 180);
	}
	else if (key == KEY_D)
	{
		double x_save = mlx->player->dirx;
		mlx->player->dirx = x_save * cos(2 * M_PI / 180) - mlx->player->diry * sin(2 * M_PI / 180);
		mlx->player->diry = x_save * sin(2 * M_PI / 180) + mlx->player->diry * cos(2 * M_PI / 180);
		x_save = mlx->player->planex;
		mlx->player->planex = x_save * cos(2 * M_PI / 180) - mlx->player->planey * sin(2 * M_PI / 180);
		mlx->player->planey = x_save * sin(2 * M_PI / 180) + mlx->player->planey * cos(2 * M_PI / 180);
	}
	return (0);
}

int			deal_mouse(int mousebutton, t_mlx *mlx)
{
	(void)mlx;
	(void)mousebutton;
	return (0);
}