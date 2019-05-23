/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 14:35:19 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 19:40:24 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#include "../includes/xlm.h"
#include "../includes/map.h"
#include "../includes/keys.h"
#include "../includes/error.h"
#include "../includes/screen.h"
#include "../includes/player.h"
#include "../includes/minimap.h"
#include "../includes/program_loops.h"

#include "../minilibx_macos/mlx.h"

/*
**	Initializes MLX
*/

t_mlx		*init_mlx(void)
{
	t_mlx	*mlx;

	mlx = MEM(t_mlx);
	if (!mlx)
		exit_failure_errno();
	MLX_PTR = mlx_init();
	WIN_PTR = mlx_new_window(MLX_PTR, REAL_WIDTH, HEIGHT, "Wolf3D");
	IMG_PTR = mlx_new_image(MLX_PTR, WIDTH, HEIGHT);
	MINIMAP_PTR = mlx_new_image(MLX_PTR, 200, 200);
	IMG_ADD = mlx_get_data_addr(IMG_PTR, &(mlx->bits_per_pixel),
				&(mlx->size_line), &(mlx->endian));
	MINIMAP_ADD = mlx_get_data_addr(MINIMAP_PTR, &(mlx->mm_bits_per_pixel),
				&(mlx->mm_size_line), &(mlx->mm_endian));
	UI_PTR = mlx_new_image(MLX_PTR, 200, 400);
	UI_ADD = mlx_get_data_addr(UI_PTR, &(mlx->mm_bits_per_pixel),
				&(mlx->ui_size_line), &(mlx->ui_endian));
	return (mlx);
}

/*
**	Initializes program
*/

t_mlx		*init_program(char *filename)
{
	int		x;
	int		y;
	t_mlx	*mlx;

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

int			main(int ac, char **av)
{
	t_mlx	*mlx;

	if (ac != 2)
		no_param();
	mlx = init_program(av[1]);
	loop_program(mlx);
	event_hooks(mlx);
	mlx_loop(MLX_PTR);
	return (0);
}
