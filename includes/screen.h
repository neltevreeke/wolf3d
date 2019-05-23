/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   screen.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 18:59:41 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 20:07:31 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_H
# define SCREEN_H

# include "bool.h"

typedef struct s_mlx	t_mlx;

typedef struct	s_screen
{
	t_bool		main_game;
	t_bool		menu;
	t_bool		wall_side_textures;
	void		**gun_img;
	int			gunstate;
	void		*save_img;
	double		save_time;
}				t_screen;

/*
**	Screen functions
*/

t_screen		*init_screen(t_mlx *mlx);

#endif
