/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 19:21:43 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 20:08:46 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

typedef struct s_mlx	t_mlx;

int				exit_x(void *nul);
void			load_game(t_mlx *mlx);
void			save_game(t_mlx *mlx);

#endif
