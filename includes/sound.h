/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sound.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 19:05:04 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 19:06:08 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_H
# define SOUND_H

typedef struct s_mlx	t_mlx;

void			play_gunshot_sound(t_mlx *mlx);
void			play_footstep_sound(t_mlx *mlx);

#endif