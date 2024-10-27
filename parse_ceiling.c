/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:47:21 by epolkhov          #+#    #+#             */
/*   Updated: 2024/10/27 19:30:34 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int extract_ceiling_color(char *line, int *start, int *i)
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

static int allocate_ceiling_array(t_cub *cub, char *line, int start, int i)
{
	cub->c_array = malloc(i - start + 1);
	if (!cub->c_array)
	{
		ft_putendl_fd("Error: Failed to allocate memory.", 2);
		return (-1);
	}
	int j = 0;
	while (start < i)
		cub->c_array[j++] = line[start++];
	cub->c_array[j] = '\0';
	return (0);
}

static int handle_whitespace(int *i, char *line)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	return (*i);
}

int	ceiling_array(char *line, t_cub *cub)
{
	int	i;
	int	start;

	i = 0;
	i = handle_whitespace(&i, line);
	if (ft_strncmp(&line[i], "C ", 2) == 0 && cub->flags.c_flag == 0)
	{
		i = handle_whitespace(&i, line);
		start = i;
		if (extract_ceiling_color(line, &start, &i) == -1)
			return (1);
		if (allocate_ceiling_array(cub, line, start, i) == -1)
            return (1);
		if (split_to_rgb_ceiling(cub->c_array, cub) == 1)
			return (1);
		cub->flags.c_flag = 1;
		return (0);
	}
	if (ft_strncmp(&line[i], "C ", 2) == 0 && cub->flags.c_flag == 1)
	{
		ft_putendl_fd("Error: Invalid map content.", 2);
		return (1);
	}
	return (0);
}
