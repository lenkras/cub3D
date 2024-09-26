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

char *open_file(char *argv)
{
	int		fd;
	char	buf[1024];
	int		bytes_read;
	char	*data;
	int		bytes_total = 0;
	char	*temp;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open a file.");
		return (NULL);
	}
	data = malloc(1);
	if (!data)
	{
		perror("Failed to allocate mamory.");
		close(fd);
		return (NULL);
	}
	data[0] = '\0';
	while ((bytes_read = read(fd, buf, sizeof(buf) - 1)) > 0)
	{
		buf[bytes_read] = '\0';
		bytes_total += bytes_read;
		temp = malloc(bytes_total + 1);
		if (!temp)
		{
			perror("Failed to allocate mamory.");
			free(data);
			close(fd);
			return (NULL);
		}
		strcpy(temp, data);
		strcat(temp, buf);
		free(data);
		data = temp;

	}
	if (bytes_read == -1)
	{
		perror("Failed to read a file.");
		return (NULL);
	}
	close(fd);
	return (data);
}

void	north_array(char *line, t_cub *cub)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		cub->NO_array = malloc(ft_strlen(line) + 1);
		if (!cub->NO_array)
		{
			perror("Failed to allocate mamory.");
			return ;
		}
		strcpy(cub->NO_array, line);
		printf("NO_array: %s\n", cub->NO_array);
	}
}

void	south_array(char *line, t_cub *cub)
{
	if (ft_strncmp(line, "SO", 2) == 0)
	{
		cub->SO_array = malloc(ft_strlen(line) + 1);
		if (!cub->SO_array)
		{
			perror("Failed to allocate mamory.");
			return ;
		}
		strcpy(cub->SO_array, line);
		printf("SO_array: %s\n", cub->SO_array);
	}
}

void	west_array(char *line, t_cub *cub)
{
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		cub->WE_array = malloc(ft_strlen(line) + 1);
		if (!cub->WE_array)
		{
			perror("Failed to allocate mamory.");
			return ;
		}
		strcpy(cub->WE_array, line);
		printf("WE_array: %s\n", cub->WE_array);
	}
}

void	east_array(char *line, t_cub *cub)
{
	if (ft_strncmp(line, "EA", 2) == 0)
	{
		cub->EA_array = malloc(ft_strlen(line) + 1);
		if (!cub->EA_array)
		{
			perror("Failed to allocate mamory.");
			return ;
		}
		strcpy(cub->EA_array, line);
		printf("EA_array: %s\n", cub->EA_array);
	}
}

void	floor_array(char *line, t_cub *cub)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		cub->F_array = malloc(ft_strlen(line) + 1);
		if (!cub->F_array)
		{
			perror("Failed to allocate mamory.");
			return ;
		}
		strcpy(cub->F_array, line);
		printf("F_aray: %s\n", cub->F_array);
	}
}

void	ceiling_array(char *line, t_cub *cub)
{
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		cub->C_array = malloc(ft_strlen(line) + 1);
		if (!cub->C_array)
		{
			perror("Failed to allocate mamory.");
			return ;
		}
		strcpy(cub->C_array, line);
		printf("C_aray: %s\n", cub->C_array);
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
		perror("Failed to allocate mamory.");
		return ;
	}
	i = start;
	while (j < cub->hight)
	{
		cub->map[j] = ft_strdup(array[i]);
		if (!cub->map[j])
		{
			perror("Failed to duplicate map line.");
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