/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   event_handlers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 12:06:06 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/20 19:56:41 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			exit_x(void *nul)
{
	(void)nul;
	exit(EXIT_SUCCESS);
}

void		player_respawn(t_mlx *mlx)
{
	mlx->player->posx = 35.5;
	mlx->player->posy = 56.5;
	mlx->player->dirx = 0.5;
	mlx->player->diry = 0.5;
	mlx->player->planex = -0.5;
	mlx->player->planey = 0.5;
	mlx->player->hp = 100;
}

void		check_player_interaction(t_mlx *mlx)
{
	if (mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] == AMMO_SPRITE)
	{
		mlx->player->ammo += 6;
		mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] = 0;
	}
	else if (mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] == HEAL_SPRITE)
	{
		if (mlx->player->hp < 100)
		{
			mlx->player->hp += 5;
			if (mlx->player->hp > 100)
				mlx->player->hp = 100;
			mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] = 0;
		}
	}
	else if (mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] == FULLHEAL_SPRITE)
	{
		if (mlx->player->hp < 100)
		{
			mlx->player->hp = 100;
			mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] = 0;
		}
	}
	if (mlx->player->hp <= 0)
		player_respawn(mlx);
}

int			deal_key_press(int key, t_mlx *mlx)
{
	if (KEY_ESC == key)
	{
		if (mlx->screen->main_game == false)
		{
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
	int	pid;
	if (mlx->screen->main_game == true)
	{
		if (mousebutton == 1 && mlx->player->ammo > 0)
		{
			pid = fork();
			if (pid == 0)
			{
				system("afplay -v 0.1 src/sound_fx/gun_shot_2.mp3");
				exit(EXIT_SUCCESS);
			}
			mlx->player->ammo -= 1;
			mlx->screen->gunstate = 1;
		}
	}
	else if (mlx->screen->menu == true)
	{
		// 35 high
		// from 160 till 510
		if (x >= 350 && x <= 750)
		{
			if (y >= 265 && y < 300)
			{
				mlx->screen->main_game = true;
				mlx->screen->menu = false;
				load_game(mlx);
			}
			else if (y >= 300 && y < 335)
			{
				mlx->screen->main_game = true;
				mlx->screen->menu = false;
				mlx->screen->save_time = get_cur_time();
				save_game(mlx);
			}
			else if (y >= 370 && y < 405)
				system("open README.md");
			else if (y >= 440 && y < 475)
			{
				mlx->screen->main_game = true;
				mlx->screen->menu = false;
			}
			else if (y >= 475 && y < 510)
				exit_x(NULL);
		}
	}
	return (0);
}