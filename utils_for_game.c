/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:38:10 by epolkhov          #+#    #+#             */
/*   Updated: 2024/11/11 22:03:24 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_sign(float f)
{
	if (f < 0.0f)
	{
		if (f > -0.000001f)
			return (0);
		else
			return (-1);
	}
	else
	{
		if (f < 0.000001f)
			return (0);
		else
			return (1);
	}
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

char	*print_readfile_error(int bytes_read, int fd, char *data)
{
	if (bytes_read == -1)
	{
		handle_error("Error\nFailed to read a file.\n", fd, data);
		return (NULL);
	}
	return (data);
}

void	mirror_map(t_cub *cub)
{
	int		top;
	int		bottom;
	char	*temp;

	top = 0;
	bottom = cub->height - 1;
	while (top < bottom)
	{
		temp = cub->map[top];
		cub->map[top] = cub->map[bottom];
		cub->map[bottom] = temp;
		top++;
		bottom--;
	}
}
