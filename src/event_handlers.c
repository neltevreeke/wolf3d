/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   event_handlers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 12:06:06 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/30 18:32:53 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			exit_x(void *nul)
{
	(void)nul;
	exit(EXIT_SUCCESS);
}

void		rotate_left(t_mlx *mlx)
{
	double	x_save;

	x_save = mlx->player->dirx;
	mlx->player->dirx = x_save * cos(-3 * M_PI * 0.0055) - mlx->player->diry * sin(-3 * M_PI * 0.0055);
	mlx->player->diry = x_save * sin(-3 * M_PI * 0.0055) + mlx->player->diry * cos(-3 * M_PI * 0.0055);
	x_save = mlx->player->planex;
	mlx->player->planex = x_save * cos(-3 * M_PI * 0.0055) - mlx->player->planey * sin(-3 * M_PI * 0.0055);
	mlx->player->planey = x_save * sin(-3 * M_PI * 0.0055) + mlx->player->planey * cos(-3 * M_PI * 0.0055);
}

void		rotate_right(t_mlx *mlx)
{
	double	x_save;

	x_save = mlx->player->dirx;
	mlx->player->dirx = x_save * cos(3 * M_PI * 0.0055) - mlx->player->diry * sin(3 * M_PI * 0.0055);
	mlx->player->diry = x_save * sin(3 * M_PI * 0.0055) + mlx->player->diry * cos(3 * M_PI * 0.0055);
	x_save = mlx->player->planex;
	mlx->player->planex = x_save * cos(3 * M_PI * 0.0055) - mlx->player->planey * sin(3 * M_PI * 0.0055);
	mlx->player->planey = x_save * sin(3 * M_PI * 0.0055) + mlx->player->planey * cos(3 * M_PI * 0.0055);
}

void		check_player_move(t_mlx *mlx)
{
	int	status;

	if (mlx->keys->key_w == true)
	{
		double	movex = mlx->player->dirx * mlx->player->ms;	
		double	movey = mlx->player->diry * mlx->player->ms;
		if (mlx->map->level[(int)(mlx->player->posy + mlx->player->diry * mlx->player->ms)][(int)(mlx->player->posx)] == 0
		|| mlx->map->level[(int)(mlx->player->posy + mlx->player->diry * mlx->player->ms)][(int)(mlx->player->posx)] == -18
		|| mlx->map->level[(int)(mlx->player->posy + mlx->player->diry * mlx->player->ms)][(int)(mlx->player->posx)] == -16
		|| mlx->map->level[(int)(mlx->player->posy + mlx->player->diry * mlx->player->ms)][(int)(mlx->player->posx)] == -17)
			mlx->player->posy += movey;
		if (mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx + mlx->player->dirx * mlx->player->ms)] == 0
		|| mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx + mlx->player->dirx * mlx->player->ms)] == -18
		|| mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx + mlx->player->dirx * mlx->player->ms)] == -16
		|| mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx + mlx->player->dirx * mlx->player->ms)] == -17)
			mlx->player->posx += movex;
	}
	if (mlx->keys->key_s == true)
	{
		double	movex = mlx->player->dirx * mlx->player->ms;	
		double	movey = mlx->player->diry * mlx->player->ms;
		if (mlx->map->level[(int)(mlx->player->posy - mlx->player->diry * mlx->player->ms)][(int)(mlx->player->posx)] == 0
		|| mlx->map->level[(int)(mlx->player->posy - mlx->player->diry * mlx->player->ms)][(int)(mlx->player->posx)] == -18
		|| mlx->map->level[(int)(mlx->player->posy - mlx->player->diry * mlx->player->ms)][(int)(mlx->player->posx)] == -16
		|| mlx->map->level[(int)(mlx->player->posy - mlx->player->diry * mlx->player->ms)][(int)(mlx->player->posx)] == -17)
			mlx->player->posy -= movey;
		if (mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx - mlx->player->dirx * mlx->player->ms)] == 0
		|| mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx - mlx->player->dirx * mlx->player->ms)] == -18
		|| mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx - mlx->player->dirx * mlx->player->ms)] == -16
		|| mlx->map->level[(int)(mlx->player->posy)][(int)(mlx->player->posx - mlx->player->dirx * mlx->player->ms)] == -17)
			mlx->player->posx -= movex;
	}
	// 7d160f
	// 500a08
	if ((mlx->keys->key_w == true || mlx->keys->key_s == true) && !(mlx->keys->key_w == true && mlx->keys->key_s == true))
	{
		if (mlx->player->step_pid == 0 || waitpid(mlx->player->step_pid, &status, WNOHANG) != 0)
		{
			mlx->player->step_pid = fork();
			if (mlx->player->step_pid == 0)
			{
				system("afplay -v 0.1 src/sound_fx/Single-footstep-snow.mp3");
				exit(EXIT_SUCCESS);
			}
		}
	}
	if (mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] == -18)
	{
		mlx->player->ammo += 6;
		mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] = 0;
	}
	else if (mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] == -16)
	{
		if (mlx->player->hp < 100)
		{
			mlx->player->hp += 5;
			if (mlx->player->hp > 100)
				mlx->player->hp = 100;
			mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] = 0;
		}
	}
	else if (mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] == -17)
	{
		if (mlx->player->hp < 100)
		{
			mlx->player->hp = 100;
			mlx->map->level[(int)mlx->player->posy][(int)mlx->player->posx] = 0;
		}
	}
	if (mlx->player->hp <= 0)
	{
		mlx->player->posx = 35.5;
		mlx->player->posy = 56.5;
		mlx->player->dirx = 0.5;
		mlx->player->diry = 0.5;
		mlx->player->planex = -0.5;
		mlx->player->planey = 0.5;
		mlx->player->hp = 100;
	}
	if (mlx->keys->key_a == true)
		rotate_left(mlx);
	if (mlx->keys->key_d == true)
		rotate_right(mlx);
}

