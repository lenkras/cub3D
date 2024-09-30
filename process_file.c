/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-27 09:06:40 by epolkhov          #+#    #+#             */
/*   Updated: 2024-09-27 09:06:40 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char *open_file(char *argv)
{
	int		fd;
	char	buf[1024];
	int		bytes_read;
	char	*data = NULL;
	int		bytes_total = 0;
	char	*temp;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		perror("Error: Failed to open a file.");
		return (NULL);
	}
	data = malloc(1);
	if (!data)
	{
		perror("Error: Failed to allocate mamory.");
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
			perror("Error: Failed to allocate mamory.");
			free(data);
			close(fd);
			return (NULL);
		}
		ft_strcpy(temp, data);
		ft_strcat(temp, buf);
		free(data);
		data = temp;
	}
	if (bytes_read == -1)
	{
		perror("Error: Failed to read a file.");
		free(data);
		close(fd);
;		return (NULL);
	}
	close(fd);
	return (data);
}

