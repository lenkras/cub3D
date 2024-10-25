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

void fill_map_spaces(t_cub *cub, char **map_copy)
{
    int h = 0;
    int w;

    // Step 1: Process each row of the map
    while (map_copy[h])
    {
        int line_len = ft_strlen(map_copy[h]);
        
        // Allocate new row with the map's width (cub->width)
        char *new_row = malloc(cub->width + 1);
        if (!new_row)
        {
            perror("Error: Failed to allocate memory.");
            exit(1);
        }

        // Step 2: Fill the new row, copying and replacing spaces
        for (w = 0; w < cub->width; w++)
        {
            if (w < line_len)
            {
                if (map_copy[h][w] == ' ')
                {
                    // Check horizontal and vertical neighbors (if in bounds)
					if ((w > 0 && (map_copy[h][w - 1] == '1' )) &&
                        (w < line_len - 1 && (map_copy[h][w + 1] == '1' )) &&
                        (h > 0 && (map_copy[h - 1][w] == '1' )) &&
                        (map_copy[h + 1] && (map_copy[h + 1][w] == '1' || map_copy[h + 1][w] == ' ' )))
						new_row[w] = '2';
					else if ((w > 0 && (map_copy[h][w - 1] == '0' || map_copy[h][w - 1] == '1' || map_copy[h][w - 1] == ' ')) &&
                        (w < line_len - 1 && (map_copy[h][w + 1] == '0' || map_copy[h][w + 1] == '1' || map_copy[h][w + 1] == ' ')) &&
                        (h > 0 && (map_copy[h - 1][w] == '0' || map_copy[h - 1][w] == '1' || map_copy[h - 1][w] == ' ')) &&
                        (map_copy[h + 1] && (map_copy[h + 1][w] == '0' || map_copy[h + 1][w] == '1' || map_copy[h + 1][w] == ' ')))
                    {
                        // Replace space with '0' if it's inside the map
                        new_row[w] = '0';
                    }
					
                    else
                    {
                        // Otherwise, replace space with '2' for outside the map
                        new_row[w] = '2';
                    }
                }
                else
                {
                    new_row[w] = map_copy[h][w]; // Copy the original character
                }
            }
            else
            {
                // If we're past the original line length, fill with '2'
                new_row[w] = '2';
            }
        }
        new_row[cub->width] = '\0';  // Null-terminate the new row
		
        // Replace the old row with the new row
        free(map_copy[h]);
        map_copy[h] = new_row;
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
	//replace_spaces(cub);
	return (0);
}



void flood_fill(char **map, int x, int y, int height, int width)
{
	if (x < 0 || x >= width || y < 0 || y >= height || map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == '2')
    {
        printf("Error: Invalid wall detected at (%d, %d)\n", x, y);
        exit(1);  // Exit or handle error accordingly
    }
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, height, width);
	flood_fill(map, x - 1, y, height, width);
	flood_fill(map, x, y + 1, height, width);
	flood_fill(map, x, y - 1, height, width);
}

int	check_walls(t_cub *cub, char **map_copy)
{
	int	i;
	
	i = 0;
	while (i < cub->height)
	{
		if ((map_copy[i][0] != '1' && map_copy[i][0] != '2') || 
			( map_copy[i][cub->width - 1] != '1' && map_copy[i][cub->width - 1] != '2'))
		{
			ft_putendl_fd("Check the walls of the map.", 2);
			return (1);
		}	
		i++;
	}
	i = 0;
	while (i < cub->width)
	{
		if ((map_copy[0][i] != '1' && map_copy[0][i] != '2') || 
			(map_copy[cub->height - 1][i] != '1' && map_copy[cub->height - 1][i] != '2'))
		{
			ft_putendl_fd("Check the walls of the map.", 2);
			return (1);
		}	
		i++;
	}
	return (0);
}

void	check_with_floodfill(t_cub *cub, char **map_copy)
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
				flood_fill(map_copy, w, h, cub->height, cub->width);
			w++;
		}
		h++;
	}
}

int	check_path(t_cub *cub, int w, int h)
{
	char	**map_copy;
	int		i;
	int		j;

	i = 0;
	check_max_width_of_map(cub);
	map_copy = malloc(sizeof(char *) * (cub->height + 1));
	if (!map_copy)
	{
		return (1);
	}
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
	fill_map_spaces(cub, map_copy);
	
	printf("Map copy after filling in with 2.\n");
    for (i = 0; map_copy[i] != NULL; i++) {
        printf("%s\n", map_copy[i]);
    }
	if (check_walls(cub, map_copy) == 1)
		return (1);
	flood_fill(map_copy, w, h, cub->height, cub->width);
	check_with_floodfill(cub, map_copy);
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
    if (check_path(cub, cub->player_w, cub->player_h))
    {
        ft_putendl_fd("Error: Invalid map or path.", 2);
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
