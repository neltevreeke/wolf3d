/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 14:35:19 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/20 19:57:33 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	fills texture data adress array
*/

char	**init_sprites_data(t_sprites *sprites)
{
	char	**sprite_data;
	int		i;

	i = 0;
	sprite_data = (char**)malloc(sizeof(char*) * AMOUNT_SPRITES);
	if (!sprite_data)
		exit_failure_errno();
	while (i < AMOUNT_SPRITES)
	{
		sprite_data[i] = mlx_get_data_addr(sprites->spr_arr[i], &sprites->bits_per_pixel[i], &sprites->size_line[i], &sprites->endian[i]);
		i++;
	}
	return (sprite_data);
}

/*
**	Initializes sprites
*/

t_sprites	*init_sprites(t_mlx *mlx)
{
	int			i;
	int			width;
	char		*tmp;
	char		*filename;
	t_sprites	*sprites;

	i = 0;
	width = 128;
	sprites = MEM(t_sprites);
	if (!sprites)
		exit_failure_errno();
	sprites->spr_arr = (void**)malloc(sizeof(void*) * AMOUNT_SPRITES);
	sprites->endian = (int*)malloc(sizeof(int) * AMOUNT_SPRITES);
	sprites->size_line = (int*)malloc(sizeof(int) * AMOUNT_SPRITES);
	sprites->bits_per_pixel = (int*)malloc(sizeof(int) * AMOUNT_SPRITES);

	sprites->x = (double*)malloc(sizeof(double) * AMOUNT_SPRITES);
	sprites->y = (double*)malloc(sizeof(double) * AMOUNT_SPRITES);
	while (i < AMOUNT_SPRITES)
	{
		char *num = ft_itoa(i + 1);
		tmp = ft_strjoin("textures/sprites/sprite_", num);
		filename = ft_strjoin(tmp, ".xpm");
		sprites->spr_arr[i] = mlx_xpm_file_to_image(MLX_PTR, filename, &width, &width);
		free(num);
		free(tmp);
		free(filename);
		i++;
	}
	sprites->sprite_data = init_sprites_data(sprites);
	return (sprites);
}

/*
**	fills texture data adress array
*/

char	**init_textures_data(t_textures *textures)
{
	char	**texture_data;
	int		i;

	i = 0;
	texture_data = (char**)malloc(sizeof(char*) * AMOUNT_TEXTURES);
	if (!texture_data)
		exit_failure_errno();
	while (i < AMOUNT_TEXTURES)
	{
		texture_data[i] = mlx_get_data_addr(textures->tex_arr[i], &textures->bits_per_pixel[i], &textures->size_line[i], &textures->endian[i]);
		i++;
	}
	return (texture_data);
}