int			deal_key_press(int key, t_mlx *mlx)
{
	if (KEY_ESC == key)
	{
		mlx_destroy_image(MLX_PTR, IMG_PTR);
		if (mlx->screen->main_game == false)
		{
			IMG_PTR = mlx_new_image(MLX_PTR, WIDTH, HEIGHT);
			IMG_ADD = mlx_get_data_addr(IMG_PTR, &(mlx->bits_per_pixel), &(mlx->size_line), &(mlx->endian));
			mlx->screen->main_game = true;
			mlx->screen->menu = false;
		}
		else
		{
			mlx->screen->main_game = false;
			mlx->screen->menu = true;
		}
	}
	else if (mlx->screen->main_game == true)
	{
		if (key == KEY_W)
			mlx->keys->key_w = true;
		else if (key == KEY_S)
			mlx->keys->key_s = true;
		else if (key == KEY_A)
			mlx->keys->key_a = true;
		else if (key == KEY_D)
			mlx->keys->key_d = true;
	}
	return (0);
}

int			deal_key_release(int key, t_mlx *mlx)
{
	if (mlx->screen->main_game == true)
	{
		if (key == KEY_W)
			mlx->keys->key_w = false;
		else if (key == KEY_S)
			mlx->keys->key_s = false;
		else if (key == KEY_A)
			mlx->keys->key_a = false;
		else if (key == KEY_D)
			mlx->keys->key_d = false;
	}
	return (0);
}

void		load_game(t_mlx *mlx)
{
	int		fd;
	int		ret;
	char	*line;
	char	*s;

	s = "src/gamesaves/save_map";

	fd = open("src/gamesaves/save1", O_RDONLY);
	if (fd < 0)
		exit_failure_errno();
	ret = get_next_line(fd, &line);
	mlx->player->ammo = ft_atoi(line);
	free(line);
	ret = get_next_line(fd, &line);
	mlx->player->dirx = atof(line);
	free(line);
	ret = get_next_line(fd, &line);
	mlx->player->diry = atof(line);
	free(line);
	ret = get_next_line(fd, &line);
	mlx->player->ms = atof(line);
	free(line);
	ret = get_next_line(fd, &line);
	mlx->player->planex = atof(line);
	free(line);
	ret = get_next_line(fd, &line);
	mlx->player->planey = atof(line);
	free(line);
	ret = get_next_line(fd, &line);
	mlx->player->posx = atof(line);
	free(line);
	ret = get_next_line(fd, &line);
	mlx->player->posy = atof(line);
	free(line);
	fill_map(mlx->map, s);
}

