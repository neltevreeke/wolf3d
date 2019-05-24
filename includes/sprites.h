/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 14:53:06 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/24 17:25:13 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# define AMOUNT_SPRITES 24
# define MAX_SPRITES 999
# define AMMO_SPRITE -18
# define FULLHEAL_SPRITE -17
# define HEAL_SPRITE -16
# define WIDTH 1000

typedef struct s_mlx	t_mlx;

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

typedef struct	s_spritecast
{
	int			sprite_order[MAX_SPRITES];
	int			sprite_distance[MAX_SPRITES];
	int			frunk;
	int			amount;
	int			sprite_screen_x;
	int			sprite_height;
	int			sprite_width;
	int			draw_start_x;
	int			draw_start_y;
	int			draw_end_x;
	int			draw_end_y;
	int			sprite_texture;
	int			stripe;
	int			texture_x;
	int			texture_y;
	double		sprite_x;
	double		sprite_y;
	double		transform_x;
	double		transform_y;
	double		inverse;
}				t_spritecast;

t_sprites		*init_sprites(t_mlx *mlx);
void			sprites_to_img(t_mlx *mlx);
void			determine_sprite_dimensions(
					t_mlx *mlx, t_spritecast *spritecast, int i);
void			determine_draw_start_end(t_spritecast *spritecast);
void			sort_sprites(t_spritecast *spritecast);

#endif
