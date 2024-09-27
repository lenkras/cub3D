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

int	check_all_flags_infile(t_cub *cub)
{
	if (cub->flags.C_flag == 1 && cub->flags.EA_flag == 1 && cub->flags.F_flag == 1 && cub->flags.NO_flag == 1 &&
		cub->flags.SO_flag == 1 && cub->flags.WE_flag == 1)
		return (0);
	else 
	{
		perror("Error: One or more configuration options are missing.");
		return (1);
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
		perror("Error: Failed to allocate mamory.");
		return ;
	}
	i = start;
	while (j < cub->hight)
	{
		cub->map[j] = ft_strdup(array[i]);
		if (!cub->map[j])
		{
			perror("Error: Failed to duplicate map line.");
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