/*
**	Initializes textures
*/

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
	textures->tex_arr = (void**)malloc(sizeof(void*) * AMOUNT_TEXTURES);
	textures->endian = (int*)malloc(sizeof(int) * AMOUNT_TEXTURES);
	textures->size_line = (int*)malloc(sizeof(int) * AMOUNT_TEXTURES);
	textures->bits_per_pixel = (int*)malloc(sizeof(int) * AMOUNT_TEXTURES);
	while (i < AMOUNT_TEXTURES)
	{
		char *num = ft_itoa(i + 1);
		tmp = ft_strjoin("textures/walls/wall_", num);
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


/*
**	Initializes Map
*/

t_map	*init_map(char *filename, t_mlx *mlx)
{
	t_map	*map;

	map = MEM(t_map);
	if (!map)
		exit_failure_errno();
	malloc_map(map, filename);
	fill_map(map, filename);
	map->textures = init_textures(mlx);
	map->sprites = init_sprites(mlx);
	return(map);
}

/*
**	Initializes MLX
*/

t_mlx	*init_mlx(void)
{
	t_mlx	*mlx;

	mlx = MEM(t_mlx);
	if (!mlx)
		exit_failure_errno();
	MLX_PTR = mlx_init();
	WIN_PTR = mlx_new_window(MLX_PTR, REAL_WIDTH, HEIGHT, "Wolf3D");
	IMG_PTR = mlx_new_image(MLX_PTR, WIDTH, HEIGHT);
	MINIMAP_PTR = mlx_new_image(MLX_PTR, 200, 200);
	IMG_ADD = mlx_get_data_addr(IMG_PTR, &(mlx->bits_per_pixel), &(mlx->size_line), &(mlx->endian));
	MINIMAP_ADD = mlx_get_data_addr(MINIMAP_PTR, &(mlx->mm_bits_per_pixel), &(mlx->mm_size_line), &(mlx->mm_endian));
	UI_PTR = mlx_new_image(MLX_PTR, 200, 400);
	UI_ADD = mlx_get_data_addr(UI_PTR, &(mlx->mm_bits_per_pixel), &(mlx->ui_size_line), &(mlx->ui_endian));
	return(mlx);
}

/*
**	Initializes Player
*/

t_player	*init_player(void)
{
	t_player	*player;

	player = MEM(t_player);
	if (!player)
		exit_failure_errno();
	player->posx = 35.5;
	player->posy = 55.5;
	player->dirx = 0.5;
	player->diry = 0.5;
	player->planex = -0.5;
	player->planey = 0.5;
	player->ms =  0.13;
	player->ammo = 600;
	player->hp = 100;
	return (player);
}

/*
**	Initializes Keys for events
*/

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

/*
**	Initializes window/screen
*/

t_screen	*init_screen(t_mlx *mlx)
{
	int			i;
	int			width;
	char		*tmp;
	char		*filename;
	t_screen	*screen;

	screen = MEM(t_screen);
	screen->main_game = true;
	screen->menu = false;
	screen->gunstate = 0;
	i = 0;
	width = 0;
	screen->save_img = mlx_xpm_file_to_image(MLX_PTR, "textures/ui/saved.xpm", &width, &width);
	screen->gun_img = (void**)malloc(sizeof(void*) * AMOUNT_GUNS);
	while (i < AMOUNT_GUNS)
	{
		char *num = ft_itoa(i + 1);
		tmp = ft_strjoin("textures/pistol/pistol_", num);
		filename = ft_strjoin(tmp, ".xpm");
		screen->gun_img[i] = mlx_xpm_file_to_image(MLX_PTR, filename, &width, &width);
		free(num);
		free(tmp);
		free(filename);
		i++;
	}
	return (screen);
}


/*
**	Initializes menu
*/

/*
**	Initializes program
*/

t_mlx	*init_program(char *filename)
{
	int	x;
	int	y;
	t_mlx *mlx;

	x = 0;
	y = 0;
	mlx = init_mlx();
	mlx->map = init_map(filename, mlx);
	mlx->keys = init_keys();
	mlx->screen = init_screen(mlx);
	mlx->player = init_player();
	MENU_PTR = mlx_xpm_file_to_image(MLX_PTR, "textures/menu3.xpm", &x, &y);
	return (mlx);
}

/*
**	Colors the border for minimap
*/

void	color_border(t_mlx *mlx)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	color = 0x0000FF;
	while (y < 200)
	{
		x = 0;
		while (x < 200)
		{
			if ((y < 5 || y >= 195) || (x < 5 || x >= 195))
			{
				color = mlx_get_color_value(MLX_PTR, color);
				ft_memcpy(MINIMAP_ADD + mlx->mm_size_line * y + x * mlx->mm_bits_per_pixel / 8,
					&color, sizeof(int));
			}
			x++;
		}
		y++;
	}
}

/*
**	Colors the block in the mminimap
*/

void	color_block(t_mlx *mlx, int y, int x, int color)
{
	int	x2;
	int	y2;

	y2 = 0;
	while (y2 < 10)
	{
		x2 = 0;
		while (x2 < 10)
		{
			ft_memcpy(MINIMAP_ADD + mlx->mm_size_line * (y * 10 + y2 + 5) + (x * 10 + x2 + 5) * mlx->mm_bits_per_pixel / 8,
				&color, sizeof(int));
			x2++;
		}
		y2++;
	}
}

/*
**	creates the minimap
*/

	// 7d160f
	// 500a08

