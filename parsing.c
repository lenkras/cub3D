/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-27 09:08:33 by epolkhov          #+#    #+#             */
/*   Updated: 2024-09-27 09:08:33 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_all_flags_infile(t_cub *cub)
{
	if (cub->flags.C_flag == 1 && cub->flags.EA_flag == 1 && cub->flags.F_flag == 1 && 
		cub->flags.NO_flag == 1 && cub->flags.SO_flag == 1 && cub->flags.WE_flag == 1)
		return (0);
	else 
	{
		ft_putendl_fd("Error: One or more file options are missing.", 2);
		return (1);
	}
}

void	copy_map(char **array, t_cub *cub, int start)
{
	int	i;
	int j;

	i = start;
	j = 0;
	cub->height = 0;
	if (!array[i])
		return ;
	while(array[i])
	{
		cub->height++;
		i++;
	}
	cub->map = malloc(sizeof(char *) * (cub->height + 1));
	if (!cub->map)
	{
		ft_putendl_fd("Error: Failed to allocate mamory.", 2);
		return ;
	}
	i = start;
	while (j < cub->height)
	{
		cub->map[j] = ft_strdup(array[i]);
		if (!cub->map[j])
		{
			ft_putendl_fd("Error: Failed to duplicate map line.", 2);
			while (j > 0)
				free(cub->map[--j]);
			free(cub->map);
			return ;
		}
		printf("Copied map line %d: \"%s\"\n", j, cub->map[j]);
		j++;
		i++;
	}
	cub->map[cub->height] = NULL;
}

int	find_map_start(char *line)
{
    int i = 0;
    
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != 'N' && 
			line[i] != 'S' && line[i] != 'W' && line[i] != 'E')
            return (0);
        i++;
    }
    return (1);
}

int	check_file_data(char *array)
{
	int	i;

	i = 0;
	while (array[i] == ' ' || array[i] == '\t')
		i++;
	if (array[i] == '1' || array[i] == '0')
		return (0);
	
	if (ft_strncmp(&array[i], "NO", 2) != 0 && ft_strncmp(&array[i], "SO", 2) != 0 && ft_strncmp(&array[i], "WE", 2) != 0 
			&& ft_strncmp(&array[i], "EA", 2) != 0 && ft_strncmp(&array[i], "F ", 2) != 0 && ft_strncmp(&array[i], "C ", 2) != 0)
		{
			ft_putendl_fd("Error: Wrong data in a file.", 2);
			return (1);
		}
		
	return (0);
}
