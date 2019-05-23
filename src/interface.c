/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interface.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 15:56:37 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 19:52:37 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../libft/libft.h"

#include "../includes/ui.h"
#include "../includes/xlm.h"
#include "../includes/screen.h"
#include "../includes/player.h"
#include "../includes/raycast.h"

#include "../minilibx_macos/mlx.h"

/*
**	Prints the crosshair to the image
*/

void		crosshair_to_img(t_mlx *mlx)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	pixel_to_img(mlx, 500, 300, 0x25ff00);
	while (i < 5 && j < 5)
	{
		pixel_to_img(mlx, i + 490, 300, 0x25ff00);
		pixel_to_img(mlx, 506 + j, 300, 0x25ff00);
		pixel_to_img(mlx, 500, i + 290, 0x25ff00);
		pixel_to_img(mlx, 500, j + 306, 0x25ff00);
		i++;
		j++;
	}
}

/*
**	Sets the right sprite for the gun in the window/screen
*/

void		put_gun_to_window(t_mlx *mlx)
{
	if (mlx->screen->gunstate == 0)
		mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_IDLE_GUN, 244, 88);
	else if (mlx->screen->gunstate > 0)
	{
		if (mlx->screen->gunstate == 1)
			mlx_put_image_to_window(
				MLX_PTR, WIN_PTR, IMG_ACTION_GUN_1, 244, 88);
		else if (mlx->screen->gunstate == 2)
			mlx_put_image_to_window(
				MLX_PTR, WIN_PTR, IMG_ACTION_GUN_2, 244, 88);
		else if (mlx->screen->gunstate == 3)
			mlx_put_image_to_window(
				MLX_PTR, WIN_PTR, IMG_ACTION_GUN_3, 244, 88);
		else if (mlx->screen->gunstate == 4)
			mlx_put_image_to_window(
				MLX_PTR, WIN_PTR, IMG_ACTION_GUN_4, 244, 88);
		if (mlx->screen->gunstate == 4)
			mlx->screen->gunstate = 0;
		else
			mlx->screen->gunstate++;
	}
}

/*
**	Puts the UI in the window/screen
*/

void		create_ui(t_mlx *mlx, char *fps_str)
{
	char	*hp;
	char	*ammo;

	ft_bzero(UI_ADD, sizeof(int) * 400 * 200);
	hp = ft_itoa(mlx->player->hp);
	ammo = ft_itoa(mlx->player->ammo);
	mlx_string_put(MLX_PTR, WIN_PTR, REAL_WIDTH - 175, 575, 0xFFFFFF, "Fps:");
	mlx_string_put(MLX_PTR, WIN_PTR, REAL_WIDTH - 40, 575, 0xFFFFFF, fps_str);
	mlx_string_put(MLX_PTR, WIN_PTR, REAL_WIDTH - 175, 250, 0xFFFFFF, "Ammo:");
	mlx_string_put(MLX_PTR, WIN_PTR, REAL_WIDTH - 40, 250, 0xFFFFFF, ammo);
	mlx_string_put(
		MLX_PTR, WIN_PTR, REAL_WIDTH - 175, 275, 0xFFFFFF, "Health:");
	mlx_string_put(MLX_PTR, WIN_PTR, REAL_WIDTH - 40, 275, 0xFFFFFF, hp);
	free(ammo);
	free(hp);
}
