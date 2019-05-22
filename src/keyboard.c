/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyboard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 14:54:49 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/22 16:10:03 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	Sets the states of keys on key press
*/

int			deal_key_press(int key, t_mlx *mlx)
{
	if (KEY_ESC == key)
		switch_game_state(mlx);
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
		else if (key == KEY_P)
		{
			if (mlx->screen->wall_side_textures == true)
				mlx->screen->wall_side_textures = false;
			else
				mlx->screen->wall_side_textures = true;
		}
	}
	return (0);
}

/*
**	Sets the states of keys on key release
*/

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

/*
**	Initializes Keys for events
*/

t_keys		*init_keys(void)
{
	t_keys	*keys;

	keys = MEM(t_keys);
	if (!keys)
		exit_failure_errno();
	keys->key_w = false;
	keys->key_a = false;
	keys->key_s = false;
	keys->key_d = false;
	keys->key_space = false;
	keys->key_ctrl = false;
	return (keys);
}
