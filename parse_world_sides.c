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
	int	start;
	char *cut_str;
	int len;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0 && cub->flags.NO_flag == 0)
	{
			i += 2;
			while(line[i] && (line[i] == ' ' || line[i] == '\t'))
				i++;
			start = i;
			len = ft_strlen(line + start);
			cut_str = ft_substr(line, start, len);
			if (!cut_str)
			{
				ft_putendl_fd("Error: Failed to extract file path.", 2);
				return (1);
			}
			if (ft_strncmp(cut_str, "pattern/north_wall.png", 22) != 0)
			{
				ft_putendl_fd("Error: Invalid file path for NO texture.", 2);
				free(cut_str);
				return (1);
			}
			if (check_file_permission(cut_str) == 1)
			{
				free(cut_str);
				return (1);
			}
			cub->NO_array = malloc(len + 1);
			if (!cub->NO_array)
			{
				ft_putendl_fd("Error: Failed to allocate mamory.", 2);
				free(cut_str);
				return (1);
			}
			ft_strlcpy(cub->NO_array, cut_str, len + 1);
			printf("NO_array: %s\n", cub->NO_array);
			cub->flags.NO_flag = 1;
			free(cut_str);
			return (0);
	}
	if (ft_strncmp(&line[i], "NO", 2) == 0 && cub->flags.NO_flag == 1)
	{
		ft_putendl_fd("Error: Invalid map content.", 2);
		return (1);
	}
	return (0);
}

int	south_array(char *line, t_cub *cub)
{
	int	i;
	int	start;
	char *cut_str;
	int len;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "SO", 2) == 0 && cub->flags.SO_flag == 0)
	{
		i += 2;
		while(line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		start = i;
		len = ft_strlen(line + start);
		cut_str = ft_substr(line, start, len);
		if (!cut_str)
		{
			ft_putendl_fd("Error: Failed to extract file path.", 2);
			return (1);
		}
		if (ft_strncmp(cut_str, "pattern/south_wall.png", 22) != 0)
		{
			ft_putendl_fd("Error: Invalid file path for SO texture.", 2);
			free(cut_str);
			return (1);
		}
		if (check_file_permission(cut_str) == 1)
        {
            free(cut_str);
            return (1);
        }
		cub->SO_array = malloc(len + 1);
		if (!cub->SO_array)
		{
			ft_putendl_fd("Error: Failed to allocate mamory.", 2);
			free(cut_str);
			return (1);
		}
		ft_strlcpy(cub->SO_array, cut_str, len + 1);
		printf("SO_array: %s\n", cub->SO_array);
		cub->flags.SO_flag = 1;
		free(cut_str);
		return (0);
	}
	if (ft_strncmp(&line[i], "SO", 2) == 0 && cub->flags.SO_flag == 1)
	{
		ft_putendl_fd("Error: Invalid map content.", 2);
		return (1);
	}
	return (0);
}

int	west_array(char *line, t_cub *cub)
{
	int	i;
	int	len;
	int	start;
	char *cut_str;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "WE", 2) == 0 && cub->flags.WE_flag == 0)
	{
		i += 2;
		while(line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		start = i;
		len = ft_strlen(line + start);
		cut_str = ft_substr(line, start, len);
		if (!cut_str)
		{
			ft_putendl_fd("Error: Failed to extract file path.", 2);
			return (1);
		}
		if (ft_strncmp(cut_str, "pattern/west_wall.png", 21) != 0)
		{
			ft_putendl_fd("Error: Invalid file path for WE texture.", 2);
			free(cut_str);
			return (1);
		}
		if (check_file_permission(cut_str) == 1)
        {
            free(cut_str);
            return (1);
        }
		cub->WE_array = malloc(len + 1);
		if (!cub->SO_array)
		{
			ft_putendl_fd("Error: Failed to allocate mamory.", 2);
			free(cut_str);
			return (1);
		}
		ft_strlcpy(cub->WE_array, cut_str, len + 1);
		printf("WE_array: %s\n", cub->WE_array);
		cub->flags.WE_flag = 1;
		free(cut_str);
		return (0);
	}
	if (ft_strncmp(&line[i], "WE", 2) == 0 && cub->flags.WE_flag == 0)
	{
		ft_putendl_fd("Error: Invalid map content.", 2);
		return (1);
	}
	return (0);
}

int	east_array(char *line, t_cub *cub)
{
	int	i;
	int	len;
	int	start;
	char *cut_str;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "EA", 2) == 0 && cub->flags.EA_flag == 0)
	{
		i += 2;
		while(line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		start = i;
		len = ft_strlen(line + start);
		cut_str = ft_substr(line, start, len);
		if (!cut_str)
		{
			ft_putendl_fd("Error: Failed to extract file path.", 2);
			return (1);
		}
		if (ft_strncmp(cut_str, "pattern/east_wall.png", 21) != 0)
		{
			ft_putendl_fd("Error: Invalid file path for EA texture.", 2);
			free(cut_str);
			return (1);
		}
		if (check_file_permission(cut_str) == 1)
        {
            free(cut_str);
            return (1);
        }
		cub->EA_array = malloc(len + 1);
		if (!cub->EA_array)
		{
			ft_putendl_fd("Error: Failed to allocate mamory.", 2);
			free(cut_str);
			return (1);
		}
		ft_strlcpy(cub->EA_array, cut_str, len + 1);
		printf("EA_array: %s\n", cub->EA_array);
		cub->flags.EA_flag = 1;
		free(cut_str);
		return (0);
	}
	if (ft_strncmp(&line[i], "EA", 2) == 0 && cub->flags.EA_flag == 1)
	{
		ft_putendl_fd("Error: Invalid map content.", 2);
		return (1);
	}
	return (0);
}
