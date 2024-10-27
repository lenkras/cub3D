/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:17:36 by epolkhov          #+#    #+#             */
/*   Updated: 2024/10/14 21:15:57 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"



int main(int argc, char **argv)
{
	t_cub cub;

	if (argc != 2)
	{
		ft_putendl_fd("Error: Wrong number of arguments.", 2);
		return (1);
	}
	if (check_format(argv[1]) == 1)
		return (1);
	else
	{
		cub.file = open_file(argv[1]);
		if (!cub.file || cub.file[0] == '\0')
		{
			ft_putendl_fd("Error: Failed to open or read file.", 2);
			return (1);
		}
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
	game(&cub);
	free_all(&cub);
	destroy_textures(&cub);
	return (0);
}
