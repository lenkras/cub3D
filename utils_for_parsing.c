/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-27 19:05:50 by epolkhov          #+#    #+#             */
/*   Updated: 2024-10-27 19:05:50 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_format(char *file_name)
{
	char	*compare;

	compare = ft_strrchr(file_name, '.');
	if (compare == file_name || compare == file_name + 4 || compare[-1] == '/')
	{
		ft_putendl_fd("Error\nInvalid file name.", 2);
		return (1);
	}
	if (!compare)
	{
		ft_putendl_fd("Error\nInvalid map file extension.", 2);
		return (1);
	}
	if (ft_strncmp(compare, ".cub", 5) != 0)
	{
		ft_putendl_fd("Error\nInvalid map file extension.", 2);
		return (1);
	}
	return (0);
}

int	check_all_flags_infile(t_cub *cub)
{
	if (cub->flags.c_flag == 1 && cub->flags.ea_flag == 1
		&& cub->flags.f_flag == 1
		&& cub->flags.no_flag == 1 && cub->flags.so_flag
		== 1 && cub->flags.we_flag == 1)
		return (0);
	ft_putendl_fd("Error\nOne or more file options are missing.", 2);
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
	if (ft_strncmp(&array[i], "NO", 2) != 0 && ft_strncmp(&array[i], "SO", 2)
		!= 0 && ft_strncmp(&array[i], "WE", 2) != 0
		&& ft_strncmp(&array[i], "EA", 2) != 0
		&& ft_strncmp(&array[i], "F ", 2) != 0
		&& ft_strncmp(&array[i], "C ", 2) != 0)
	{
		ft_putendl_fd("Error\nWrong data in a file.", 2);
		return (1);
	}
	return (0);
}

int	find_map_start(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'W' && line[i] != 'E')
			return (0);
		i++;
	}
	return (1);
}
