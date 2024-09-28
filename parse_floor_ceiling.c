/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_ceiling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-27 11:35:59 by epolkhov          #+#    #+#             */
/*   Updated: 2024-09-27 11:35:59 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	split_toRGB_floor(char *array, t_cub *cub)
{
	char	**rgb_arr;
	int		rgb_val[3];
	int		i;

	i = 0;
	rgb_arr = ft_split(array, ',');
	if (!rgb_arr)
	{
		ft_putendl_fd("Error: Failed to split by comma.", 2);
		return (1);
	}
	while(rgb_arr[i] && i < 3)
	{
		rgb_val[i] = ft_atoi(rgb_arr[i]);
		if (rgb_val[i] < 0 || rgb_val[i] > 255)
		{
			ft_putendl_fd("Error: RGB value out of range (0-255).\n", 2);
			free_array(rgb_arr);
			return (1);
		}
		i++;
	}
	if (i != 3)
	{
		ft_putendl_fd("Error: Invalid number of values.\n", 2);
		free_array(rgb_arr);
		return (1);
	}
	cub->F_R = rgb_val[0];
	cub->F_G = rgb_val[1];
	cub->F_B = rgb_val[2];
	printf("F_R:  %d, F_G: %d, F_B: %d\n", cub->F_R, cub->F_G, cub->F_B);
	free_array(rgb_arr);
	return (0);
}

int	split_toRGB_ceiling(char *array, t_cub *cub)
{
	char	**rgb_arr;
	int		rgb_val[3];
	int		i;

	i = 0;
	rgb_arr = ft_split(array, ',');
	if (!rgb_arr)
	{
		ft_putendl_fd("Error: Failed to split by comma.", 2);
		return (1);
	}
	while(rgb_arr[i] && i < 3)
	{
		rgb_val[i] = ft_atoi(rgb_arr[i]);
		if (rgb_val[i] < 0 || rgb_val[i] > 255)
		{
			ft_putendl_fd("Error: RGB value out of range (0-255).\n", 2);
			free_array(rgb_arr);
			return (1);
		}
		i++;
	}
	if (i != 3)
	{
		ft_putendl_fd("Error: Invalid number of values.\n", 2);
		free_array(rgb_arr);
		return (1);
	}
	cub->C_R = rgb_val[0];
	cub->C_G = rgb_val[1];
	cub->C_B = rgb_val[2];
	printf("C_R:  %d, C_G: %d, C_B: %d\n", cub->C_R, cub->C_G, cub->C_B);
	free_array(rgb_arr);
	return (0);
}

int	floor_array(char *line, t_cub *cub)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	if (ft_strncmp(line, "F ", 2) == 0 && cub->flags.F_flag == 0)
	{
		while (line[i] && !ft_isdigit(line[i]))
			i++;
		start = i;
		while (line[i] && line[i] != '\n')
		{
			if (has_space(line[i]) || (!ft_isdigit(line[i]) && line[i] != ','))
			{
				ft_putendl_fd("Error: Invalid file content, no spaces and characters allowed.", 2);
				return (1);
			}
			i++;
		}
		cub->F_array = malloc(i - start + 1);
		if (!cub->F_array)
		{
			ft_putendl_fd("Error: Failed to allocate memory.", 2);
			return (1);
		}
		j = 0;
		while (start < i)
			cub->F_array[j++] = line[start++];
		cub->F_array[j] = '\0';
		printf("F_array: %s\n", cub->F_array);
		if (split_toRGB_floor(cub->F_array, cub) == 1)
			return (1);
		cub->flags.F_flag = 1;
		return (0);
	}
	if (ft_strncmp(line, "F ", 2) == 0 && cub->flags.F_flag == 1)
	{
		ft_putendl_fd("Error: Invalid map content.", 2);
		return (1);
	}
	return (0);
}

int	ceiling_array(char *line, t_cub *cub)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	if (ft_strncmp(line, "C ", 2) == 0 && cub->flags.C_flag == 0)
	{
		while (line[i] && !ft_isdigit(line[i]))
			i++;
		start = i;
		while (line[i] && line[i] != '\n')
		{
			if (has_space(line[i]) || (!ft_isdigit(line[i]) && line[i] != ','))
			{
				ft_putendl_fd("Error: Invalid file content, no spaces and characters allowed.", 2);
				return (1);
			}
			i++;
		}
		cub->C_array = malloc(i - start + 1);
		if (!cub->C_array)
		{
			ft_putendl_fd("Error: Failed to allocate memory.", 2);
			return (1);
		}
		j = 0;
		while (start < i)
			cub->C_array[j++] = line[start++];
		cub->C_array[j] = '\0';
		printf("C_aray: %s\n", cub->C_array);
		if (split_toRGB_ceiling(cub->C_array, cub) == 1)
			return (1);
		cub->flags.C_flag = 1;
		return (0);
	}
	if (ft_strncmp(line, "C ", 2) == 0 && cub->flags.C_flag == 1)
	{
		ft_putendl_fd("Error: Invalid map content.", 2);
		return (1);
	}
	return (0);
}
