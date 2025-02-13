/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_parsing_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-27 19:05:41 by epolkhov          #+#    #+#             */
/*   Updated: 2024-10-27 19:05:41 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// Helper function to skip whitespace after newline
static int	skip_whitespace(const char *file, int i)
{
	while (file[i] == ' ' || file[i] == '\t')
		i++;
	return (i);
}

// Helper function to check if map section has started
static int	is_map_section(const char *file, int i, int map_section)
{
	if (!map_section && ((file[i + 1] == '1' || file[i + 1] == '0')
			|| (file[i] == '1' || file[i] == '0')))
		return (1);
	return (map_section);
}

// Main function to check for consecutive newlines in map section
int	check_consecutive_newlines_in_map(char *file)
{
	int	i;
	int	map_section;

	i = 0;
	map_section = 0;
	while (file[i])
	{
		while (file[i] && file[i] != '\n')
			i++;
		if (file[i])
		{
			if (file[i + 1] == ' ' || file[i + 1] == '\t')
				i = skip_whitespace(file, i + 1);
			map_section = is_map_section(file, i, map_section);
			if (map_section && file[i] == '\n' && file[i + 1] == '\n')
			{
				ft_putendl_fd
				("Error\nMultiple consecutive newlines in map.", 2);
				return (1);
			}
			if (file[i] == '\n')
				i++;
		}
	}
	return (0);
}
