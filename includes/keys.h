/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 13:37:34 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 14:46:30 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_D 2
# define KEY_S 1
# define KEY_SPA 49
# define KEY_P 35

# include "bool.h"

typedef struct s_mlx t_mlx;

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
**	Keyboard functions
*/

t_keys			*init_keys(void);
int				deal_key_press(int key, t_mlx *mlx);
int				deal_key_release(int key, t_mlx *mlx);

#endif
