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

static int validate_rgb_values_floor(char **rgb_arr, t_cub *cub)
{
	int rgb_val[3];
	int i = 0;

	while (i < 3)
	{
		if (!rgb_arr[i])
			return (1);
		rgb_val[i] = ft_atoi(rgb_arr[i]);
		if (rgb_val[i] < 0 || rgb_val[i] > 255)
		{
			ft_putendl_fd("Error: RGB value out of range (0-255).\n", 2);
			return (1);
		}
		i++;
	}
	cub->F_R = rgb_val[0];
	cub->F_G = rgb_val[1];
	cub->F_B = rgb_val[2];
	printf("F_R:  %d, F_G: %d, F_B: %d\n", cub->F_R, cub->F_G, cub->F_B);
	return (0);
}

int	split_toRGB_floor(char *array, t_cub *cub)
{
	char	**rgb_arr;

	rgb_arr = ft_split(array, ',');
	if (!rgb_arr)
	{
		ft_putendl_fd("Error: Failed to split by comma.", 2);
		return (1);
	}
	if (rgb_arr[3])
	{
		ft_putendl_fd("Error: Invalid number of values.\n", 2);
		free_array(rgb_arr);
		return (1);
	}
	if (validate_rgb_values_floor(rgb_arr, cub))
	{
		free_array(rgb_arr);
		return (1);
	}
	free_array(rgb_arr);
	return (0);
}

static int validate_rgb_values_ceiling(char **rgb_arr, t_cub *cub)
{
	int rgb_val[3];
	int i = 0;

	while (i < 3)
	{
		if (!rgb_arr[i])
			return (1);
		rgb_val[i] = ft_atoi(rgb_arr[i]);
		if (rgb_val[i] < 0 || rgb_val[i] > 255)
		{
			ft_putendl_fd("Error: RGB value out of range (0-255).\n", 2);
			return (1);
		}
		i++;
	}
	cub->C_R = rgb_val[0];
	cub->C_G = rgb_val[1];
	cub->C_B = rgb_val[2];
	return (0);
}

int	split_toRGB_ceiling(char *array, t_cub *cub)
{
	char	**rgb_arr;

	rgb_arr = ft_split(array, ',');
	if (!rgb_arr)
	{
		ft_putendl_fd("Error: Failed to split by comma.", 2);
		return (1);
	}
	if (rgb_arr[3])
	{
		ft_putendl_fd("Error: Invalid number of values.\n", 2);
		free_array(rgb_arr);
		return (1);
	}
	if (validate_rgb_values_ceiling(rgb_arr, cub))
	{
		free_array(rgb_arr);
		return (1);
	}
	free_array(rgb_arr);
	return (0);
}

