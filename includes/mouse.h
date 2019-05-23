/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 14:47:50 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 20:07:54 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOUSE_H
# define MOUSE_H

# define BTN_LEFT 1
# define BTN_RIGHT 2
# define BTN_MID 3
# define BTN_UP 4
# define BTN_DOWN 5

typedef struct s_mlx	t_mlx;

int		deal_mouse(int mousebutton, int x, int y, t_mlx *mlx);

#endif
