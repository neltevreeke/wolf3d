/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyboard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 14:54:49 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/24 17:39:57 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../libft/libft.h"

#include "../includes/xlm.h"
#include "../includes/keys.h"
#include "../includes/error.h"
#include "../includes/screen.h"
#include "../includes/game_states.h"

/*
**	Sets the states of keys on key press
*/

int			deal_key_press(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (key == KEY_M)
		switch_game_state(mlx);
	else if (mlx->screen->main_game == true)
	{
		if (key == KEY_W || key == KEY_UP)
			mlx->keys->key_w = true;
		else if (key == KEY_S || key == KEY_DOWN)
			mlx->keys->key_s = true;
		else if (key == KEY_A || key == KEY_LEFT)
			mlx->keys->key_a = true;
		else if (key == KEY_D || key == KEY_RIGHT)
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
		if (key == KEY_W || key == KEY_UP)
			mlx->keys->key_w = false;
		else if (key == KEY_S || key == KEY_DOWN)
			mlx->keys->key_s = false;
		else if (key == KEY_A || key == KEY_LEFT)
			mlx->keys->key_a = false;
		else if (key == KEY_D || key == KEY_RIGHT)
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
