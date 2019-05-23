/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wolf3d.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 14:13:17 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 14:56:39 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

/*
***********************************************************	Includes
*/

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <sys/time.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include <unistd.h>

# include "../includes/xlm.h"
# include "../includes/bool.h"

/*
***********************************************************	Defines
*/

/*
**	Pistol defines
*/

# define AMOUNT_GUNS 5
# define IMG_IDLE_GUN mlx->screen->gun_img[0]
# define IMG_ACTION_GUN_1 mlx->screen->gun_img[1]
# define IMG_ACTION_GUN_2 mlx->screen->gun_img[2]
# define IMG_ACTION_GUN_3 mlx->screen->gun_img[3]
# define IMG_ACTION_GUN_4 mlx->screen->gun_img[4]

/*
**	Sprite, texture defines
*/

# define AMOUNT_SPRITES 24
# define AMOUNT_TEXTURES 41
# define MAX_SPRITES 99
# define AMMO_SPRITE -18
# define FULLHEAL_SPRITE -17
# define HEAL_SPRITE -16

/*
***********************************************************	Structs
*/

typedef struct s_mlx t_mlx;

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

/*
**	Interface / menu struct
*/

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
**	texture struct
*/

typedef struct	s_textures
{
	void		**tex_arr;
	char		**texture_data;
	int			*bits_per_pixel;
	int			*size_line;
	int			*endian;
}				t_textures;

/*
**	Spritecasting struct
*/

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


/*
***********************************************************	Prototypes
*/

/*
**	Loop functions
*/

void			event_hooks(t_mlx *mlx);
int				loop_program(t_mlx *mlx);

/*
**	Menu functions
*/

int				exit_x(void *nul);
void			load_game(t_mlx *mlx);
void			save_game(t_mlx *mlx);

/*
**	UI functions
*/

void			put_gun_to_window(t_mlx *mlx);
void			create_ui(t_mlx *mlx, char *str);
void			crosshair_to_img(t_mlx *mlx);

/*
**	Fps meter functions
*/

double			get_cur_time(void);
char			*get_fps(char *str);

/*
**	Error functions
*/

void			no_param(void);
void			exit_failure_errno(void);

/*
**	Sound functions
*/

void			play_gunshot_sound(t_mlx *mlx);
void			play_footstep_sound(t_mlx *mlx);

/*
**	Game state functions
*/

void			switch_game_state(t_mlx *mlx);

/*
**	Texture functions
*/

t_textures		*init_textures(t_mlx *mlx);

/*
**	Screen functions
*/

t_screen		*init_screen(t_mlx *mlx);

#endif
