/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_east_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-27 14:05:54 by epolkhov          #+#    #+#             */
/*   Updated: 2024-10-27 14:05:54 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	*extract_file_path(char *line, int *i)
{
	int		start;
	int		len;
	char	*cut_str;

	start = *i;
	len = ft_strlen(line + start);
	cut_str = ft_substr(line, start, len);
	if (!cut_str)
	{
		ft_putendl_fd("Error: Failed to extract file path.", 2);
		return (NULL);
	}
	return (cut_str);
}

static int	validate_file_path(char *cut_str)
{
	if (ft_strncmp(cut_str, "pattern/east_wall.png", 22) != 0)
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
	return (0);
}

static int	allocate_east_array(t_cub *cub, char *cut_str, int len)
{
	cub->EA_array = malloc(len + 1);
	if (!cub->EA_array)
	{
		ft_putendl_fd("Error: Failed to allocate memory.", 2);
		free(cut_str);
		return (1);
	}
	ft_strlcpy(cub->EA_array, cut_str, len + 1);
	return (0);
}

static int	parse_east(char *line, int *i, t_cub *cub)
{
	char	*cut_str;

	cut_str = extract_file_path(line, i);
	if (!cut_str)
		return (1);
	if (validate_file_path(cut_str))
		return (1);
	if (allocate_east_array(cub, cut_str, ft_strlen(cut_str)))
	{
		free(cut_str);
		return (1);
	}
	ft_strlcpy(cub->EA_array, cut_str, ft_strlen(cut_str) + 1);
	cub->flags.EA_flag = 1;
	free(cut_str);
	return (0);
}

int	east_array(char *line, t_cub *cub)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "EA", 2) == 0 && cub->flags.EA_flag == 0)
	{
		i += 2;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		return (parse_east(line, &i, cub));
	}
	if (ft_strncmp(&line[i], "EA", 2) == 0 && cub->flags.EA_flag == 1)
	{
		ft_putendl_fd("Error: Invalid map content.", 2);
		return (1);
	}
	return (0);
}
