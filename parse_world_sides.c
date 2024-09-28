/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_world_sides.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-27 11:47:45 by epolkhov          #+#    #+#             */
/*   Updated: 2024-09-27 11:47:45 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	north_array(char *line, t_cub *cub)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	if (ft_strncmp(line, "NO", 2) == 0 && cub->flags.NO_flag == 0)
	{
		while(line[i] && (line[i] != '.' && line[i + 1] != '/'))
			i++;
		start = i;
		while (line[i] && line[i] != '\n')
		{
			if (has_space(line[i]))
			{
				ft_putendl_fd("Error: Invalid file content, has space where not expected.", 2);
				return (1);
			}
			i++;
		}
		cub->NO_array = malloc(i - start + 1);
		if (!cub->NO_array)
		{
			ft_putendl_fd("Error: Failed to allocate mamory.", 2);
			return (1);
		}
		j = 0;
		while (start < i)
			cub->NO_array[j++] = line[start++];
		cub->NO_array[j] = '\0';
		printf("NO_array: %s\n", cub->NO_array);
		cub->flags.NO_flag = 1;
		return (0);
	}
	if (ft_strncmp(line, "NO", 2) == 0 && cub->flags.NO_flag == 1)
	{
		ft_putendl_fd("Error: Invalid map content.", 2);
		return (1);
	}
	return (0);
}

int	south_array(char *line, t_cub *cub)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	if (ft_strncmp(line, "SO", 2) == 0 && cub->flags.SO_flag == 0)
	{
		while(line[i] && (line[i] != '.' && line[i + 1] != '/'))
			i++;
		start = i;
		while (line[i] && line[i] != '\n')
		{
			if (has_space(line[i]))
			{
				ft_putendl_fd("Error: Invalid file content, has space where not expected.", 2);
				return (1);
			}
			i++;
		}
		cub->SO_array = malloc(i - start + 1);
		if (!cub->NO_array)
		{
			ft_putendl_fd("Error: Failed to allocate mamory.", 2);
			return (1);
		}
		j = 0;
		while (start < i)
			cub->SO_array[j++] = line[start++];
		cub->SO_array[j] = '\0';
		printf("SO_array: %s\n", cub->SO_array);
		cub->flags.SO_flag = 1;
		return (0);
	}
	if (ft_strncmp(line, "SO", 2) == 0 && cub->flags.SO_flag == 1)
	{
		ft_putendl_fd("Error: Invalid map content.", 2);
		return (1);
	}
	return (0);
}

int	west_array(char *line, t_cub *cub)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	if (ft_strncmp(line, "WE", 2) == 0 && cub->flags.WE_flag == 0)
	{
		while(line[i] && (line[i] != '.' && line[i + 1] != '/'))
			i++;
		start = i;
		while (line[i] && line[i] != '\n')
		{
			if (has_space(line[i]))
			{
				ft_putendl_fd("Error: Invalid file content, has space where not expected.", 2);
				return (1);
			}
			i++;
		}
		cub->WE_array = malloc(i - start + 1);
		if (!cub->NO_array)
		{
			ft_putendl_fd("Error: Failed to allocate mamory.", 2);
			return (1);
		}
		j = 0;
		while (start < i)
			cub->WE_array[j++] = line[start++];
		cub->WE_array[j] = '\0';
		printf("WE_array: %s\n", cub->WE_array);
		cub->flags.WE_flag = 1;
		return (0);
	}
	if (ft_strncmp(line, "WE", 2) == 0 && cub->flags.WE_flag == 0)
	{
		ft_putendl_fd("Error: Invalid map content.", 2);
		return (1);
	}
	return (0);
}

int	east_array(char *line, t_cub *cub)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	if (ft_strncmp(line, "EA", 2) == 0 && cub->flags.EA_flag == 0)
	{
		while(line[i] && (line[i] != '.' && line[i + 1] != '/'))
			i++;
		if(line[i] == '.' && line[i + 1] == '/')
		{
			start = i;
			while (line[i] && line[i] != '\n')
			{
				if (has_space(line[i]))
				{
					ft_putendl_fd("Error: Invalid file content, has space where not expected.", 2);
					return (1);
				}
				i++;
			}
			cub->EA_array = malloc(i - start + 1);
			if (!cub->EA_array)
			{
				ft_putendl_fd("Error: Failed to allocate mamory.", 2);
				return (1);
			}
			j = 0;
			while (start < i && line[start] != ' ')
				cub->EA_array[j++] = line[start++];
			cub->EA_array[j] = '\0';
			printf("EA_array: %s\n", cub->EA_array);
			cub->flags.EA_flag = 1;
			return (0);
		}
		else
		{
			ft_putendl_fd("Error: Invalid file content.", 2);
			return (1);
		}
	}
	if (ft_strncmp(line, "EA", 2) == 0 && cub->flags.EA_flag == 1)
	{
		ft_putendl_fd("Error: Invalid map content.", 2);
		return (1);
	}
	return (0);
}
