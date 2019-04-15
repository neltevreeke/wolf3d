/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   event_handlers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 12:06:06 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/15 14:10:01 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// void		ui_handlers(int key, t_mlx *mlx)
// {

// }

int			exit_x(void *nul)
{
	(void)nul;
	exit(0);
}

void		put_menu(t_mlx *mlx)
{
	printf("TEST\n");
	mlx_string_put(mlx->init, mlx->win, 200, 200, 0xFFFFFF, "DIT IS HET MENU");
}

int			deal_key(int key, t_mlx *mlx)
{
	// (void)mlx;
	if (KEY_ESC == key)
		put_menu(mlx);
	return (0);
}
