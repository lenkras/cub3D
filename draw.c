/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 19:04:05 by epolkhov          #+#    #+#             */
/*   Updated: 2024/11/05 21:25:30 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
/*
// Get the pixel color at position (x, y) in the texture
static int	get_pixel(mlx_texture_t *texture, int x, int y)
{
	int	color;
	int	index;

	index = y * (int)texture->width * (int)texture->bytes_per_pixel + x
		* (int)texture->bytes_per_pixel;
	color = get_rgba(texture->pixels[index], texture->pixels[index + 1],
			texture->pixels[index + 2], 255);
	return (color);
}
*/

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
/*
// Initialize line parameters based on texture and distance
void	init_line_params(t_cub *cub, float dist, t_line_params *params, int x)
{
	params->h = (float)WINDOW_H / dist;
	params->src_f = 0.0f;
	params->d_shift = (float)cub->txt[cub->txt_idx]->height / params->h;
	if (params->h > WINDOW_H)
	{
		params->src_f = 0.5f * (params->h - WINDOW_H) / params->h
			* cub->txt[cub->txt_idx]->height;
		params->h = WINDOW_H;
	}
	params->texture_x = (x * cub->txt[cub->txt_idx]->width) / WINDOW_W;
	params->y_start = (WINDOW_H - params->h) / 2;
}

// Helper function to draw the textured line vertically
void	draw_texture_line(t_cub *cub, int x, t_line_params *params)
{
	uint32_t	y;
	uint32_t	color;

	y = 0;
	while (y < params->h)
	{
		color = get_pixel(cub->txt[cub->txt_idx], params->texture_x,
				(int)params->src_f);
		mlx_put_pixel(cub->img, x, params->y_start + y, color);
		params->src_f += params->d_shift;
		y++;
	}
}

// Draw a vertical line on the screen using a texture and distance
void	line(t_cub *cub, int x, float dist)
{
	t_line_params	params;

	init_line_params(cub, dist, &params, x);
	draw_texture_line(cub, x, &params);
}
*/
void ft_line(t_cub *cub, int w, float dist)
{
    uint32_t *src;
    unsigned int h;
    float src_f;
    float d_shift;

    h = (float)WINDOW_H / dist;
    src_f = 0.0f;
    d_shift = (float)cub->txt[cub->txt_idx]->height / h;

    // Adjust height and starting point if the line is taller than the window
    if (h > WINDOW_H)
    {
        src_f = 0.5f * (h - WINDOW_H) / h * cub->txt[cub->txt_idx]->height;
        h = WINDOW_H;
    }

    // Set the source to the starting pixel in the texture based on `txt_w`
    src = (uint32_t *)cub->txt[cub->txt_idx]->pixels + (int)((float)cub->txt_w * cub->txt[cub->txt_idx]->width);

    // Calculate vertical offset in the destination image
    unsigned int y_start = (WINDOW_H - h) / 2;
	
	printf("cub->txt_w = %f\n", cub->txt_w);
	
    // Draw each line pixel
    for (unsigned int y = 0; y < h; y++)
    {
        // Calculate destination position in the MLX42 image
        uint32_t color = *(src + (int)src_f * cub->txt[cub->txt_idx]->width);

        // Set the pixel color using MLX42
        mlx_put_pixel(cub->img, w, y_start + y, color);

        // Move to the next line in the source texture
        src_f += d_shift;
    }
}
