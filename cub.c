/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:17:36 by epolkhov          #+#    #+#             */
/*   Updated: 2024/11/11 21:57:59 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	handle_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd("Error: Wrong number of arguments.", 2);
		return (1);
	}
	if (check_format(argv[1]) == 1)
		return (1);
	return (0);
}

static int	create_file(t_cub *cub, char *filename)
{
	cub->file = open_file(filename);
	if (!cub->file || cub->file[0] == '\0')
	{
		if (cub->file)
			free(cub->file);
		ft_putendl_fd("Error: Failed to open or read file.", 2);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (handle_arguments(argc, argv) == 1)
		return (1);
	else
	{
		if (create_file(&cub, argv[1]) == 1)
			return (1);
		init_main_struct(&cub);
		if (split_by_new_line(&cub) == 1)
		{
			free_all(&cub);
			return (1);
		}
	}
	if (is_map_valid(&cub) == 1)
	{
		free_all(&cub);
		return (1);
	}
	mirror_map(&cub);
	game(&cub);
	free_all(&cub);
	destroy_textures(&cub);
	return (0);
}
