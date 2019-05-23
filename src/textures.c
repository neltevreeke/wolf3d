/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 14:25:14 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/23 19:49:42 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../libft/libft.h"

#include "../includes/xlm.h"
#include "../includes/error.h"
#include "../includes/textures.h"

#include "../minilibx_macos/mlx.h"

/*
**	fills texture data adress array
*/

static char			**init_textures_data(t_textures *textures)
{
	int				i;
	char			**texture_data;

	i = 0;
	texture_data = (char**)malloc(sizeof(char*) * AMOUNT_TEXTURES);
	if (!texture_data)
		exit_failure_errno();
	while (i < AMOUNT_TEXTURES)
	{
		texture_data[i] = mlx_get_data_addr(textures->tex_arr[i],
						&textures->bits_per_pixel[i],
						&textures->size_line[i],
						&textures->endian[i]);
		i++;
	}
	return (texture_data);
}

/*
**	Mallloc the texture struct with right amounts
*/

static t_textures	*malloc_texture_struct(void)
{
	t_textures		*textures;

	textures = MEM(t_textures);
	if (!textures)
		exit_failure_errno();
	textures->tex_arr = (void**)malloc(sizeof(void*) * AMOUNT_TEXTURES);
	textures->endian = (int*)malloc(sizeof(int) * AMOUNT_TEXTURES);
	textures->size_line = (int*)malloc(sizeof(int) * AMOUNT_TEXTURES);
	textures->bits_per_pixel = (int*)malloc(sizeof(int) * AMOUNT_TEXTURES);
	return (textures);
}

/*
**	Initializes textures
*/

t_textures			*init_textures(t_mlx *mlx)
{
	int				i;
	int				width;
	char			*tmp;
	char			*filenum;
	t_textures		*textures;

	i = 0;
	width = 128;
	textures = malloc_texture_struct();
	while (i < AMOUNT_TEXTURES)
	{
		filenum = ft_itoa(i + 1);
		tmp = ft_strjoin("textures/walls/wall_", filenum);
		free(filenum);
		filenum = ft_strjoin(tmp, ".xpm");
		free(tmp);
		textures->tex_arr[i] = mlx_xpm_file_to_image(
			MLX_PTR, filenum, &width, &width);
		free(filenum);
		i++;
	}
	textures->texture_data = init_textures_data(textures);
	return (textures);
}
