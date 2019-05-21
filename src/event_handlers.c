/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   event_handlers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 12:06:06 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/21 13:25:39 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			exit_x(void *nul)
{
	(void)nul;
	exit(EXIT_SUCCESS);
}

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

static void	deal_game_clicks(t_mlx *mlx)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		system("afplay -v 0.1 src/sound_fx/gun_shot_2.mp3");
		exit(EXIT_SUCCESS);
	}
	mlx->player->ammo -= 1;
	mlx->screen->gunstate = 1;
}

static void	deal_menu_clicks(int x, int y, t_mlx *mlx)
{
	if (x >= 350 && x <= 750)
	{
		if (y >= 265 && y < 300)
		{
			switch_game_state(mlx);
			load_game(mlx);
		}
		else if (y >= 300 && y < 335)
		{
			switch_game_state(mlx);
			save_game(mlx);
		}
		else if (y >= 370 && y < 405)
			system("open README.md");
		else if (y >= 440 && y < 475)
			switch_game_state(mlx);
		else if (y >= 475 && y < 510)
			exit_x(NULL);
	}
}

int			deal_mouse(int mousebutton, int x, int y, t_mlx *mlx)
{
	if (mlx->screen->main_game == true)
	{
		if (mousebutton == 1 && mlx->player->ammo > 0)
			deal_game_clicks(mlx);
	}
	else if (mlx->screen->menu == true)
		deal_menu_clicks(x, y, mlx);
	return (0);
}
