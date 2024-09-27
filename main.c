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

void	split_by_new_line(t_cub *cub)
{
	char	**array;
	int		i;

	i = 0;
	array = ft_split(cub->file, '\n');
	if (!array)
	{
		perror("Failed to split by new line.");
		return ;
	}
	for (int i = 0; array[i] != NULL; i++)
		printf("splited str %d: %s\n", i, array[i]);
	while (array[i])
	{
		north_array(array[i], cub);
		south_array(array[i], cub);
		west_array(array[i], cub);
		east_array(array[i], cub);
		floor_array(array[i], cub);
		ceiling_array(array[i], cub);
		if (find_map_start(array[i]))
			break ;
		i++;
	}
	copy_map(array, cub, i);
	free_array(array);
}


int main(int argc, char **argv)
{
	t_cub cub;

	if (argc != 2)
	{
		perror("Wrong number of arguments.");
		return (1);
	}
	else
	{
		cub.file = open_file(argv[1]);
		printf("%s\n",cub.file);
		if (!cub.file)
		{
			perror("Failed to open or read file.");
			return (1);
		}
		split_by_new_line(&cub);
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