/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvreeke <nvreeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 17:28:23 by nvreeke        #+#    #+#                */
/*   Updated: 2019/04/15 17:34:17 by nvreeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	no_param(void)
{
	ft_putendl("Usage: ./wolf3d <map parameter>");
	exit(EXIT_FAILURE);
}

void	exit_failure_errno(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}
