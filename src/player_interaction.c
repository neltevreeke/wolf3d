/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_interaction.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/21 13:05:57 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 19:59:06 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xlm.h"
#include "../includes/map.h"
#include "../includes/player.h"
#include "../includes/sprites.h"

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

static void	player_ammo(t_mlx *mlx)
{
	mlx->player->ammo += 6;
	mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] = 0;
}

static void	player_heal(t_mlx *mlx)
{
	if (mlx->player->hp < 100)
	{
		mlx->player->hp += 5;
		if (mlx->player->hp > 100)
			mlx->player->hp = 100;
		mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] = 0;
	}
}

static void	player_full_heal(t_mlx *mlx)
{
	if (mlx->player->hp < 100)
	{
		mlx->player->hp = 100;
		mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] = 0;
	}
}

void		check_player_interaction(t_mlx *mlx)
{
	if (mlx->map->level[(int)mlx->player->posy]
	[(int)mlx->player->posx] == AMMO_SPRITE)
		player_ammo(mlx);
	else if (mlx->map->level[(int)mlx->player->posy]
	[(int)mlx->player->posx] == HEAL_SPRITE)
		player_heal(mlx);
	else if (mlx->map->level[(int)mlx->player->posy]
	[(int)mlx->player->posx] == FULLHEAL_SPRITE)
		player_full_heal(mlx);
	if (mlx->player->hp <= 0)
		player_respawn(mlx);
}
