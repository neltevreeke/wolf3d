/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   xlm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 13:08:16 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 14:45:21 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef XLM_H
# define XLM_H

/*
**	Standard defines
*/

# define MEM(x) (x*)ft_memalloc(sizeof(x))
# define MLX_PTR mlx->init
# define WIN_PTR mlx->win
# define IMG_PTR mlx->img
# define MENU_PTR mlx->menu
# define IMG_ADD mlx->data_addr
# define UI_PTR mlx->ui
# define UI_ADD mlx->ui_data_addr

/*
**	Dimension defines
*/

# define WIDTH 1000
# define REAL_WIDTH 1200
# define HEIGHT 600
# define THREAD_AMOUNT 5

typedef struct s_map	t_map;
typedef struct s_keys	t_keys;
typedef struct s_screen	t_screen;
typedef struct s_player	t_player;

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

#endif
