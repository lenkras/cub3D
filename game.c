/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-27 19:04:17 by epolkhov          #+#    #+#             */
/*   Updated: 2024-10-27 19:04:17 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	render(t_cub *cub)
{
	ft_memset(cub->img->pixels, 0, (cub->img->width * cub->img->height)
		* sizeof(int32_t));
	draw_ceiling_and_floor(cub);
	view_direction(cub);
}

void	game(t_cub *cub)
{
	determine_player_position(cub);
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

void	determine_player_position(t_cub *cub)
{
	cub->p_x = (float)cub->player_w + 0.5f;
	cub->p_y = (float)cub->player_h + 0.5f;
	view_set_angle(cub, cub->map[cub->player_h][cub->player_w]);
}
