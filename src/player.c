/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 15:54:54 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/24 13:17:46 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#include "../includes/xlm.h"
#include "../includes/error.h"
#include "../includes/player.h"

/*
**	Initializes Player
*/

t_player	*init_player(void)
{
	t_player	*player;

	player = MEM(t_player);
	if (!player)
		exit_failure_errno();
	player->posx = 35.5;
	player->posy = 55.5;
	player->dirx = 0.5;
	player->diry = 0.5;
	player->planex = -0.5;
	player->planey = 0.5;
	player->ms = 0.13;
	player->ammo = 12;
	player->hp = 100;
	return (player);
}
