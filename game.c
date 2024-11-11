/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 19:04:17 by epolkhov          #+#    #+#             */
/*   Updated: 2024/11/11 22:34:42 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	find_position(t_cub *cub);

void	render(t_cub *cub)
{
	ft_memset(cub->img->pixels, 0, (cub->img->width * cub->img->height)
		* sizeof(int32_t));
	draw_ceiling_and_floor(cub);
	view_direction(cub);
}

void	game(t_cub *cub)
{
//	mirror_map(cub);
	find_position(cub);
//	determine_player_position(cub);
	cub->mlx = mlx_init(WINDOW_W, WINDOW_H, TITLE, false);
	if (!cub->mlx)
	{
		perror(mlx_strerror(mlx_errno));
		return ;
	}
	if (load_textures(cub))
		return ;
	cub->img = mlx_new_image(cub->mlx, WINDOW_W, WINDOW_H);
	if (!cub->img)
	{
		mlx_close_window(cub->mlx);
		perror(mlx_strerror(mlx_errno));
		return ;
	}
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
	{
		mlx_close_window(cub->mlx);
		perror(mlx_strerror(mlx_errno));
		return ;
	}
	mlx_key_hook(cub->mlx, press_key, cub);
	mlx_loop_hook(cub->mlx, (void *)render, cub);
	mlx_loop(cub->mlx);
}

void	view_set_angle(t_cub *cub, const char c)
{
	if (c == 'E')
		cub->gaze = 0.0f * M_PI;
	else if (c == 'N')
		cub->gaze = 0.5f * M_PI;
	else if (c == 'W')
		cub->gaze = 1.0f * M_PI;
	else if (c == 'S')
		cub->gaze = -0.5f * M_PI;
}
/*
void	determine_player_position(t_cub *cub)
{
	cub->p_x = (float)cub->player_w + 0.5f;
	cub->p_y = (float)cub->player_h + 0.5f;
	view_set_angle(cub, cub->map[cub->player_h][cub->player_w]);
}
*/

void	find_position(t_cub *cub)
{
	cub->p_x = (float)cub->player_w + 0.5f;
	cub->p_y = (float)(cub->height - 1 - cub->player_h) + 0.5f;
	view_set_angle(cub, cub->map[cub->height - 1 - cub->player_h][cub->player_w]);
	printf("x = %i, y = %i, h = %i, w = %i \n", cub->player_w, cub->height - 1 - cub->player_h, cub->height, cub->width);
/*	int	i;
	int	j;

	i = -1;
	while (++i < cub->height)
	{
		j = -1;
		while (++j < cub->width)
		{
			if (ft_strchr("NSWE", cub->map[i][j]))
			{
				cub->p_x = (float) j + 0.5f;
				cub->p_y = (float) i + 0.5f;
				view_set_angle(cub, cub->map[i][j]);
				printf("x = %i, y = %i \n", j, i);
				
				return ;
			}
		}
	}
*/}

