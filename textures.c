#include "cub.h"

// Allocate memory for textures
int	allocate_texture_memory(t_cub *cub)
{
	cub->txt = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 5);
	if (!cub->txt)
	{
		ft_putendl_fd("Can't allocate memory for textures!", 2);
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
	if (load_texture(&cub->txt[1], cub->NO_array,
			"Failed to load the North texture")
		|| load_texture(&cub->txt[3], cub->SO_array,
			"Failed to load the South texture")
		|| load_texture(&cub->txt[2], cub->WE_array,
			"Failed to load the West texture")
		|| load_texture(&cub->txt[0], cub->EA_array,
			"Failed to load the East texture"))
	{
		return (1);
	}
	return (0);
}
