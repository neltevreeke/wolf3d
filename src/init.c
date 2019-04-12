/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 14:35:19 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/12 18:14:25 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_mlx	*init_program(void)
{
	t_mlx *mlx;

	mlx = MEM(t_mlx);
	mlx->init = mlx_init();
	mlx->win = mlx_new_window(mlx->init, WIDTH, HEIGHT, "Jelle en Neltes nazi steekpartij");
	mlx->img = mlx_new_image(mlx->init, WIDTH, HEIGHT);
	mlx->data_addr = mlx_get_data_addr(mlx->img, &(mlx->bits_per_pixel), &(mlx->size_line), &(mlx->endian));

	return (mlx);
}

int		loop_program(t_mlx *mlx)
{
	char *str;

	str = NULL;
	str = get_fps(str);
	ft_bzero(mlx->data_addr, HEIGHT * WIDTH * (mlx->bits_per_pixel / 8));
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
	put_ui(mlx, str);
	free(str);
	return (0);
}

void	put_ui(t_mlx *mlx, char *str)
{
	mlx_string_put(mlx->init, mlx->win, WIDTH / 100 * 92, HEIGHT / 100, 0xFFFFFF, "FPS:");
	mlx_string_put(mlx->init, mlx->win, (WIDTH / 100 * 92) + 50, HEIGHT / 100, 0xFFFFFF, str);
}

int		main(void)
{
	t_mlx *mlx;
	
	mlx = init_program();
	loop_program(mlx);
	mlx_loop_hook(mlx->init, loop_program, mlx);
	mlx_loop(mlx->init);
	return (0);
}
