/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fps_meter.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/08 18:16:45 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/12 15:24:16 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	Gets the current time of day in milliseconds.
*/

double		get_cur_time(void)
{
	double			time_in_mill;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_mill);
}

/*
**	Calculates amount of frames per second, converts the nb into str.
*/

char		*get_fps(char *str)
{
	static double	start_time;
	static int		frames;
	static int		last_fps;

	frames++;
	if (get_cur_time() > start_time + 1000)
	{
		start_time = get_cur_time();
		last_fps = frames;
		frames = 0;
	}
	str = ft_itoa(last_fps);
	return (str);
}
