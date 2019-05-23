/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 14:22:37 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 20:07:37 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <sys/types.h>

typedef struct s_mlx	t_mlx;

/*
**	player struct
*/

typedef struct	s_player
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		ms;
	int			ammo;
	int			hp;
	pid_t		step_pid;
}				t_player;

/*
**	Player functions
*/

t_player		*init_player(void);
void			rotate(t_mlx *mlx);
void			check_player_move(t_mlx *mlx);
void			check_player_interaction(t_mlx *mlx);

#endif
