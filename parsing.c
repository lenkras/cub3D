/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 09:08:33 by epolkhov          #+#    #+#             */
/*   Updated: 2024/10/27 21:12:16 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	parse_array(char **array, t_cub *cub)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (check_file_data(array[i]) == 1)
		{
			free_array(array);
			return (-1);
		}
		if (north_array(array[i], cub) || south_array(array[i], cub) || \
			west_array(array[i], cub) || east_array(array[i], cub) || \
			floor_array(array[i], cub) || ceiling_array(array[i], cub))
		{
			free_array(array);
			return (-1);
		}
		if (find_map_start(array[i]))
			break ;
		i++;
	}
	return (i);
}

int	split_by_new_line(t_cub *cub)
{
	char	**array;
	int		i;

	if (check_consecutive_newlines_in_map(cub->file) == 1)
		return (1);
	array = ft_split(cub->file, '\n');
	if (!array)
	{
		ft_putendl_fd("Error\nFailed to split by new line.", 2);
		return (1);
	}
	init_flag_struct(cub);
	i = parse_array(array, cub);
	if (i == -1)
		return (1);
	if (check_all_flags_infile(cub) == 1)
	{
		free_array(array);
		return (1);
	}
	copy_map(array, cub, i);
	free_array(array);
	return (0);
}

static void	make_copy_of_array(t_cub *cub, char **array, int i)
{
	int	j;

	j = 0;
	while (j < cub->height)
	{
		cub->map[j] = ft_strdup(array[i]);
		if (!cub->map[j])
		{
			ft_putendl_fd("Error\nFailed to duplicate map line.", 2);
			while (j > 0)
				free(cub->map[--j]);
			free(cub->map);
			return ;
		}
		j++;
		i++;
	}
	cub->map[cub->height] = NULL;
}

void	copy_map(char **array, t_cub *cub, int start)
{
	int	i;

	i = start;
	cub->height = 0;
	if (!array[i])
		return ;
	while (array[i])
	{
		cub->height++;
		i++;
	}
	cub->map = malloc(sizeof(char *) * (cub->height + 1));
	if (!cub->map)
	{
		ft_putendl_fd("Error\nFailed to allocate mamory.", 2);
		return ;
	}
	i = start;
	make_copy_of_array(cub, array, i);
}
