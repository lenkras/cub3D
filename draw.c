#include "cub.h"

// Struct to hold line parameters
typedef struct s_line_params
{
	uint32_t	h;
	float		src_f;
	float		d_shift;
	int			texture_x;
	int			y_start;
}	t_line_params;

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
