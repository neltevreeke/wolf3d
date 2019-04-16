/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 14:35:19 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/16 12:58:29 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
/*
**	Rotate Vector:
**	[ cos(a) -sin(a) ]
**	[ sin(a)  cos(a) ]
*/

t_map	*init_map(char *filename)
{
	t_map	*map;
	
	map = MEM(t_map);
	if (!map)
		exit_failure_errno();
	malloc_map(map, filename);
	fill_map(map, filename);
	return(map);
}

t_mlx	*init_mlx(void)
{
	t_mlx	*mlx;

	mlx = MEM(t_mlx);
	if (!mlx)
		exit_failure_errno();
	MLX_PTR = mlx_init();
	WIN_PTR = mlx_new_window(MLX_PTR, WIDTH, HEIGHT, "Wolf3D");
	IMG_PTR = mlx_new_image(MLX_PTR, WIDTH, HEIGHT);
	IMG_ADD = mlx_get_data_addr(IMG_PTR, &(mlx->bits_per_pixel), &(mlx->size_line), &(mlx->endian));
	return(mlx);
}

t_player	*init_player(void)
{
	t_player	*player;

	player = MEM(t_player);
	if (!player)
		exit_failure_errno();
	player->posx = 1.5;
	player->posy = 2.5;
	player->dirx = 0.5;
	player->diry = 0.5;
	player->planex = 0;
	player->planey = 0.66;
	return (player);
}

t_mlx	*init_program(char *filename)
{
	t_mlx *mlx;

	mlx = init_mlx();
	mlx->map = init_map(filename);
	mlx->player = init_player();
	return (mlx);
}

int		loop_program(t_mlx *mlx)
{
	char *fps_str;

	fps_str = NULL;
	fps_str = get_fps(fps_str);
	ft_bzero(IMG_ADD, HEIGHT * WIDTH * (mlx->bits_per_pixel / 8));
	create_image(mlx);
	mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_PTR, 0, 0);
	put_ui(mlx, fps_str);
	free(fps_str);
	return (0);
}

void	put_ui(t_mlx *mlx, char *fps_str)
{
	mlx_string_put(MLX_PTR, WIN_PTR, WIDTH / 100 * 92, HEIGHT / 100, 0xFFFFFF, "FPS:");
	mlx_string_put(MLX_PTR, WIN_PTR, (WIDTH / 100 * 92) + 50, HEIGHT / 100, 0xFFFFFF, fps_str);
}

void	event_hooks(t_mlx *mlx)
{
	mlx_hook(WIN_PTR, 2, 1L << 0, deal_key, mlx);
	mlx_hook(WIN_PTR, 4, 1L << 8, deal_mouse, NULL);
	mlx_hook(WIN_PTR, 17, 1L << 19, exit_x, NULL);
	mlx_loop_hook(MLX_PTR, loop_program, mlx);
	mlx_loop(MLX_PTR);
}

int		main(int ac, char **av)
{
	t_mlx *mlx;

	if (ac != 2)
		no_param();
	mlx = init_program(av[1]);
	loop_program(mlx);
	event_hooks(mlx);
	mlx_loop(MLX_PTR);
	return (0);
}
