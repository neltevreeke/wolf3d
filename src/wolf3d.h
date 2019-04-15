/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wolf3d.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 14:13:17 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/15 15:52:42 by jvisser       ########   odam.nl         */
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

/*
**	mlx struct
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
}				t_mlx;

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
}				t_player;

typedef struct	s_map
{
	int			**map;
	int			size_x;
	int			size_y;
}				t_map;

/*
***********************************************************	Prototypes
*/

/*
**	UI functions
*/

void			put_ui(t_mlx *mlx, char *str);

/*
**	Event_handler functions
*/

void			ui_handlers(t_mlx *mlx);
int				exit_x(void *nul);
int				deal_key(int key, t_mlx *mlx);
int				deal_mouse(int mousebutton, t_mlx *mlx);

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


#endif
