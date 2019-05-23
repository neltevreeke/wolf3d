/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 15:53:29 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 14:57:11 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "../includes/xlm.h"
#include "../includes/map.h"
#include "../includes/sprites.h"

/*
**	Initializes Map
*/

t_map		*init_map(char *filename, t_mlx *mlx)
{
	t_map	*map;

	map = MEM(t_map);
	if (!map)
		exit_failure_errno();
	malloc_map(map, filename);
	fill_map(map, filename);
	map->textures = init_textures(mlx);
	map->sprites = init_sprites(mlx);
	return (map);
}
