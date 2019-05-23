/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   program_loops.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 15:58:36 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 19:52:24 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../libft/libft.h"

#include "../includes/ui.h"
#include "../includes/xlm.h"
#include "../includes/keys.h"
#include "../includes/menu.h"
#include "../includes/mouse.h"
#include "../includes/player.h"
#include "../includes/screen.h"
#include "../includes/minimap.h"
#include "../includes/raycast.h"

#include "../minilibx_macos/mlx.h"

/*
**	Keeps the program running in an infinite loop
*/

int			loop_program(t_mlx *mlx)
{
	char	*fps_str;

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
		mlx_put_image_to_window(
			MLX_PTR, WIN_PTR, mlx->screen->save_img, 734, 505);
	create_ui(mlx, fps_str);
	if (mlx->screen->main_game == true)
		put_gun_to_window(mlx);
	free(fps_str);
	return (0);
}

/*
**	Hooks key / mouse events to the window
*/

void		event_hooks(t_mlx *mlx)
{
	mlx_hook(WIN_PTR, 2, 1L << 0, deal_key_press, mlx);
	mlx_hook(WIN_PTR, 3, 1L << 1, deal_key_release, mlx);
	mlx_hook(WIN_PTR, 4, 1L << 8, deal_mouse, mlx);
	mlx_hook(WIN_PTR, 17, 1L << 19, exit_x, NULL);
	mlx_loop_hook(MLX_PTR, loop_program, mlx);
	mlx_loop(MLX_PTR);
}