void		save_map_state(FILE *save, t_mlx *mlx)
{
	int x;
	int y;

	y = 0;
	while (y < mlx->map->size_y)
	{
		x = 0;
		while (x < mlx->map->size_x)
		{
			fprintf(save, "%d ", mlx->map->level[y][x]);
			x++;
		}
		fprintf(save, "%c", '\n');
		y++;
	}
}

void		save_game(t_mlx	*mlx)
{
	FILE	*save;
	FILE	*save_map;

	save = fopen("src/gamesaves/save1", "w");
	save_map = fopen("src/gamesaves/save_map", "w");
	fprintf(save, "%d\n", mlx->player->ammo);
	fprintf(save, "%lf\n", mlx->player->dirx);
	fprintf(save, "%lf\n", mlx->player->diry);
	fprintf(save, "%lf\n", mlx->player->ms);
	fprintf(save, "%lf\n", mlx->player->planex);
	fprintf(save, "%lf\n", mlx->player->planey);
	fprintf(save, "%lf\n", mlx->player->posx);
	fprintf(save, "%lf\n", mlx->player->posy);
	save_map_state(save_map, mlx);
	fclose(save);
	fclose(save_map);
}

int			deal_mouse(int mousebutton, int x, int y, t_mlx *mlx)
{
	int	pid;
	if (mlx->screen->main_game == true)
	{
		if (mousebutton == 1 && mlx->player->ammo > 0)
		{
			pid = fork();
			if (pid == 0)
			{
				system("afplay -v 0.1 src/sound_fx/gun_shot_2.mp3");
				exit(EXIT_SUCCESS);
			}
			mlx->player->ammo -= 1;
			mlx->screen->gunstate = 1;
		}
	}
	else if (mlx->screen->menu == true)
	{
		// 35 high
		// from 160 till 510
		if (x >= 350 && x <= 750)
		{
			if (y >= 265 && y < 300)
			{
				mlx_destroy_image(MLX_PTR, IMG_PTR);
				IMG_PTR = mlx_new_image(MLX_PTR, WIDTH, HEIGHT);
				IMG_ADD = mlx_get_data_addr(IMG_PTR, &(mlx->bits_per_pixel), &(mlx->size_line), &(mlx->endian));
				mlx->screen->main_game = true;
				mlx->screen->menu = false;
				load_game(mlx);
			}
			else if (y >= 300 && y < 335)
			{
				mlx_destroy_image(MLX_PTR, IMG_PTR);
				IMG_PTR = mlx_new_image(MLX_PTR, WIDTH, HEIGHT);
				IMG_ADD = mlx_get_data_addr(IMG_PTR, &(mlx->bits_per_pixel), &(mlx->size_line), &(mlx->endian));
				mlx->screen->main_game = true;
				mlx->screen->menu = false;
				mlx->screen->save_time = get_cur_time();
				save_game(mlx);
			}
			else if (y >= 370 && y < 405)
				system("open README.md");
			else if (y >= 440 && y < 475)
			{
				mlx_destroy_image(MLX_PTR, IMG_PTR);
				IMG_PTR = mlx_new_image(MLX_PTR, WIDTH, HEIGHT);
				IMG_ADD = mlx_get_data_addr(IMG_PTR, &(mlx->bits_per_pixel), &(mlx->size_line), &(mlx->endian));
				mlx->screen->main_game = true;
				mlx->screen->menu = false;
			}
			else if (y >= 475 && y < 510)
				exit_x(NULL);
		}
	}
	return (0);
}