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