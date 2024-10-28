/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-27 16:15:18 by epolkhov          #+#    #+#             */
/*   Updated: 2024-10-27 16:15:18 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	flood_fill(char **map, int x, int y, t_cub *cub)
{
	if (x < 0 || x >= cub->width || y < 0 || y >= cub->height)
	{
		cub->valid = 0;
		return ;
	}
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, cub);
	flood_fill(map, x - 1, y, cub);
	flood_fill(map, x, y + 1, cub);
	flood_fill(map, x, y - 1, cub);
}

int	check_with_floodfill(t_cub *cub, char **map_copy)
{
	int	h;
	int	w;

	h = 0;
	while (map_copy[h])
	{
		w = 0;
		while (map_copy[h][w])
		{
			while (map_copy[h][w] == '0')
				flood_fill(map_copy, w, h, cub);
			w++;
		}
		h++;
	}
	if (!cub->valid)
	{
		ft_putendl_fd("Error\nMap is invalid, check the walls.\n", 2);
		return (1);
	}
	return (0);
}

static void	copy_map_for_check(char **map_copy, char **original_map, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (original_map[i][j])
		{
			map_copy[i][j] = original_map[i][j];
			j++;
		}
		map_copy[i][j] = '\0';
		i++;
	}
	map_copy[height] = NULL;
}

static char	**allocate_map_copy(int height, int width)
{
	char	**map_copy;
	int		i;

	i = 0;
	map_copy = malloc(sizeof(char *) * (height + 1));
	if (!map_copy)
		return (NULL);
	while (i < height)
	{
		map_copy[i] = malloc(sizeof(char) * (width + 1));
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[height] = NULL;
	return (map_copy);
}

int	check_path(t_cub *cub)
{
	char	**map_copy;
	int		i;

	i = 0;
	check_max_width_of_map(cub);
	map_copy = allocate_map_copy(cub->height, cub->width);
	if (!map_copy)
		return (1);
	copy_map_for_check(map_copy, cub->map, cub->height);
	if (check_with_floodfill(cub, map_copy) == 1)
	{
		free_array(map_copy);
		return (1);
	}
	i = 0;
	while (i < cub->height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
	return (0);
}