void	create_minimap(t_mlx *mlx)
{
	int	y;
	int	x;
	int	mapx;
	int	mapy;

	y = 0;
	mapx = (int)mlx->player->posx;
	mapy = (int)mlx->player->posy;
	ft_bzero(MINIMAP_ADD, sizeof(int) * 200 * 200);
	color_border(mlx);
	while (y < 19)
	{
		x = 0;
		if (mapy - 9 + y >= 0 && mapy - 9 + y < mlx->map->size_y)
		{
			while (x < 19)
			{
				if (mapx - 9 + x >= 0 && mapx - 9 + x < mlx->map->size_x)
				{
					if (mlx->map->level[mapy - 9 + y][mapx - 9 + x] != 0)
					{
						if (mlx->map->level[mapy - 9 + y][mapx - 9 + x] == -18)
							color_block(mlx, y, x, 0x4f74af);
						else if (mlx->map->level[mapy - 9 + y][mapx - 9 + x] == -16)
							color_block(mlx, y, x, 0xff7f7f);
						else if (mlx->map->level[mapy - 9 + y][mapx - 9 + x] == -17)
							color_block(mlx, y, x, 0xff7f7f);
						else if (mlx->map->level[mapy - 9 + y][mapx - 9 + x] > 0)
							color_block(mlx, y, x, 0x707070);
						else
							color_block(mlx, y, x, 0x00ff00);
					}
					if (y == 9 && x == 9)
						color_block(mlx, y, x, 0xff0000);
				}
				x++;
			}
		}
		y++;
	}
}

/*
**	Keeps the program running in an infinite loop
*/

int		loop_program(t_mlx *mlx)
{
	char *fps_str;

	fps_str = NULL;
	fps_str = get_fps(fps_str);
	check_player_move(mlx);
	check_player_interaction(mlx);
	ft_bzero(IMG_ADD, HEIGHT * WIDTH * (mlx->bits_per_pixel / 8));
	if (mlx->screen->main_game == true)
	{
		create_image(mlx);
		create_minimap(mlx);
		mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_PTR, 0, 0);
	}
	else if (mlx->screen->menu == true)
		mlx_put_image_to_window(MLX_PTR, WIN_PTR, MENU_PTR, 0, 0);
	mlx_put_image_to_window(MLX_PTR, WIN_PTR, MINIMAP_PTR, 1000, 0);
	mlx_put_image_to_window(MLX_PTR, WIN_PTR, UI_PTR, 1000, 200);
	if (mlx->screen->save_time > get_cur_time() - 2000)
		mlx_put_image_to_window(MLX_PTR, WIN_PTR, mlx->screen->save_img, 734, 505);
	create_ui(mlx, fps_str);
	if (mlx->screen->main_game == true)
		put_gun_to_window(mlx);
	free(fps_str);
	return (0);
}

/*
**	Sets the right sprite for the gun in the window/screen
*/

void	put_gun_to_window(t_mlx *mlx)
{
	if (mlx->screen->gunstate == 0)
		mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_IDLE_GUN, 244, 88);
	else if (mlx->screen->gunstate > 0)
	{
		if (mlx->screen->gunstate == 1)
			mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_ACTION_GUN_1, 244, 88);
		else if (mlx->screen->gunstate == 2)
			mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_ACTION_GUN_2, 244, 88);
		else if (mlx->screen->gunstate == 3)
			mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_ACTION_GUN_3, 244, 88);
		else if (mlx->screen->gunstate == 4)
			mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_ACTION_GUN_4, 244, 88);
		if (mlx->screen->gunstate == 4)
			mlx->screen->gunstate = 0;
		else
			mlx->screen->gunstate++;
	}
}

/*
**	Puts the UI in the window/screen
*/

void	create_ui(t_mlx *mlx, char *fps_str)
{
	char *ammo;
	char *hp;

	ft_bzero(UI_ADD, sizeof(int) * 400 * 200);
	mlx_string_put(MLX_PTR, WIN_PTR, REAL_WIDTH - 175, 575, 0xFFFFFF, "Fps:");
	mlx_string_put(MLX_PTR, WIN_PTR, REAL_WIDTH - 40, 575, 0xFFFFFF, fps_str);

	ammo = ft_itoa(mlx->player->ammo);

	mlx_string_put(MLX_PTR, WIN_PTR, REAL_WIDTH - 175, 250, 0xFFFFFF, "Ammo:");
	mlx_string_put(MLX_PTR, WIN_PTR, REAL_WIDTH - 40, 250, 0xFFFFFF, ammo);

	hp = ft_itoa(mlx->player->hp);

	mlx_string_put(MLX_PTR, WIN_PTR, REAL_WIDTH - 175, 275, 0xFFFFFF, "Health:");
	mlx_string_put(MLX_PTR, WIN_PTR, REAL_WIDTH - 40, 275, 0xFFFFFF, hp);
	free(ammo);
	free(hp);
}

/*
**	Initializes event handlers
*/

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
