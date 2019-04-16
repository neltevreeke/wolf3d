/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   event_handlers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 12:06:06 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/16 13:09:42 by jvisser       ########   odam.nl         */
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
	(void)mlx;
	if (KEY_ESC == key)
		put_menu(mlx);
	else if (key == KEY_W)
		mlx->player->posx += 0.1;
	else if (key == KEY_S)
		mlx->player->posx -= 0.1;
	else if (key == KEY_A)
	{
		mlx->player->dirx += 0.05;
		mlx->player->diry -= 0.05;
	}
	else if (key == KEY_D)
	{
		mlx->player->dirx -= 0.05;
		mlx->player->diry += 0.05;
	}
	return (0);
}

int			deal_mouse(int mousebutton, t_mlx *mlx)
{
	(void)mlx;
	(void)mousebutton;
	return (0);
}