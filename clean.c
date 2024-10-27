/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-26 17:26:42 by epolkhov          #+#    #+#             */
/*   Updated: 2024-10-26 17:26:42 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_all(t_cub *cub)
{
	if (cub->map)
		free_array(cub->map);
	if (cub->file)
		free(cub->file);
	if (cub->NO_array)
		free(cub->NO_array);
	if (cub->SO_array)
		free (cub->SO_array);
	if (cub->WE_array)
		free(cub->WE_array);
	if (cub->EA_array)
		free(cub->EA_array);
	if (cub->F_array)
		free(cub->F_array);
	if (cub->C_array)
		free(cub->C_array);
}

void	destroy_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->txt[i])
		{
			mlx_delete_texture(cub->txt[i]);
			cub->txt[i] = NULL;
		}
		i++;
	}
	free(cub->txt);
	cub->txt = NULL;
	if (cub->img)
	{
		mlx_delete_image(cub->mlx, cub->img);
		cub->img = NULL;
	}
	mlx_terminate(cub->mlx);
}
