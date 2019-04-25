/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wolf3d.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 14:13:17 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/25 14:17:19 by nvreeke       ########   odam.nl         */
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
# define WIDTH 1000
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
**	Map struct
*/

typedef struct	s_map
{
	int			**level;
	int			size_x;
	int			size_y;
	t_textures	*textures;
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
}				t_player;

/*
**	MLX struct
*/

typedef struct	s_mlx
{
	void		*init;
	void		*win;
	void		*img;
	char		*data_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
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

void	pixel_to_img(t_mlx *mlx, int px, int py, int color);

/*
**	UI functions
*/

void			put_ui(t_mlx *mlx, char *str);

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
void 		   create_image(t_mlx *mlx);

#endif
