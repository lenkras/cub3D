/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:26:42 by epolkhov          #+#    #+#             */
/*   Updated: 2024/10/27 19:22:08 by dlevinsc         ###   ########.fr       */
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
	if (cub->no_array)
		free(cub->no_array);
	if (cub->so_array)
		free (cub->so_array);
	if (cub->we_array)
		free(cub->we_array);
	if (cub->ea_array)
		free(cub->ea_array);
	if (cub->f_array)
		free(cub->f_array);
	if (cub->c_array)
		free(cub->c_array);
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
