/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 19:04:51 by epolkhov          #+#    #+#             */
/*   Updated: 2024/10/27 21:11:40 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move(t_cub *cub, int direction);

void	press_key(mlx_key_data_t keydata, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (cub == NULL)
	{
		ft_putendl_fd("Error\nInvalid cub pointer\n", 2);
		return ;
	}
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			move(cub, 0);
		else if (keydata.key == MLX_KEY_S)
			move(cub, 2);
		else if (keydata.key == MLX_KEY_LEFT)
			cub->gaze -= AS * M_PI;
		else if (keydata.key == MLX_KEY_RIGHT)
			cub->gaze += AS * M_PI;
		else if (keydata.key == MLX_KEY_A)
			move(cub, 3);
		else if (keydata.key == MLX_KEY_D)
			move(cub, 1);
		else if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(cub->mlx);
	}
}

void	move(t_cub *cub, int direction)
{
	float	dist;
	float	dx;
	float	dy;
	float	angle;

	angle = cub->gaze + direction * M_PI / 2;
	dx = LS * cos(angle);
	dy = LS * sin(angle);
	dist = view(cub, check_sign(dy) * M_PI / 2);
	if (dist * dist < dy * dy)
		dy = 0.0f;
	dist = view(cub, (1 - (check_sign(dx) + 1) / 2) * M_PI);
	if (dist * dist < dx * dx)
		dx = 0.0f;
	dist = view(cub, angle);
	if (dist * dist < dy * dy + dx * dx)
	{
		if (check_sign(dy) * check_sign(dx) != 0)
			dy = 0.0f;
	}
	cub->p_x += dx;
	cub->p_y -= dy;
}
