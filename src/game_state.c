/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_state.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/21 13:12:10 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/21 13:14:22 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	switch_game_state(t_mlx *mlx)
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