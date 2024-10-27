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
				cub->map[h][w] != 'E' && cub->map[h][w] != 'W' && cub->map[h][w] != ' ' 
				&& cub->map[h][w] != '\t')
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


void flood_fill(char **map, int x, int y, int height, int width, int *valid)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		*valid = 0;
		return ;
	}
	if ( map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, height, width, valid);
	flood_fill(map, x - 1, y, height, width, valid);
	flood_fill(map, x, y + 1, height, width, valid);
	flood_fill(map, x, y - 1, height, width, valid);
}

int	check_with_floodfill(t_cub *cub, char **map_copy)
{
	int	h;
	int	w;
	int valid = 1;

	h = 0;
	while (map_copy[h])
	{
		w = 0;
		while (map_copy[h][w])
		{
			while (map_copy[h][w] == '0')
				flood_fill(map_copy, w, h, cub->height, cub->width, &valid);
			w++;
		}
		h++;
	}
	if (!valid)
	{
		ft_putendl_fd("Error: Map is invalid, check the walls.\n", 2);
		return (1);
	}
	return (0);
}

int	check_path(t_cub *cub)
{
	char	**map_copy;
	int		i;
	int		j;

	i = 0;
	check_max_width_of_map(cub);
	map_copy = malloc(sizeof(char *) * (cub->height + 1));
	if (!map_copy)
		return (1);
	while(cub->height > i)
	{
		map_copy[i] = malloc(sizeof(char *) * (cub->width + 1));
		if (!map_copy[i])
		{
			 while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
		 	return (1);
		}
		j = 0;
		while (cub->map[i][j])
		{
			map_copy[i][j] = cub->map[i][j];
			j++;
		}
		map_copy[i][j] = '\0';
		i++;
	}
	map_copy[cub->height] = NULL;
	
	printf("Map copy\n");
    for (i = 0; map_copy[i] != NULL; i++) {
        printf("%s\n", map_copy[i]);
    }
	if (check_with_floodfill(cub, map_copy) == 1)
		return (1);
	printf("Map copy after flood_fill.\n");
    for (i = 0; map_copy[i] != NULL; i++) {
        printf("%s\n", map_copy[i]);
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

int validate_player_path(t_cub *cub)
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
                break;
            }
			w++;
        }
		h++;
    }
    if (check_path(cub) == 1)
    {
        //ft_putendl_fd("Error: Invalid map or path.", 2);
        return (1);
    }
    return (0);
}

int	is_map_valid(t_cub *cub)
{
	if (!cub->map)
	{
		ft_putendl_fd("Error: Empty map.", 2);
		return (1);
	}
	if (check_map_content(cub) || validate_player_path(cub) == 1)
		return (1);
	replace_spaces(cub);
	return (0);
}
