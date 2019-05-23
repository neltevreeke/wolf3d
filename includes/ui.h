/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 19:17:20 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 20:07:06 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# define AMOUNT_GUNS 5
# define IMG_IDLE_GUN mlx->screen->gun_img[0]
# define IMG_ACTION_GUN_1 mlx->screen->gun_img[1]
# define IMG_ACTION_GUN_2 mlx->screen->gun_img[2]
# define IMG_ACTION_GUN_3 mlx->screen->gun_img[3]
# define IMG_ACTION_GUN_4 mlx->screen->gun_img[4]

typedef struct s_mlx	t_mlx;

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

#endif
