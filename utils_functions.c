/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 09:02:17 by epolkhov          #+#    #+#             */
/*   Updated: 2024/10/20 21:50:46 by dlevinsc         ###   ########.fr       */
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

int	is_all_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int has_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || 
		c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

char	*ft_strcpy(char *dest, const char *src)
{
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	while (*dest != '\0')
		dest++;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest);
}

void	free_all(t_cub *cub)
{
	if (cub->map)
		free_array(cub->map);
	if (cub->file)
		free(cub->file);
	if (cub->NO_array)
		free(cub->NO_array);
	if (cub->SO_array)
		free (cub->SO_array);
	if (cub->WE_array)
		free(cub->WE_array);
	if (cub->EA_array)
		free(cub->EA_array);
	if (cub->F_array)
		free(cub->F_array);
	if (cub->C_array)
		free(cub->C_array);
}

int check_file_permission(const char *filepath)
{
    if (access(filepath, F_OK) != 0)
    {
        ft_putendl_fd("Error: File does not exist.", 2);
        return (1);
    }
    if (access(filepath, R_OK) != 0)
    {
        ft_putendl_fd("Error: File is not readable.", 2);
        return (1);
    }
    return (0);
}
int check_sign(float f)
{
    if (f < 0.0f)
    {
        if (f > -0.000001f)
            return (0);
        else
            return (-1);
    }
    else
    {
        if (f < 0.000001f)
            return (0);
        else
            return (1);
    }
}

void destroy_textures(t_cub *cub)
{
    int i = 0;

    while (i < 4)
    {
        if (cub->txt[i])
        {
            mlx_delete_texture(cub->txt[i]);
            cub->txt[i] = NULL; 
        }
        i++;
    }
	if (cub->img)
    	mlx_delete_image(cub->mlx, cub->img);

    mlx_terminate(cub->mlx);
}