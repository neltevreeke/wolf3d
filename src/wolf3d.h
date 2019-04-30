/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wolf3d.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 14:13:17 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/30 17:37:09 by jvisser       ########   odam.nl         */
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
# define AMOUNT_TEXTURES 39

/*
***********************************************************	Structs
*/

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

typedef struct	s_screen
{
	t_bool		main_game;
	t_bool		menu;
	void**		gun_img;
	int			gunstate;
	void*		save_img;
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
	int			amount_textures;
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
	double		Zbuffer[WIDTH];
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
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		per_wall_dist;
}				t_casting;

/*
**	player struct
*/

typedef struct	s_player
{
	double		posx; // Starting x of player
	double		posy; // Starting y of player
	double		dirx; // Viewing direction x
	double		diry; // Viewing direction y
	double		planex; // Viewing width x
	double		planey; // Viewing width y
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


void	sprites_to_img(t_mlx *mlx);
/*
***********************************************************	Prototypes
*/

void			pixel_to_img(t_mlx *mlx, int px, int py, int color);
void			sort_sprites(int *spriteorder, int *spritedistance, int amount);

/*
**	UI functions
*/

void			put_gun_to_window(t_mlx *mlx);
void			create_ui(t_mlx *mlx, char *str);

/*
**	Event_handler functions
*/

void			ui_handlers(t_mlx *mlx);
int				exit_x(void *nul);
void			check_player_move(t_mlx *mlx);
int				deal_key_press(int key, t_mlx *mlx);
int				deal_key_release(int key, t_mlx *mlx);
int				deal_mouse(int mousebutton, int x, int y, t_mlx *mlx);
void			rotate(t_mlx *mlx);

/*
**	Event_handler functions
*/

void			fill_map(t_map *map, char *filename);
void			malloc_map(t_map *map, char *filename);

/*
**	Fps meter functions
*/

double			get_cur_time(void);
char			*get_fps(char *str);

/*
**	Fps meter functions
*/

void			no_param(void);
void			exit_failure_errno(void);
void			create_image(t_mlx *mlx);

/*
**	print map functions
*/

void			print_walls(t_mlx *mlx, t_casting casting);

#endif
