/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wolf3d.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 14:13:17 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/22 17:55:45 by nvreeke       ########   odam.nl         */
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
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <unistd.h>

/*
***********************************************************	Defines
*/

/*
**	Standard defines
*/

# define MEM(x) (x*)ft_memalloc(sizeof(x))
# define MLX_PTR mlx->init
# define WIN_PTR mlx->win
# define IMG_PTR mlx->img
# define MENU_PTR mlx->menu
# define IMG_ADD mlx->data_addr
# define MINIMAP_PTR mlx->minimap
# define MINIMAP_ADD mlx->mm_data_addr
# define UI_PTR mlx->ui
# define UI_ADD mlx->ui_data_addr
# define WIDTH 1000
# define REAL_WIDTH 1200
# define HEIGHT 600
# define THREAD_AMOUNT 5

/*
**	Key & mouse defines
*/

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_D 2
# define KEY_S 1
# define KEY_SPA 49
# define KEY_P 35

# define BTN_LEFT 1
# define BTN_RIGHT 2
# define BTN_MID 3
# define BTN_UP 4
# define BTN_DOWN 5

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

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef enum	e_bool
{
	true = 1,
	false = 0
}				t_bool;

/*
**	keys struct
*/

typedef struct	s_keys
{
	t_bool		key_w;
	t_bool		key_a;
	t_bool		key_s;
	t_bool		key_d;
	t_bool		key_space;
	t_bool		key_ctrl;
}				t_keys;

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
**	sprite struct
*/

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

/*
**	Map struct
*/

typedef struct	s_map
{
	int			**level;
	int			size_x;
	int			size_y;
	t_textures	*textures;
	t_sprites	*sprites;
}				t_map;

/*
**	Raycasting struct
*/

typedef struct	s_casting
{
	int			hit;
	int			side;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			lineheight;
	int			texture_x;
	int			texture_y;
	double		topbot_wall_x;
	double		topbot_wall_y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		per_wall_dist;
	double		wall_x;
}				t_casting;

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
**	MLX struct
*/

typedef struct	s_mlx
{
	void		*init;
	void		*win;
	void		*img;
	void		*menu;
	void		*ui;
	void		*minimap;
	char		*data_addr;
	char		*mm_data_addr;
	char		*ui_data_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			mm_bits_per_pixel;
	int			mm_size_line;
	int			mm_endian;
	int			ui_bits_per_pixel;
	int			ui_size_line;
	int			ui_endian;
	int			max_x;
	int			cur_x;
	t_map		*map;
	t_keys		*keys;
	t_screen	*screen;
	t_player	*player;
}				t_mlx;

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
**	Keyboard functions
*/

t_keys			*init_keys(void);
int				deal_key_press(int key, t_mlx *mlx);
int				deal_key_release(int key, t_mlx *mlx);

/*
**	Mouse functions
*/

int				deal_mouse(int mousebutton, int x, int y, t_mlx *mlx);

/*
**	Player functions
*/

t_player		*init_player(void);
void			rotate(t_mlx *mlx);
void			check_player_move(t_mlx *mlx);
void			check_player_interaction(t_mlx *mlx);

/*
**	Map functions
*/

int				open_file(char *filename, int mode);
void			fill_map(t_map *map, char *filename);
void			malloc_map(t_map *map, char *filename);
t_map			*init_map(char *filename, t_mlx *mlx);

/*
**	Minimap functions
*/

void			create_minimap(t_mlx *mlx);

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
void			create_image(t_mlx *mlx);

/*
**	Print functions
*/

void			print_walls(t_mlx *mlx, t_casting casting);
void			sprites_to_img(t_mlx *mlx);
void			pixel_to_img(t_mlx *mlx, int px, int py, int color);

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
**	Raycasting functions
*/

void			print_roof(t_mlx *mlx, t_casting casting);
void			print_floor(t_mlx *mlx, t_casting casting);
void			print_wall(t_mlx *mlx, t_casting casting);
void			determine_step_side(t_mlx *mlx, t_casting *casting);
void			determine_side_hit(t_mlx *mlx, t_casting *casting);
void			determine_distance(t_mlx *mlx, t_casting *casting);
void			determine_wall_x(t_mlx *mlx, t_casting *casting);
void			determine_texture_x(t_casting *casting);
void			determine_topbot(t_casting *casting);
void			determine_begin_end(t_casting casting, int *begin, int *end);

/*
**	Sprite functions
*/

t_sprites		*init_sprites(t_mlx *mlx);
void			sprites_to_img(t_mlx *mlx);
void			determine_sprite_dimensions(t_mlx *mlx, t_spritecast *spritecast, int i);
void			determine_draw_start_end(t_spritecast *spritecast);
void			sort_sprites(t_spritecast *spritecast);

/*
**	Screen functions
*/

t_screen		*init_screen(t_mlx *mlx);

#endif
