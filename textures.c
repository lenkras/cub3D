/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-27 19:05:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024-10-27 19:05:26 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// Allocate memory for textures
int	allocate_texture_memory(t_cub *cub)
{
	cub->txt = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 5);
	if (!cub->txt)
	{
		ft_putendl_fd("Error\nFailed to allocate memory.", 2);
		return (1);
	}
	return (0);
}

// Load a texture from the specified file path
int	load_texture(mlx_texture_t **texture, const char *filepath,
		const char *error_message)
{
	*texture = mlx_load_png(filepath);
	if (!(*texture))
	{
		ft_putendl_fd((char *)error_message, 2);
		return (1);
	}
	return (0);
}

// Load all textures into the cub structure
int	load_textures(t_cub *cub)
{
	if (allocate_texture_memory(cub))
		return (1);
	if (load_texture(&cub->txt[1], cub->no_array,
			"Failed to load the North texture")
		|| load_texture(&cub->txt[3], cub->so_array,
			"Failed to load the South texture")
		|| load_texture(&cub->txt[2], cub->we_array,
			"Failed to load the West texture")
		|| load_texture(&cub->txt[0], cub->ea_array,
			"Failed to load the East texture"))
	{
		return (1);
	}
	return (0);
}
