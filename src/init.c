/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 14:35:19 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/25 13:10:58 by nvreeke       ########   odam.nl         */
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
	while (i < textures->amount_textures)
	{
		texture_data[i] = mlx_get_data_addr(textures->tex_arr[i], &textures->bits_per_pixel[i], &textures->size_line[i], &textures->endian[i]);
		i++;
	}
	return (texture_data);
}

t_textures	*init_textures(t_mlx *mlx)
{
	int			i;
	int			width;
	char		*tmp;
	char		*filename;
	t_textures	*textures;

	i = 0;
	width = 128;
	textures = MEM(t_textures);
	if (!textures)
		exit_failure_errno();
	textures->amount_textures = 38;
	textures->tex_arr = (void**)malloc(sizeof(void*) * textures->amount_textures);
	textures->endian = (int*)malloc(sizeof(int) * textures->amount_textures);
	textures->size_line = (int*)malloc(sizeof(int) * textures->amount_textures);
	textures->bits_per_pixel = (int*)malloc(sizeof(int) * textures->amount_textures);
	while (i < textures->amount_textures)
	{
		char *num = ft_itoa(i + 1);
		tmp = ft_strjoin("textures/wall_", num);
		filename = ft_strjoin(tmp, ".xpm");
		textures->tex_arr[i] = mlx_xpm_file_to_image(MLX_PTR, filename, &width, &width);
		free(num);
		free(tmp);
		free(filename);
		i++;
	}
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
	player->posx = 3.5;
	player->posy = 2.5;
	player->dirx = 0.5;
	player->diry = 0.5;
	player->planex = -0.5;
	player->planey = 0.5;
	player->ms =  0.13;
	return (player);
}

t_keys	*init_keys(void)
{
	t_keys	*keys;

	keys = MEM(t_keys);
	if (!keys)
		exit_failure_errno();
	keys->key_w = false;
	keys->key_a = false;
	keys->key_s = false;
	keys->key_d = false;
	keys->key_space = false;
	keys->key_ctrl = false;
	return (keys);
}

t_screen	*init_screen(void)
{
	t_screen	*screen;

	screen = MEM(t_screen);
	screen->main_game = true;
	screen->menu = false;
	return (screen);
}

t_mlx	*init_program(char *filename)
{
	t_mlx *mlx;

	mlx = init_mlx();
	mlx->map = init_map(filename, mlx);
	mlx->keys = init_keys();
	mlx->screen = init_screen();
	mlx->player = init_player();
	return (mlx);
}

void	create_menu(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	IMG_PTR = mlx_xpm_file_to_image(MLX_PTR, "textures/menu3.xpm", &x, &y);
}

int		loop_program(t_mlx *mlx)
{
	char *fps_str;

	fps_str = NULL;
	fps_str = get_fps(fps_str);
	check_player_move(mlx);
	ft_bzero(IMG_ADD, HEIGHT * WIDTH * (mlx->bits_per_pixel / 8));
	if (mlx->screen->main_game == true)
		create_image(mlx);
	else if (mlx->screen->menu == true)
		create_menu(mlx);
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
	mlx_hook(WIN_PTR, 2, 1L << 0, deal_key_press, mlx);
	mlx_hook(WIN_PTR, 3, 1L << 1, deal_key_release, mlx);
	mlx_hook(WIN_PTR, 4, 1L << 8, deal_mouse, mlx);
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
