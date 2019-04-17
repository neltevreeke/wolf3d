/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 14:35:19 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/17 12:02:01 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	**init_textures_data(t_textures *textures)
{
	char	**texture_data;
	int		i;

	i = 0;
	texture_data = (char**)malloc(sizeof(char*) * textures->amount_textures);
	if (!texture_data)
		exit_failure_errno();
	while (i < textures->amount_textures - 1)
	{
		texture_data[i] = mlx_get_data_addr(textures->tex_arr[i], &textures->bits_per_pixel[i], &textures->size_line[i], &textures->endian[i]);
		i++;
	}
	return (texture_data);
}

t_textures	*init_textures(t_mlx *mlx)
{
	int			width;
	t_textures	*textures;

	width = 128;
	textures = MEM(t_textures);
	if (!textures)
		exit_failure_errno();
	textures->tex_arr = (void**)malloc(sizeof(void*) * 4);
	textures->endian = (int*)malloc(sizeof(int) * 4);
	textures->size_line = (int*)malloc(sizeof(int) * 4);
	textures->bits_per_pixel = (int*)malloc(sizeof(int) * 4);
	textures->amount_textures = 4;
	textures->tex_arr[0] = mlx_xpm_file_to_image(MLX_PTR, "textures/wall_29.xpm", &width, &width);
	textures->tex_arr[1] = mlx_xpm_file_to_image(MLX_PTR, "textures/wall_36.xpm", &width, &width);
	textures->tex_arr[2] = mlx_xpm_file_to_image(MLX_PTR, "textures/wall_03.xpm", &width, &width);
	textures->tex_arr[3] = mlx_xpm_file_to_image(MLX_PTR, "textures/wall_32.xpm", &width, &width);
	textures->texture_data = init_textures_data(textures);
	return (textures);
}

t_map	*init_map(char *filename, t_mlx *mlx)
{
	t_map	*map;

	map = MEM(t_map);
	if (!map)
		exit_failure_errno();
	malloc_map(map, filename);
	fill_map(map, filename);
	map->textures = init_textures(mlx);
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
	player->posx = 15.5;
	player->posy = 3.5;
	player->dirx = 0.5;
	player->diry = 0.5;
	player->planex = -0.5;
	player->planey = 0.5;
	return (player);
}

t_mlx	*init_program(char *filename)
{
	t_mlx *mlx;

	mlx = init_mlx();
	mlx->map = init_map(filename, mlx);
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
