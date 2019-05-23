/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/20 18:04:44 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 19:59:05 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../includes/xlm.h"
#include "../includes/map.h"
#include "../includes/keys.h"
#include "../includes/sound.h"
#include "../includes/player.h"
#include "../includes/sprites.h"

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
