/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-25 11:12:49 by epolkhov          #+#    #+#             */
/*   Updated: 2024-09-25 11:12:49 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

typedef struct  s_cub
{
	char	**map;
	int		hight;
	int		width;
	char	*file;
	char	*NO_array;
	char	*SO_array;
	char	*WE_array;
	char	*EA_array;
	char	*F_array;
	char	*C_array;


} t_cub;

#endif