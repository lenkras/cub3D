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
	int		F_R;
	int		F_G;
	int		F_B;
	int		C_R;
	int		C_G;
	int		C_B;


} t_cub;

void	free_array(char **arr);
char	*open_file(char *argv);

void	north_array(char *line, t_cub *cub);
void	south_array(char *line, t_cub *cub);
void	west_array(char *line, t_cub *cub);
void	east_array(char *line, t_cub *cub);
void	split_toRGB_floor(char *array, t_cub *cub);
void	split_toRGB_ceiling(char *array, t_cub *cub);
void	floor_array(char *line, t_cub *cub);
void	ceiling_array(char *line, t_cub *cub);
void	copy_map(char **array, t_cub *cub, int start);
int		find_map_start(char *line);

#endif