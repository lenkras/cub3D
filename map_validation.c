/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-27 12:05:54 by epolkhov          #+#    #+#             */
/*   Updated: 2024-09-27 12:05:54 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	replace_spaces(t_cub *cub)
{
	int	h;
	int	w;

	h = 0;
	while (cub->map[h])
	{
		w = 0;
		while (cub->map[h][w])
		{
			if (has_space(cub->map[h][w]))
			{
				cub->map[h][w] = '1';
			}
			w++;
		}
		h++;
	}
}

int	check_max_width_of_map(t_cub *cub)
{
	int	width;
	int	curr_width;
	int	i;

	i = 0;
	width = ft_strlen(cub->map[i]);
	while (cub->map[i])
	{
		curr_width = ft_strlen(cub->map[i]);
		if (width < curr_width)
			width = curr_width;
		i++;
	}
	cub->width = width;
	return (0);
}

int	validate_player_path(t_cub *cub)
{
	int	h;
	int	w;

	h = 0;
	while (cub->map[h])
	{
		w = 0;
		while (cub->map[h][w])
		{
			if (cub->map[h][w] == 'N' || cub->map[h][w] == 'S' ||
				cub->map[h][w] == 'E' || cub->map[h][w] == 'W')
			{
				cub->player_w = w;
				cub->player_h = h;
				break ;
			}
			w++;
		}
		h++;
	}
	if (check_path(cub) == 1)
		return (1);
	return (0);
}

int	is_map_valid(t_cub *cub)
{
	if (!cub->map)
	{
		ft_putendl_fd("Error\nEmpty map.", 2);
		return (1);
	}
	if (check_map_content(cub) || validate_player_path(cub) == 1)
		return (1);
	replace_spaces(cub);
	return (0);
}
