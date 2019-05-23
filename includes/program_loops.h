/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   program_loops.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 19:29:39 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 20:07:46 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_LOOPS_H
# define PROGRAM_LOOPS_H

typedef struct s_mlx	t_mlx;

void			event_hooks(t_mlx *mlx);
int				loop_program(t_mlx *mlx);

#endif
