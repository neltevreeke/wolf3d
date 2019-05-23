/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 13:05:23 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 14:26:04 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

typedef struct s_mlx	t_mlx;

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
	int			texture_x;
	int			texture_y;
	double		topbot_wall_x;
	double		topbot_wall_y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		per_wall_dist;
	double		wall_x;
}				t_casting;

/*
**	Raycasting functions
*/

void			create_image(t_mlx *mlx);

/*
**	Raycasting printing functions
*/

void			print_roof(t_mlx *mlx, t_casting casting);
void			print_wall(t_mlx *mlx, t_casting casting);
void			print_floor(t_mlx *mlx, t_casting casting);
void			pixel_to_img(t_mlx *mlx, int px, int py, int color);

/*
**	Raycasting calculation functions
*/

void			determine_topbot(t_casting *casting);
void			determine_texture_x(t_casting *casting);
void			determine_wall_x(t_mlx *mlx, t_casting *casting);
void			determine_side_hit(t_mlx *mlx, t_casting *casting);
void			determine_distance(t_mlx *mlx, t_casting *casting);
void			determine_step_side(t_mlx *mlx, t_casting *casting);
void			determine_begin_end(t_casting casting, int *begin, int *end);

#endif
