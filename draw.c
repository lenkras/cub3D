/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 19:04:05 by epolkhov          #+#    #+#             */
/*   Updated: 2024/11/05 22:03:02 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// Draw the ceiling and floor colors on the screen
void	draw_ceiling_and_floor(t_cub *cub)
{
	unsigned int	color_ceiling;
	unsigned int	color_floor;
	unsigned int	y;
	unsigned int	x;

	color_ceiling = (cub->c_r << 24) | (cub->c_g << 16)
		| (cub->c_b << 8) | 0xFF;
	color_floor = (cub->f_r << 24) | (cub->f_g << 16) | (cub->f_b << 8) | 0xFF;
	y = 0;
	while (y < WINDOW_H / 2)
	{
		x = 0;
		while (x < WINDOW_W)
			mlx_put_pixel(cub->img, x++, y, color_ceiling);
		y++;
	}
	y = WINDOW_H / 2;
	while (y < WINDOW_H)
	{
		x = 0;
		while (x < WINDOW_W)
			mlx_put_pixel(cub->img, x++, y, color_floor);
		y++;
	}
}

void	ft_line(t_cub *cub, int w, float dist)
{
	unsigned int	*dst;
	unsigned int	*src;
	unsigned int	h;
	float			src_f;
	float			d_shift;

	h = (float)WINDOW_H / dist;
	src_f = 0.0f;
	d_shift = (float)cub->txt[cub->txt_idx]->height / h;
	if (h > WINDOW_H)
	{
		src_f = 0.5f * (h - WINDOW_H) / h * cub->txt[cub->txt_idx]->height;
		h = WINDOW_H;
	}
	dst = (unsigned int *)cub->img->pixels + w + (WINDOW_H - h) / 2 * WINDOW_W;
	while (h-- > 0)
	{
		src = (unsigned int *)cub->txt[cub->txt_idx]->pixels + \
			((int)(cub->txt_w * cub->txt[cub->txt_idx]->width)) \
			+ ((int)src_f * cub->txt[cub->txt_idx]->width);
		*dst = *src;
		dst += WINDOW_W;
		src_f += d_shift;
	}
}
