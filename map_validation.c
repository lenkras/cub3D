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

int	check_width_of_map(t_cub *cub)
{
	int	width;
	int	curr_width;
	int	i;

	i = 0;
	width = ft_strlen(cub->map[i]);
	while (cub->map[i])
	{
		curr_width = 0;
		curr_width = ft_strlen(cub->map[i]);
		if (width != curr_width)
		{
			ft_putendl_fd("Error: Invalid map.", 2);
			return (1);
		}
		i++;
	}
	cub->width = width;
	return (0);
}

int	check_spaces_in_map(t_cub *cub)
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
				ft_putendl_fd("Error: Map has invalid spaces.", 2);
				return (1);
			}
			w++;
		}
		h++;
	}
	return (0);
}

int	check_walls(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->height)
	{
		if (cub->map[i][0] != '1' || cub->map[i][cub->width - 1] != '1' )
		{
			ft_putendl_fd("Check the walls of the map.", 2);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < cub->width)
	{
		if (cub->map[0][i] != '1' || cub->map[cub->height - 1][i] != '1' )
		{
			ft_putendl_fd("Check the walls of the map.", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_map_content(t_cub *cub)
{
	int	h;
	int	w;

	h = 0;

	while (cub->map[h])
	{
		w = 0;
		while (cub->map[h][w])
		{
			if (cub->map[h][w] != '1' && cub->map[h][w] != '0' && \
				cub->map[h][w] != 'N' && cub->map[h][w] != 'S' && \
				cub->map[h][w] != 'E' && cub->map[h][w] != 'W')
			{
				ft_putendl_fd("Error: Map content is invalid.", 2);
				return (1);
			}
			if (cub->map[h][w] == 'N' || cub->map[h][w] == 'S' || \
				cub->map[h][w] == 'E' || cub->map[h][w] == 'W')
				cub->player++;
			if (cub->player > 1)
			{
				ft_putendl_fd("Error: Player should be only one.", 2);
				return (1);
			}
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



// int validate_player_path(t_cub *cub)
// {
// 	int	h;
// 	int	w;

// 	h = 0;
// 	while (cub->map[h])
//     {
//         w = 0;
// 		while (cub->map[h][w])
//         {
//             if (cub->map[h][w] == 'N' || cub->map[h][w] == 'S' ||
//                 cub->map[h][w] == 'E' || cub->map[h][w] == 'W')
//             {
//                 cub->player_w = w;
//                 cub->player_h = h;
//                 break; 
//             }
// 			w++;
//         }
// 		h++;
//     }
//     if (!check_path(cub, cub->player_w, cub->player_h))
//     {
//         ft_putendl_fd("Error: Invalid path, player cannot move freely.", 2);
//         return (1);
//     }
//     return (0);
// }

int	is_map_valid(t_cub *cub)
{
	if (!cub->map)
	{
		ft_putendl_fd("Error: Empty map.", 2);
		return (1);
	}
	if ( check_walls(cub) ||
		 check_map_content(cub))
		return (1);
	return (0);
}
