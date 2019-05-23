/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_state.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/21 13:12:10 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 19:46:13 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../includes/xlm.h"
#include "../includes/screen.h"

int			exit_x(void *nul)
{
	(void)nul;
	exit(EXIT_SUCCESS);
}

void		switch_game_state(t_mlx *mlx)
{
	if (mlx->screen->main_game == true)
	{
		mlx->screen->main_game = false;
		mlx->screen->menu = true;
	}
	else if (mlx->screen->menu == true)
	{
		mlx->screen->main_game = true;
		mlx->screen->menu = false;
	}
}
