/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-27 11:38:10 by epolkhov          #+#    #+#             */
/*   Updated: 2024-10-27 11:38:10 by epolkhov         ###   ########.fr       */
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
		handle_error("Error: Failed to read a file.\n", fd, data);
		return (NULL);
	}
	return (data);
}