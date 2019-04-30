/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 18:35:01 by jvisser        #+#    #+#                */
/*   Updated: 2019/04/30 17:44:21 by jvisser       ########   odam.nl         */
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
		mlx->map->sprites->Zbuffer[mlx->cur_x] = casting.per_wall_dist;
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
		ft_memcpy(IMG_ADD + mlx->size_line * (HEIGHT - y) + mlx->cur_x * mlx->bits_per_pixel / 8,
							&mlx->map->textures->texture_data[38]
							[ floorTexY % 128 * mlx->map->textures->size_line[38]
							+ floorTexX % 128 * (mlx->map->textures->bits_per_pixel[38] / 8)],
							sizeof(int));
      }

		mlx->cur_x++;
	}
	return (data);
}

//	Hij swapped het goed. maar hij print nog steeds niet goed uit.
//	Optimizen mogelijk?
void	sort_sprites(int *spriteorder, int *spritedistance, int amount)
{
	int i;
	int temp;
	int	temp2;

	i = 0;
	while (i < amount - 1)
	{
		if (spritedistance[i] < spritedistance[i + 1])
		{
			temp = spritedistance[i];
			spritedistance[i] = spritedistance[i + 1];
			spritedistance[i + 1] = temp;

			temp2 = spriteorder[i];
			spriteorder[i] = spriteorder[i + 1];
			spriteorder[i + 1] = temp2;
			i = 0;
		}
		else
			i++;
	}
}

void	sprites_to_img(t_mlx *mlx)
{
		// Sprite casting
	int	i;
	int	y;
	int	x;
	int	spriteorder[AMOUNT_SPRITES];
	int	spritedistance[AMOUNT_SPRITES];
	int amount;

	i = 0;
	y = 0;
	while (y < mlx->map->size_y)
	{
		x = 0;
		while (x < mlx->map->size_x)
		{
			if (mlx->map->level[y][x] < 0)
			{
					mlx->map->sprites->x[i] = x;
					mlx->map->sprites->y[i] = y;
     			spriteorder[i] = i;
     			spritedistance[i] = ((mlx->player->posx - mlx->map->sprites->x[i]) * (mlx->player->posx - mlx->map->sprites->x[i]) + (mlx->player->posy - mlx->map->sprites->y[i]) * (mlx->player->posy - mlx->map->sprites->y[i]));
					i++;
			}
			x++;
		}
		y++;
	}
	amount = i;
	sort_sprites(spriteorder, spritedistance, amount);

	int frunk = 0;
		while (frunk < amount)
		{
					i = 0;
					while (spriteorder[i] != frunk && i < amount)
						i++;
					// We resetten x en y hier i.p.v. die op een bepaalde manier over te nemen van bovenstaande loop.
					// ik heb het geprobeerd over te nemen maar dan vind ie de sprites niet meer en print ie ze niet..
     			double spriteX = mlx->map->sprites->x[i] + 0.5 - mlx->player->posx;
     			double spriteY = mlx->map->sprites->y[i] + 0.5 - mlx->player->posy;

					double invDet = 1.0 / (mlx->player->planex * mlx->player->diry - mlx->player->dirx * mlx->player->planey);

    			double transformX = invDet * (mlx->player->diry * spriteX - mlx->player->dirx * spriteY);
    			double transformY = invDet * (-mlx->player->planey * spriteX + mlx->player->planex * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

     			 int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));
     			 int spriteHeight = abs((int)(HEIGHT / (transformY))); //using "transformY" instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
    			 int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
    			  if(drawStartY < 0) drawStartY = 0;
     			 int drawEndY = spriteHeight / 2 + HEIGHT / 2;
     			 if(drawEndY >= HEIGHT)
							drawEndY = HEIGHT - 1;
				int spriteWidth = abs( (int)(HEIGHT / (transformY)));
     			int drawStartX = -spriteWidth / 2 + spriteScreenX;
     			if(drawStartX < 0)
					drawStartX = 0;
     			int drawEndX = spriteWidth / 2 + spriteScreenX;
     			if(drawEndX >= WIDTH)
				 	drawEndX = WIDTH - 1;
			int	sprite_texture = mlx->map->level[(int)mlx->map->sprites->y[i]][(int)mlx->map->sprites->x[i]];
			for(int stripe = drawStartX; stripe < drawEndX; stripe++)
   			{
 		       	int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 128 / spriteWidth) / 256;
        	//the conditions in the if are:
        	//1) it's in front of camera plane so you don't see things behind you
        	//2) it's on the screen (left)
        	//3) it's on the screen (right)
        	//4) ZBuffer, with perpendicular distance
        		if(transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < mlx->map->sprites->Zbuffer[stripe])
        			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        			{
        			  	int d = (y) * 256 - HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
        			  	int texY = ((d * 128) / spriteHeight) / 256;
								
									int color = 0;
									memcpy( &color, &mlx->map->sprites->sprite_data[ft_abs(sprite_texture) - 1]
									[ texY % 128 * mlx->map->sprites->size_line[ft_abs(sprite_texture) - 1]
									+ texX % 128 * (mlx->map->sprites->bits_per_pixel[ft_abs(sprite_texture) - 1] / 8)], sizeof(int));
        			  	if((color & 0x00FFFFFF) != 0)
						 			memcpy(IMG_ADD + mlx->size_line * y + stripe * mlx->bits_per_pixel / 8,
														&color,
														sizeof(int));
        			}
      			}
						frunk++;
		}
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
		pthread_create(&thread[i], NULL, raycasting, &tab[i]);
		i++;
	}
	while (i)
	{
		pthread_join(thread[i - 1], NULL);
		i--;
	}

	sprites_to_img(mlx);
	crosshair_to_img(mlx);
}
