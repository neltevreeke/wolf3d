/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wolf3d.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 14:13:17 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/12 18:15:25 by nvreeke       ########   odam.nl         */
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
# define WIDTH 1000
# define HEIGHT 600

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
***********************************************************	Prototypes
*/

/*
**	UI functions
*/

void			put_ui(t_mlx *mlx, char *str);

/*
**	Fps meter functions
*/

double			get_cur_time(void);
char			*get_fps(char *str);


#endif
