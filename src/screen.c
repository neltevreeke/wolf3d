/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   screen.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 14:42:38 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 19:47:10 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../libft/libft.h"

#include "../includes/ui.h"
#include "../includes/xlm.h"
#include "../includes/screen.h"

#include "../minilibx_macos/mlx.h"

/*
**	Initializes window/screen
*/

static t_screen		*init_screen_var(void)
{
	t_screen		*screen;

	screen = MEM(t_screen);
	screen->main_game = true;
	screen->menu = false;
	screen->wall_side_textures = true;
	screen->gunstate = 0;
	screen->gun_img = (void**)malloc(sizeof(void*) * AMOUNT_GUNS);
	return (screen);
}

/*
**	Initializes window/screen
*/

t_screen			*init_screen(t_mlx *mlx)
{
	int				i;
	int				width;
	char			*tmp;
	char			*filenum;
	t_screen		*screen;

	i = 0;
	width = 0;
	screen = init_screen_var();
	screen->save_img = mlx_xpm_file_to_image(
					MLX_PTR, "textures/ui/saved.xpm", &width, &width);
	while (i < AMOUNT_GUNS)
	{
		filenum = ft_itoa(i + 1);
		tmp = ft_strjoin("textures/pistol/pistol_", filenum);
		free(filenum);
		filenum = ft_strjoin(tmp, ".xpm");
		free(tmp);
		screen->gun_img[i] = mlx_xpm_file_to_image(
							MLX_PTR, filenum, &width, &width);
		free(filenum);
		i++;
	}
	return (screen);
}
