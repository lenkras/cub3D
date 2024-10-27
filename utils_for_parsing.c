/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-27 11:40:11 by epolkhov          #+#    #+#             */
/*   Updated: 2024-10-27 11:40:11 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 #include "cub.h"

int	check_format(char *file_name)
{
	char	*compare;

	compare = ft_strrchr(file_name, '.');
	if (!compare)
	{
		ft_putendl_fd("Error: Invalid map file extansion.", 2);
		return (1);
	}
	if (ft_strncmp(compare, ".cub", 5) != 0)
	{
		ft_putendl_fd("Error: Invalid map file extansion.", 2);
		return (1) ;
	}
	return (0);
}

int	check_consecutive_newlines_in_map(char *file)
{
	int	i = 0;
	int	map_section = 0;

	while (file[i])
	{
		while (file[i] && file[i] != '\n')
			i++;
		if(file[i])
		{
			if (file[i + 1] == ' ' || file[i + 1] == '\t')
			{
				i = i + 1;
				while (file[i] == ' ' || file[i] == '\t')
					i++;
			}
			if (!map_section && ((file[i + 1] == '1' || file[i + 1] == '0') || (file[i] == '1' || file[i] == '0')))
				map_section = 1;
			if (map_section && file[i] == '\n' && file[i + 1] == '\n')
			{
				ft_putendl_fd("Error: Multiple consecutive newlines in map.", 2);
				return (1);
			}
			if (file[i] == '\n')
				i++;
		}
	}
	return (0);
}

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

int	check_file_data(char *array)
{
	int	i;

	i = 0;
	while (array[i] == ' ' || array[i] == '\t')
		i++;
	if (array[i] == '1' || array[i] == '0')
		return (0);
	
	if (ft_strncmp(&array[i], "NO", 2) != 0 && ft_strncmp(&array[i], "SO", 2) != 0 && 
		ft_strncmp(&array[i], "WE", 2) != 0 && ft_strncmp(&array[i], "EA", 2) != 0 && 
		ft_strncmp(&array[i], "F ", 2) != 0 && ft_strncmp(&array[i], "C ", 2) != 0)
		{
			ft_putendl_fd("Error: Wrong data in a file.", 2);
			return (1);
		}
	return (0);
}

int	find_map_start(char *line)
{
	int i;

	i = 0;
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