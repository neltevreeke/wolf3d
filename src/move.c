/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/20 18:04:44 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/20 19:59:00 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	rotate_left(t_mlx *mlx)
{
	double	x_save;

	x_save = mlx->player->dirx;
	mlx->player->dirx = x_save * cos(-3 * M_PI * 0.0055)
						- mlx->player->diry * sin(-3 * M_PI * 0.0055);
	mlx->player->diry = x_save * sin(-3 * M_PI * 0.0055)
						+ mlx->player->diry * cos(-3 * M_PI * 0.0055);
	x_save = mlx->player->planex;
	mlx->player->planex = x_save * cos(-3 * M_PI * 0.0055)
						- mlx->player->planey * sin(-3 * M_PI * 0.0055);
	mlx->player->planey = x_save * sin(-3 * M_PI * 0.0055)
						+ mlx->player->planey * cos(-3 * M_PI * 0.0055);
}

static void	rotate_right(t_mlx *mlx)
{
	double	x_save;

	x_save = mlx->player->dirx;
	mlx->player->dirx = x_save * cos(3 * M_PI * 0.0055)
						- mlx->player->diry * sin(3 * M_PI * 0.0055);
	mlx->player->diry = x_save * sin(3 * M_PI * 0.0055)
						+ mlx->player->diry * cos(3 * M_PI * 0.0055);
	x_save = mlx->player->planex;
	mlx->player->planex = x_save * cos(3 * M_PI * 0.0055)
						- mlx->player->planey * sin(3 * M_PI * 0.0055);
	mlx->player->planey = x_save * sin(3 * M_PI * 0.0055)
						+ mlx->player->planey * cos(3 * M_PI * 0.0055);
}

static void	move_forward(t_mlx *mlx)
{
	double	movex;
	double	movey;

	movex = mlx->player->dirx * mlx->player->ms;
	movey = mlx->player->diry * mlx->player->ms;
	if (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry
		* mlx->player->ms)][(int)(mlx->player->posx)] == 0
	|| mlx->map->level[(int)(mlx->player->posy + mlx->player->diry
		* mlx->player->ms)][(int)(mlx->player->posx)] == AMMO_SPRITE
	|| mlx->map->level[(int)(mlx->player->posy + mlx->player->diry
		* mlx->player->ms)][(int)(mlx->player->posx)] == HEAL_SPRITE
	|| mlx->map->level[(int)(mlx->player->posy + mlx->player->diry
		* mlx->player->ms)][(int)(mlx->player->posx)] == FULLHEAL_SPRITE)
		mlx->player->posy += movey;
	if (mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx
		+ mlx->player->dirx * mlx->player->ms)] == 0
	|| mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx
		+ mlx->player->dirx * mlx->player->ms)] == AMMO_SPRITE
	|| mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx
		+ mlx->player->dirx * mlx->player->ms)] == HEAL_SPRITE
	|| mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx
		+ mlx->player->dirx * mlx->player->ms)] == FULLHEAL_SPRITE)
		mlx->player->posx += movex;
}

static void	move_backward(t_mlx *mlx)
{
	double	movex;
	double	movey;

	movex = mlx->player->dirx * mlx->player->ms;
	movey = mlx->player->diry * mlx->player->ms;
	if (mlx->map->level[(int)(mlx->player->posy - mlx->player->diry
		* mlx->player->ms)][(int)(mlx->player->posx)] == 0
	|| mlx->map->level[(int)(mlx->player->posy - mlx->player->diry
		* mlx->player->ms)][(int)(mlx->player->posx)] == AMMO_SPRITE
	|| mlx->map->level[(int)(mlx->player->posy - mlx->player->diry
		* mlx->player->ms)][(int)(mlx->player->posx)] == HEAL_SPRITE
	|| mlx->map->level[(int)(mlx->player->posy - mlx->player->diry
		* mlx->player->ms)][(int)(mlx->player->posx)] == FULLHEAL_SPRITE)
		mlx->player->posy -= movey;
	if (mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx
		- mlx->player->dirx * mlx->player->ms)] == 0
	|| mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx
		- mlx->player->dirx * mlx->player->ms)] == AMMO_SPRITE
	|| mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx
		- mlx->player->dirx * mlx->player->ms)] == HEAL_SPRITE
	|| mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx
		- mlx->player->dirx * mlx->player->ms)] == FULLHEAL_SPRITE)
		mlx->player->posx -= movex;
}

static void	play_footstep_sound(t_mlx *mlx)
{
	int	status;

	if (mlx->player->step_pid == 0
	|| waitpid(mlx->player->step_pid, &status, WNOHANG) != 0)
	{
		mlx->player->step_pid = fork();
		if (mlx->player->step_pid == 0)
		{
			system("afplay -v 0.5 src/sound_fx/voetstappen.wav");
			exit(EXIT_SUCCESS);
		}
	}
}

void		check_player_move(t_mlx *mlx)
{
	if (mlx->keys->key_w == true)
		move_forward(mlx);
	if (mlx->keys->key_s == true)
		move_backward(mlx);
	if ((mlx->keys->key_w == true || mlx->keys->key_s == true)
	&& !(mlx->keys->key_w == true && mlx->keys->key_s == true))
		play_footstep_sound(mlx);
	if (mlx->keys->key_a == true)
		rotate_left(mlx);
	if (mlx->keys->key_d == true)
		rotate_right(mlx);
}
