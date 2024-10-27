/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parrse_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-27 14:48:47 by epolkhov          #+#    #+#             */
/*   Updated: 2024-10-27 14:48:47 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int extract_floor_color(char *line, int *start, int *i)
{
	while (line[*i] && !ft_isdigit(line[*i]))
		(*i)++;
	*start = *i;
	while (line[*i] && line[*i] != '\n')
	{
		if (!ft_isdigit(line[*i]) && line[*i] != ',' && line[*i] != ' ' && line[*i] != '\t')
		{
			ft_putendl_fd("Error: Invalid file content, no spaces and characters allowed.", 2);
			return (-1);
		}
		(*i)++;
	}
	return (0);
}

static int allocate_floor_array(t_cub *cub, char *line, int start, int i)
{
	cub->F_array = malloc(i - start + 1);
	if (!cub->F_array)
	{
		ft_putendl_fd("Error: Failed to allocate memory.", 2);
		return (-1);
	}
	int j = 0;
	while (start < i)
		cub->F_array[j++] = line[start++];
	cub->F_array[j] = '\0';
	return (0);
}

static int handle_whitespace(int *i, char *line)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	return (*i);
}

int	floor_array(char *line, t_cub *cub)
{
	int	i;
	int	start;

	i = 0;
	i = handle_whitespace(&i, line);
	if (ft_strncmp(&line[i], "F ", 2) == 0 && cub->flags.F_flag == 0)
	{
		i = handle_whitespace(&i, line);
		start = i;
		if (extract_floor_color(line, &start, &i) == -1)
			return (1);
		if (allocate_floor_array(cub, line, start, i) == -1)
            return (1);
		if (split_toRGB_floor(cub->F_array, cub) == 1)
			return (1);
		cub->flags.F_flag = 1;
		return (0);
	}
	if (ft_strncmp(&line[i], "F ", 2) == 0 && cub->flags.F_flag == 1)
	{
		ft_putendl_fd("Error: Invalid map content.", 2);
		return (1);
	}
	return (0);
}
