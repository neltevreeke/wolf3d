/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 13:36:56 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 19:31:00 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

/*
**	Map struct
*/

typedef struct s_mlx	t_mlx;
typedef struct s_sprites	t_sprites;
typedef struct s_textures	t_textures;

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct	s_map
{
	int			**level;
	int			size_x;
	int			size_y;
	t_sprites	*sprites;
	t_textures	*textures;
}				t_map;

/*
**	Map functions
*/

int				open_file(char *filename, int mode);
void			fill_map(t_map *map, char *filename);
void			malloc_map(t_map *map, char *filename);
t_map			*init_map(char *filename, t_mlx *mlx);

#endif
