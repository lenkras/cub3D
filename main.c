/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-25 11:17:36 by epolkhov          #+#    #+#             */
/*   Updated: 2024-09-25 11:17:36 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_format(char *file_name)
{
	char	*compare;

	compare = ft_strrchr(file_name, '.');
	if (!compare)
	{
		perror("Error: Invalid map file extansion.");
		return (1);
	}
	if (ft_strncmp(compare, ".cub", 5) != 0)
	{
		perror("Error: Invalid map file extansion.");
		return (1) ;
	}
	return (0);
}

int	split_by_new_line(t_cub *cub)
{
	char	**array;
	int		i;

	i = 0;
	array = ft_split(cub->file, '\n');
	if (!array)
	{
		perror("Error: Failed to split by new line.");
		return (1);
	}
	for (int i = 0; array[i] != NULL; i++)
		printf("splited str %d: %s\n", i, array[i]);
	init_flag_struct(cub);
	while (array[i])
	{
		if (north_array(array[i], cub) == 1 || south_array(array[i], cub) == 1 || west_array(array[i], cub) == 1 ||
			east_array(array[i], cub) == 1 || floor_array(array[i], cub) == 1 || ceiling_array(array[i], cub) == 1)
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
		perror("Error: Wrong number of arguments.");
		return (1);
	}
	if (check_format(argv[1]) == 1)
		return (1);
	else
	{
		cub.file = open_file(argv[1]);
		printf("%s\n",cub.file);
		if (!cub.file)
		{
			perror("Error: Failed to open or read file.");
			return (1);
		}
		init_main_struct(&cub);
		if (split_by_new_line(&cub) == 1)
			return (1);
	}
	printf("Map:\n");
    for (int i = 0; cub.map && cub.map[i] != NULL; i++)
    {
        printf("%s\n", cub.map[i]);
    }
	//cub = malloc(sizeof(cub));
	// parsing(&cub);
	// check_validity(cub);
	// init_map(cub);
	// game(cub);
	// destroy(&cub);
	free(cub.file);
	return (0);
}
