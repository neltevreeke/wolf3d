/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 14:32:29 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/24 15:53:00 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../libft/libft.h"

#include "../includes/xlm.h"
#include "../includes/error.h"
#include "../includes/sprites.h"

#include "../minilibx_macos/mlx.h"

/*
**	Fills sprite data adress array
*/

char				**init_sprites_data(t_sprites *sprites)
{
	char			**sprite_data;
	int				i;

	i = 0;
	sprite_data = (char**)malloc(sizeof(char*) * AMOUNT_SPRITES);
	if (!sprite_data)
		exit_failure_errno();
	while (i < AMOUNT_SPRITES)
	{
		sprite_data[i] = mlx_get_data_addr(sprites->spr_arr[i],
						&sprites->bits_per_pixel[i],
						&sprites->size_line[i],
						&sprites->endian[i]);
		i++;
	}
	return (sprite_data);
}

/*
**	Mallocs the sprite struct
*/

static t_sprites	*malloc_sprite_struct(void)
{
	t_sprites		*sprites;

	sprites = MEM(t_sprites);
	if (!sprites)
		exit_failure_errno();
	sprites->spr_arr = (void**)malloc(sizeof(void*) * AMOUNT_SPRITES);
	sprites->endian = (int*)malloc(sizeof(int) * AMOUNT_SPRITES);
	sprites->size_line = (int*)malloc(sizeof(int) * AMOUNT_SPRITES);
	sprites->bits_per_pixel = (int*)malloc(sizeof(int) * AMOUNT_SPRITES);
	sprites->x = (double*)malloc(sizeof(double) * MAX_SPRITES);
	sprites->y = (double*)malloc(sizeof(double) * MAX_SPRITES);
	return (sprites);
}

/*
**	Initializes sprites
*/

t_sprites			*init_sprites(t_mlx *mlx)
{
	int				i;
	int				width;
	char			*tmp;
	char			*filenum;
	t_sprites		*sprites;

	i = 0;
	width = 128;
	sprites = malloc_sprite_struct();
	while (i < AMOUNT_SPRITES)
	{
		filenum = ft_itoa(i + 1);
		tmp = ft_strjoin("textures/sprites/sprite_", filenum);
		free(filenum);
		filenum = ft_strjoin(tmp, ".xpm");
		free(tmp);
		sprites->spr_arr[i] = mlx_xpm_file_to_image(
							MLX_PTR, filenum, &width, &width);
		free(filenum);
		i++;
	}
	sprites->sprite_data = init_sprites_data(sprites);
	return (sprites);
}
