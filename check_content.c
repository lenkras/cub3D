/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-27 16:07:17 by epolkhov          #+#    #+#             */
/*   Updated: 2024-10-27 16:07:17 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	check_player_count(t_cub *cub, char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		cub->player++;
		if (cub->player > 1)
		{
			ft_putendl_fd("Error: Player should be only one.", 2);
			return (1);
		}
	}
	return (0);
}

static int	check_valid_content(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || \
			c == 'E' || c == 'W' || c == ' ' || c == '\t');
}

int	check_map_content(t_cub *cub)
{
	int	h;
	int	w;

	h = 0;
	while (cub->map[h])
	{
		w = 0;
		while (cub->map[h][w])
		{
			if (!check_valid_content(cub->map[h][w]))
			{
				ft_putendl_fd("Error: Map content is invalid.", 2);
				return (1);
			}
			if (check_player_count(cub, cub->map[h][w]))
				return (1);
			w++;
		}
		h++;
	}
	if (cub->player == 0)
	{
		ft_putendl_fd("Error: No player found.", 2);
	}
	return (0);
}
