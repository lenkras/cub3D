/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_north_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:51:00 by epolkhov          #+#    #+#             */
/*   Updated: 2024/10/27 21:11:59 by dlevinsc         ###   ########.fr       */
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
	return (0);
}

static int	allocate_north_array(t_cub *cub, char *cut_str, int len)
{
	cub->no_array = malloc(len + 1);
	if (!cub->no_array)
	{
		ft_putendl_fd("Error: Failed to allocate memory.", 2);
		free(cut_str);
		return (1);
	}
	ft_strlcpy(cub->no_array, cut_str, len + 1);
	return (0);
}

static int	parse_north(char *line, int *i, t_cub *cub)
{
	char	*cut_str;

	cut_str = extract_file_path(line, i);
	if (!cut_str)
		return (1);
	if (validate_file_path(cut_str))
		return (1);
	if (allocate_north_array(cub, cut_str, ft_strlen(cut_str)))
	{
		free(cut_str);
		return (1);
	}
	ft_strlcpy(cub->no_array, cut_str, ft_strlen(cut_str) + 1);
	cub->flags.no_flag = 1;
	free(cut_str);
	return (0);
}

int	north_array(char *line, t_cub *cub)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0 && cub->flags.no_flag == 0)
	{
		i += 2;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		return (parse_north(line, &i, cub));
	}
	if (ft_strncmp(&line[i], "NO", 2) == 0 && cub->flags.no_flag == 1)
	{
		ft_putendl_fd("Error: Invalid map content.", 2);
		return (1);
	}
	return (0);
}
