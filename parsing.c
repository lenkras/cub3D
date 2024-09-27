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

void	north_array(char *line, t_cub *cub)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		while(line[i] && (line[i] != '.' && line[i] != '/'))
			i++;
		start = i;
		while (line[i] && line[i] != ' ' && line[i] != '\n')
			i++;
		cub->NO_array = malloc(i - start + 1);
		if (!cub->NO_array)
		{
			perror("Failed to allocate mamory.");
			return ;
		}
		j = 0;
		while (start < i)
			cub->NO_array[j++] = line[start++];
		cub->NO_array[j] = '\0';
		printf("NO_array: %s\n", cub->NO_array);
	}
}

void	south_array(char *line, t_cub *cub)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	if (ft_strncmp(line, "SO", 2) == 0)
	{
		while(line[i] && (line[i] != '.' && line[i] != '/'))
			i++;
		start = i;
		while (line[i] && line[i] != ' ' && line[i] != '\n')
			i++;
		cub->SO_array = malloc(i - start + 1);
		if (!cub->NO_array)
		{
			perror("Failed to allocate mamory.");
			return ;
		}
		j = 0;
		while (start < i)
			cub->SO_array[j++] = line[start++];
		cub->SO_array[j] = '\0';
		printf("SO_array: %s\n", cub->SO_array);
	}
}

void	west_array(char *line, t_cub *cub)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		while(line[i] && (line[i] != '.' && line[i] != '/'))
			i++;
		start = i;
		while (line[i] && line[i] != ' ' && line[i] != '\n')
			i++;
		cub->WE_array = malloc(i - start + 1);
		if (!cub->NO_array)
		{
			perror("Failed to allocate mamory.");
			return ;
		}
		j = 0;
		while (start < i)
			cub->WE_array[j++] = line[start++];
		cub->WE_array[j] = '\0';
		printf("WE_array: %s\n", cub->WE_array);
	}
}

void	east_array(char *line, t_cub *cub)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	if (ft_strncmp(line, "EA", 2) == 0)
	{
		while(line[i] && (line[i] != '.' && line[i] != '/'))
			i++;
		start = i;
		while (line[i] && line[i] != ' ' && line[i] != '\n')
			i++;
		cub->EA_array = malloc(i - start + 1);
		if (!cub->EA_array)
		{
			perror("Failed to allocate mamory.");
			return ;
		}
		j = 0;
		while (start < i)
			cub->EA_array[j++] = line[start++];
		cub->EA_array[j] = '\0';
		printf("EA_array: %s\n", cub->EA_array);
	}
}

void	split_toRGB_floor(char *array, t_cub *cub)
{
	char	**rgb_arr;
	int		rgb_val[3];
	int		i;

	i = 0;
	rgb_arr = ft_split(array, ',');
	if (!rgb_arr)
	{
		perror("Failed to split by comma.");
		return ;
	}
	while(rgb_arr[i] && i < 3)
	{
		rgb_val[i] = ft_atoi(rgb_arr[i]);
		if (rgb_val[i] < 0 || rgb_val[i] > 255)
		{
			perror("Error: RGB value out of range (0-255).\n");
			free_array(rgb_arr);
			return ;
		}
		i++;
	}
	if (i != 3)
	{
		perror("Invalid number of values.\n");
		free_array(rgb_arr);
		return ;
	}
	cub->F_R = rgb_val[0];
	cub->F_G = rgb_val[1];
	cub->F_B = rgb_val[2];
	printf("F_R:  %d, F_G: %d, F_B: %d\n", cub->F_R, cub->F_G, cub->F_B);
	free_array(rgb_arr);
}

void	split_toRGB_ceiling(char *array, t_cub *cub)
{
	char	**rgb_arr;
	int		rgb_val[3];
	int		i;

	i = 0;
	rgb_arr = ft_split(array, ',');
	if (!rgb_arr)
	{
		perror("Failed to split by comma.");
		return ;
	}
	while(rgb_arr[i] && i < 3)
	{
		rgb_val[i] = ft_atoi(rgb_arr[i]);
		if (rgb_val[i] < 0 || rgb_val[i] > 255)
		{
			perror("Error: RGB value out of range (0-255).\n");
			free_array(rgb_arr);
			return ;
		}
		i++;
	}
	if (i != 3)
	{
		perror("Invalid number of values.\n");
		free_array(rgb_arr);
		return ;
	}
	cub->C_R = rgb_val[0];
	cub->C_G = rgb_val[1];
	cub->C_B = rgb_val[2];
	printf("C_R:  %d, C_G: %d, C_B: %d\n", cub->C_R, cub->C_G, cub->C_B);
	free_array(rgb_arr);
}

void	floor_array(char *line, t_cub *cub)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		while (line[i] && ft_isdigit(line[i]) != 1)
			i++;
		start = i;
		while (line[i] && line[i] != ' ' && line[i] != '\n')
			i++;
		cub->F_array = malloc(i - start + 1);
		if (!cub->F_array)
		{
			perror("Failed to allocate mamory.");
			return ;
		}
		j = 0;
		while (start < i)
			cub->F_array[j++] = line[start++];
		cub->F_array[j] = '\0';
		printf("F_array: %s\n", cub->F_array);
		split_toRGB_floor(cub->F_array, cub);
	}
}

void	ceiling_array(char *line, t_cub *cub)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		while (line[i] && ft_isdigit(line[i]) != 1)
			i++;
		start = i;
		while (line[i] && line[i] != ' ' && line[i] != '\n')
			i++;
		cub->C_array = malloc(i - start + 1);
		if (!cub->C_array)
		{
			perror("Failed to allocate mamory.");
			return ;
		}
		j = 0;
		while (start < i)
			cub->C_array[j++] = line[start++];
		cub->C_array[j] = '\0';
		printf("C_aray: %s\n", cub->C_array);
		split_toRGB_ceiling(cub->C_array, cub);
	}
}

void	copy_map(char **array, t_cub *cub, int start)
{
	int	i;
	int j;

	i = start;
	j = 0;
	cub->hight = 0;
	while(array[i])
	{
		cub->hight++;
		i++;
	}
	cub->map = malloc(sizeof(char *) * cub->hight + 1);
	if (!cub->map)
	{
		perror("Failed to allocate mamory.");
		return ;
	}
	i = start;
	while (j < cub->hight)
	{
		cub->map[j] = ft_strdup(array[i]);
		if (!cub->map[j])
		{
			perror("Failed to duplicate map line.");
			return ;
		}
		j++;
		i++;
	}
	cub->map[cub->hight] = NULL;
}

int	find_map_start(char *line)
{
	while(*line)
	{
		if (*line != '1' && *line != '0')
			return(0);
		line++;
	}
	return (1);
}
