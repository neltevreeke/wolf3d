/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 14:55:01 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 19:48:05 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../includes/xlm.h"
#include "../includes/menu.h"
#include "../includes/sound.h"
#include "../includes/screen.h"
#include "../includes/player.h"
#include "../includes/game_states.h"

/*
**	Deals with clicks in the menu
*/

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

/*
**	Recognizes whether the clicks are game or menu clicks
*/

int			deal_mouse(int mousebutton, int x, int y, t_mlx *mlx)
{
	if (mlx->screen->main_game == true)
	{
		if (mousebutton == 1 && mlx->player->ammo > 0)
			play_gunshot_sound(mlx);
	}
	else if (mlx->screen->menu == true)
		deal_menu_clicks(x, y, mlx);
	return (0);
}
