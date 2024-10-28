/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_south_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:53:32 by epolkhov          #+#    #+#             */
/*   Updated: 2024/10/27 19:20:20 by dlevinsc         ###   ########.fr       */
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
		ft_putendl_fd("Error\nFailed to extract file path.", 2);
		return (NULL);
	}
	return (cut_str);
}

static int validate_file_path(char *cut_str)
{
	int fd;

	fd = open(cut_str, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error:\nFile does not exist or cannot be opened.", 2);
		free(cut_str);
		return (1);
	}
	close(fd);
	return (0);
}

static int	allocate_south_array(t_cub *cub, char *cut_str, int len)
{
	cub->so_array = malloc(len + 1);
	if (!cub->so_array)
	{
		ft_putendl_fd("Error\nFailed to allocate memory.", 2);
		free(cut_str);
		return (1);
	}
	ft_strlcpy(cub->so_array, cut_str, len + 1);
	return (0);
}

static int	parse_south(char *line, int *i, t_cub *cub)
{
	char	*cut_str;

	cut_str = extract_file_path(line, i);
	if (!cut_str)
		return (1);
	if (validate_file_path(cut_str))
		return (1);
	if (allocate_south_array(cub, cut_str, ft_strlen(cut_str)))
	{
		free(cut_str);
		return (1);
	}
	ft_strlcpy(cub->so_array, cut_str, ft_strlen(cut_str) + 1);
	cub->flags.so_flag = 1;
	free(cut_str);
	return (0);
}

int	south_array(char *line, t_cub *cub)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "SO", 2) == 0 && cub->flags.so_flag == 0)
	{
		i += 2;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		return (parse_south(line, &i, cub));
	}
	if (ft_strncmp(&line[i], "SO", 2) == 0 && cub->flags.so_flag == 1)
	{
		ft_putendl_fd("Error\nInvalid map content.", 2);
		return (1);
	}
	return (0);
}
