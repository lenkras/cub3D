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

void	handle_error(char *msg, int fd, char *data)
{
	perror(msg);
	free(data);
	if (fd != -1)
		close(fd);
}

static int	check_size_limit(int bytes_total, int fd, char *data)
{
	if (bytes_total > MAX_FILE_SIZE)
	{
		handle_error("File exceeds the maximum allowed size.\n", \
			fd, data);
		return (1);
	}
	return (0);
}

static char	*allocate_memory_for_temp(char *temp, int bytes_total, \
								int fd, char *data)
{
	temp = malloc(bytes_total + 1);
	if (!temp)
	{
		handle_error("Error: Failed to allocate mamory.\n", fd, data);
		return (NULL);
	}
	return (temp);
}

static char	*read_file(char *data, int fd)
{
	char	buf[1024];
	int		bytes_total;
	int		bytes_read;
	char	*temp;

	bytes_total = 0;
	bytes_read = read(fd, buf, sizeof(buf) - 1);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		bytes_total += bytes_read;
		if (check_size_limit(bytes_total, fd, data))
			return (NULL);
		temp = allocate_memory_for_temp(temp, bytes_total, fd, data);
		ft_strcpy(temp, data);
		ft_strcat(temp, buf);
		free(data);
		data = temp;
		bytes_read = read(fd, buf, sizeof(buf) - 1);
	}
	return (print_readfile_error(bytes_read, fd, data));
}

char	*open_file(char *argv)
{
	int		fd;
	char	*data;

	data = NULL;
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
	data = read_file(data, fd);
	close(fd);
	return (data);
}
