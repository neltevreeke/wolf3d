/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sounds.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 16:02:25 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 19:43:33 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "../includes/xlm.h"
#include "../includes/screen.h"
#include "../includes/player.h"

/*
**	Plays in-game gunshot sound
*/

void		play_gunshot_sound(t_mlx *mlx)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		system("afplay -v 0.1 src/sound_fx/gun_shot_2.mp3");
		exit(EXIT_SUCCESS);
	}
	mlx->player->ammo -= 1;
	mlx->screen->gunstate = 1;
}

/*
**	Plays in-game footstep sound
*/

void		play_footstep_sound(t_mlx *mlx)
{
	int		status;

	if (mlx->player->step_pid == 0
	|| waitpid(mlx->player->step_pid, &status, WNOHANG) != 0)
	{
		mlx->player->step_pid = fork();
		if (mlx->player->step_pid == 0)
		{
			system("afplay -v 0.8 src/sound_fx/voetstappen.wav");
			exit(EXIT_SUCCESS);
		}
	}
}
