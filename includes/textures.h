/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 19:11:36 by jvisser        #+#    #+#                */
/*   Updated: 2019/05/23 20:07:19 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# define AMOUNT_TEXTURES 41

typedef struct s_mlx	t_mlx;

typedef struct	s_textures
{
	void		**tex_arr;
	char		**texture_data;
	int			*bits_per_pixel;
	int			*size_line;
	int			*endian;
}				t_textures;

t_textures		*init_textures(t_mlx *mlx);

#endif
