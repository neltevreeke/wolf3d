/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 14:53:06 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 14:56:21 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

#include "xlm.h"

typedef struct s_mlx	t_mlx;
typedef struct s_spritecast	t_spritecast;

typedef struct	s_sprites
{
	void		**spr_arr;
	char		**sprite_data;
	int			*bits_per_pixel;
	int			*size_line;
	int			*endian;
	double		*x;
	double		*y;
	int			sprite;
	double		zbuffer[WIDTH];
}				t_sprites;

t_sprites		*init_sprites(t_mlx *mlx);
void			sprites_to_img(t_mlx *mlx);
void			determine_sprite_dimensions(t_mlx *mlx, t_spritecast *spritecast, int i);
void			determine_draw_start_end(t_spritecast *spritecast);
void			sort_sprites(t_spritecast *spritecast);

#endif