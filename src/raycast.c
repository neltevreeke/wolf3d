/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 18:35:01 by jvisser        #+#    #+#                */
/*   Updated: 2019/04/28 12:53:09 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "wolf3d.h"

void	pixel_to_img(t_mlx *mlx, int px, int py, int color)
{
	color = mlx_get_color_value(MLX_PTR, color);
	ft_memcpy(IMG_ADD + mlx->size_line * py + px * mlx->bits_per_pixel / 8,
				&color, sizeof(int));
}

void	print_roof(t_mlx *mlx, t_casting casting)
{
	int	start;

	start = 0;
	while (start < (HEIGHT / 2 - casting.lineheight / 2))
	{	
		pixel_to_img(mlx, mlx->cur_x, start, 0x383838);
		start++;
	}
}

void	print_floor(t_mlx *mlx, t_casting casting)
{
	int	start;

	start = HEIGHT / 2 + casting.lineheight / 2;
	while (start < HEIGHT)
	{	
		pixel_to_img(mlx, mlx->cur_x, start, 0x707070);
		start++;
	}
}

void    *raycasting(void *data)
{
	t_mlx		*mlx;
	t_casting	casting;
	double		ZBuffer[WIDTH];

	mlx = (t_mlx*)data;
	while (mlx->cur_x < mlx->max_x)
	{
		casting.camera_x = 2 * mlx->cur_x / (double)WIDTH - 1;
		casting.ray_dir_x = mlx->player->dirx + mlx->player->planex * casting.camera_x;
		casting.ray_dir_y = mlx->player->diry + mlx->player->planey * casting.camera_x;

		casting.map_x = (int)mlx->player->posx;
		casting.map_y = (int)mlx->player->posy;

		casting.delta_dist_x = fabs(1 / casting.ray_dir_x);
		casting.delta_dist_y = fabs(1 / casting.ray_dir_y);

		casting.hit = 0;
		if (casting.ray_dir_x < 0)
		{
			casting.step_x = -1;
			casting.side_dist_x = (mlx->player->posx - casting.map_x) * casting.delta_dist_x;
		}
		else
		{
			casting.step_x = 1;
			casting.side_dist_x = (casting.map_x + 1 - mlx->player->posx) * casting.delta_dist_x;
		}
		if (casting.ray_dir_y < 0)
		{
			casting.step_y = -1;
			casting.side_dist_y = (mlx->player->posy - casting.map_y) * casting.delta_dist_y;
		}
		else
		{
			casting.step_y = 1;
			casting.side_dist_y = (casting.map_y + 1 - mlx->player->posy) * casting.delta_dist_y;
		}
	
		while (casting.hit == 0)
		{
			if (casting.side_dist_x < casting.side_dist_y)
			{
				casting.side_dist_x += casting.delta_dist_x;
				casting.map_x += casting.step_x;
				if (casting.step_x == 1)
					casting.side = 0;
				else
					casting.side = 2;
			}
			else
			{
				casting.side_dist_y += casting.delta_dist_y;
				casting.map_y += casting.step_y;
				if (casting.step_y == 1)
					casting.side = 1;
				else
					casting.side = 3;
			}
			if (mlx->map->level[casting.map_y][casting.map_x] > 0)
				casting.hit = 1;
		}
		if (casting.side % 2 == 0)
		{
			casting.per_wall_dist = (casting.map_x - mlx->player->posx + (1 - casting.step_x) / 2) / casting.ray_dir_x;
		}
		else
		{
			casting.per_wall_dist = (casting.map_y - mlx->player->posy + (1 - casting.step_y) / 2) / casting.ray_dir_y;
		}
		ZBuffer[mlx->cur_x] = casting.per_wall_dist;
		casting.lineheight = (int)(HEIGHT / casting.per_wall_dist);

		double wallX;
     	if (casting.side % 2 == 0)
	  		wallX = mlx->player->posy + casting.per_wall_dist * casting.ray_dir_y;
		else
	  		wallX = mlx->player->posx + casting.per_wall_dist * casting.ray_dir_x;
      	wallX -= floor((wallX));

		int texX = (int)(wallX * (double)128);
		if(casting.side % 2 == 0 && casting.ray_dir_x > 0)
	  		texX = 128 - texX - 1;
		if(casting.side % 2 == 1 && casting.ray_dir_y < 0)
	  		texX = 128 - texX - 1;
		texX = abs(texX);

		// sky texture
		// print_roof(mlx, casting);

		int	index = mlx->map->level[casting.map_y][casting.map_x];
		int y = (HEIGHT / 2 - casting.lineheight / 2);
		if (y < 0)
			y = 0;
		int end = (HEIGHT / 2 - casting.lineheight / 2) + casting.lineheight;
		if (end > HEIGHT)
			end = HEIGHT;

		// walls
			while (y < end)
			{
				if (y < HEIGHT && y >= 0)
				{
					int d = y - HEIGHT * 0.5 + casting.lineheight * 0.5;
					int texY = abs(((d * 128) / casting.lineheight));

					ft_memcpy(IMG_ADD + mlx->size_line * y + mlx->cur_x * mlx->bits_per_pixel / 8,
							&mlx->map->textures->texture_data[index - 1 + casting.side]
							[ texY % 128 * mlx->map->textures->size_line[index - 1 + casting.side]
							+ texX % 128 * (mlx->map->textures->bits_per_pixel[index - 1 + casting.side] / 8)],
							sizeof(int));
				}
				y++;
			}

		// Floor texture
		print_floor(mlx, casting);


      //FLOOR CASTING
      double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

      //4 different wall directions possible
		if(casting.side % 2 == 0 && casting.ray_dir_x > 0)
		{
			floorXWall = casting.map_x;
			floorYWall = casting.map_y + wallX;
		}
		else if(casting.side % 2 == 0 && casting.ray_dir_x < 0)
		{
			floorXWall = casting.map_x + 1.0;
			floorYWall = casting.map_y + wallX;
		}
		else if(casting.side % 2 == 1 && casting.ray_dir_y > 0)
		{
			floorXWall = casting.map_x + wallX;
			floorYWall = casting.map_y;
		}
		else
		{
			floorXWall = casting.map_x + wallX;
			floorYWall = casting.map_y + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = casting.per_wall_dist;
		distPlayer = 0.0;
	  end = casting.lineheight / 2 + HEIGHT / 2;
		if (end < 0) end = HEIGHT;
		for(int y = end + 1; y < HEIGHT; y++)
		{
			currentDist = HEIGHT / (2.0 * y - HEIGHT); //you could make a small lookup table for this instead

			double weight = (currentDist - distPlayer) / (distWall - distPlayer);

			double currentFloorX = weight * floorXWall + (1.0 - weight) * mlx->player->posx;
			double currentFloorY = weight * floorYWall + (1.0 - weight) * mlx->player->posy;

			int floorTexX, floorTexY;
			floorTexX = (int)(currentFloorX * 128) % 128;
			floorTexY = (int)(currentFloorY * 128) % 128;

		// ft_memcpy(IMG_ADD + mlx->size_line * y + mlx->cur_x * mlx->bits_per_pixel / 8,
		// 					&mlx->map->textures->texture_data[1]
		// 					[ floorTexY % 128 * mlx->map->textures->size_line[1]
		// 					+ floorTexX % 128 * (mlx->map->textures->bits_per_pixel[1] / 8)],
		// 					sizeof(int));
        // buffer[y][x] = (mlx->textures->texture_data[3][128 * floorTexY + floorTexX] >> 1) & 8355711;
		//ceiling (symmetrical!)
		ft_memcpy(IMG_ADD + mlx->size_line * (HEIGHT - y) + mlx->cur_x * mlx->bits_per_pixel / 8,
							&mlx->map->textures->texture_data[38]
							[ floorTexY % 128 * mlx->map->textures->size_line[38]
							+ floorTexX % 128 * (mlx->map->textures->bits_per_pixel[38] / 8)],
							sizeof(int));
        // buffer[HEIGHT - y][x] = texture[6][texWidth * floorTexY + floorTexX];
      }

		mlx->cur_x++;
	}
	
	// Sprite casting
	int	i;
	int	y;
	int	x;
	int	spriteorder[AMOUNT_SPRITES];
	int	spritedistance[AMOUNT_SPRITES];

	i = 0;
	y = 0;
	while (y < mlx->map->size_y)
    {
		x = 0;
		while (x < mlx->map->size_x)
		{
			if (mlx->map->level[y][x] < 0)
			{
     			spriteorder[i] = i;
     			spritedistance[i] = ((mlx->player->posx - x) * (mlx->player->posx - x) + (mlx->player->posy - y) * (mlx->player->posy - y));
			}
			x++;
		}
		y++;
    }

	y = 0;
	while (y < mlx->map->size_y)
    {
		x = 0;
		while (x < mlx->map->size_x)
		{
			if (mlx->map->level[y][x] < 0)
			{
     			double spriteX = x + 0.5 - mlx->player->posx;
     			double spriteY = y + 0.5 - mlx->player->posy;

				double invDet = 1.0 / (mlx->player->planex * mlx->player->diry - mlx->player->dirx * mlx->player->planey);

    			double transformX = invDet * (mlx->player->diry * spriteX - mlx->player->dirx * spriteY);
    			double transformY = invDet * (-mlx->player->planey * spriteX + mlx->player->planex * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

     			 int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));
     			 int spriteHeight = abs((int)(HEIGHT / (transformY))); //using "transformY" instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
    			 int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
    			  if(drawStartY < 0) drawStartY = 0;
     			 int drawEndY = spriteHeight / 2 + HEIGHT / 2;
     			 if(drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

				int spriteWidth = abs( (int)(HEIGHT / (transformY)));
     			int drawStartX = -spriteWidth / 2 + spriteScreenX;
     			if(drawStartX < 0)
					drawStartX = 0;
     			int drawEndX = spriteWidth / 2 + spriteScreenX;
     			if(drawEndX >= WIDTH)
				 	drawEndX = WIDTH - 1;
			int	sprite_texture = mlx->map->level[y][x];
			for(int stripe = drawStartX; stripe < drawEndX; stripe++)
   			{
 		       	int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 128 / spriteWidth) / 256;
        	//the conditions in the if are:
        	//1) it's in front of camera plane so you don't see things behind you
        	//2) it's on the screen (left)
        	//3) it's on the screen (right)
        	//4) ZBuffer, with perpendicular distance
        		if(transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < ZBuffer[stripe])
        			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        			{
        			  	int d = (y) * 256 - HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
        			  	int texY = ((d * 128) / spriteHeight) / 256;
						int color;
						ft_memcpy( &color, &mlx->map->sprites->sprite_data[ft_abs(sprite_texture) - 1]
							[ texY % 128 * mlx->map->sprites->size_line[ft_abs(sprite_texture) - 1]
							+ texX % 128 * (mlx->map->sprites->bits_per_pixel[ft_abs(sprite_texture) - 1] / 8)], sizeof(int));
        			  	// uint32_t color = mlx->textures->texture_data[sprite[spriteOrder[i]].texture][128 * texY + texX]; //get current color from the texture
        			  	if((color & 0x00FFFFFF) != 0)
						  ft_memcpy(IMG_ADD + mlx->size_line * y + stripe * mlx->bits_per_pixel / 8,
							&color,
							sizeof(int));
						//   buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
        			}
      			}
			}
			x++;
		}
		y++;
    }

	return (data);
}

void	crosshair_to_img(t_mlx *mlx)
{
	int i;
	int j;

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

void	create_image(t_mlx *mlx)
{
	int			i;
	t_mlx		tab[THREAD_AMOUNT];
	pthread_t	thread[THREAD_AMOUNT];

	i = 0;
	while (i < THREAD_AMOUNT)
	{
		ft_memcpy((void*)&tab[i], (void*)mlx, sizeof(t_mlx));
		tab[i].max_x = (i + 1) * (WIDTH / THREAD_AMOUNT);
		tab[i].cur_x = i * (WIDTH / THREAD_AMOUNT);
		pthread_create(&thread[i], NULL, &raycasting, &tab[i]);
		i++;
	}
	while (i)
	{
		pthread_join(thread[i - 1], NULL);
		i--;
	}
	crosshair_to_img(mlx);
}
