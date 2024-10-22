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

int	check_format(char *file_name)
{
	char	*compare;

	compare = ft_strrchr(file_name, '.');
	if (!compare)
	{
		ft_putendl_fd("Error: Invalid map file extansion.", 2);
		return (1);
	}
	if (ft_strncmp(compare, ".cub", 5) != 0)
	{
		ft_putendl_fd("Error: Invalid map file extansion.", 2);
		return (1) ;
	}
	return (0);
}

int	check_consecutive_newlines_in_map(char *file)
{
	int	i = 0;
	int	map_section = 0;

	while (file[i])
	{
		while (file[i] && file[i] != '\n')
			i++;
		
		if (file[i + 1] == ' ' || file[i + 1] == '\t')
		{
			i = i + 1;
			while (file[i] == ' ' || file[i] == '\t')
				i++;
		}
		if (!map_section && ((file[i + 1] == '1' || file[i + 1] == '0') || (file[i] == '1' || file[i] == '0')))
			map_section = 1;
		if (map_section && file[i] == '\n' && file[i + 1] == '\n')
		{
			ft_putendl_fd("Error: Multiple consecutive newlines in map.", 2);
			return (1);
		}
		if (file[i] == '\n')
			i++;
	}
	return (0);
}

int	split_by_new_line(t_cub *cub)
{
	char	**array;
	int		i;

	if (check_consecutive_newlines_in_map(cub->file) == 1)
		return (1);
	i = 0;
	array = ft_split(cub->file, '\n');
	if (!array)
	{
		ft_putendl_fd("Error: Failed to split by new line.", 2);
		return (1);
	}
	for (int i = 0; array[i] != NULL; i++)
		printf("splited str %d: %s\n", i, array[i]);
	init_flag_struct(cub);
	while (array[i])
	{
		if (north_array(array[i], cub) == 1 || south_array(array[i], cub) == 1 || 
			west_array(array[i], cub) == 1 || east_array(array[i], cub) == 1 || 
			floor_array(array[i], cub) == 1 || ceiling_array(array[i], cub) == 1)
			return (1);
		if (find_map_start(array[i]))
			break ;
		i++;
	}
	if (check_all_flags_infile(cub) == 1)
		return (1);
	copy_map(array, cub, i);
	free_array(array);
	return (0);
}

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
		printf("File\n");
		printf("%s\n",cub.file);
		if (!cub.file || cub.file[0] == '\0')
		{
			ft_putendl_fd("Error: Failed to open or read file.", 2);
			return (1);
		}
		init_main_struct(&cub);
		if (split_by_new_line(&cub) == 1)
			return (1);
	}
	
	is_map_valid(&cub);
	printf("Map:\n");
    for (int i = 0; cub.map && cub.map[i] != NULL; i++)
    {
        printf("%s\n", cub.map[i]);
    }
	//cub = malloc(sizeof(cub));
	// parsing(&cub);
	// check_validity(cub);
	// init_map(cub);
	game(&cub);
	free_all(&cub);
	destroy_textures(&cub);
	return (0);
}
