#include "cub.h"

static int	get_pixel(mlx_texture_t *texture, int x, int y)
{
	int	color;
	int	index;

	index = y * (int)texture->height * (int)texture->bytes_per_pixel + x
		* (int)texture->bytes_per_pixel;
	color = get_rgba(texture->pixels[index], texture->pixels[index + 1],
			texture->pixels[index + 2], 255);
	return (color);
}

void draw_ceiling_and_floor(t_cub *cub)
{
	unsigned int color_ceiling;
	unsigned int color_floor;

	color_ceiling = (cub->C_R << 24) | (cub->C_G << 16) | (cub->C_B << 8) | 0xFF;
	color_floor = (cub->F_R << 24) | (cub->F_G << 16) | (cub->F_B << 8) | 0xFF;
	unsigned int y = 0;
	while (y < WINDOW_H / 2) {
		unsigned int x = 0;
		while (x < WINDOW_W) {
			mlx_put_pixel(cub->img, x, y, color_ceiling);
			x++;
		}
		y++;
	}
	y = WINDOW_H / 2;
	while (y < WINDOW_H) {
		unsigned int x = 0;
		while (x < WINDOW_W) {
			mlx_put_pixel(cub->img, x, y, color_floor);
			x++;
		}
		y++;
	}
}

void	line(t_cub *cub, int x, float dist)
{
	mlx_texture_t	*texture = cub->txt[cub->txt_idx];
	uint32_t		h;
	float			src_f;
	float			d_shift;
	uint32_t		texture_height = texture->height;

	h = (float) WINDOW_H / dist;
	src_f = 0.0f;
	d_shift = (float) texture_height / h;

	if (h > WINDOW_H)
	{
		src_f = 0.5f * (h - WINDOW_H) / h * texture_height;
		h = WINDOW_H;
	}
	int texture_x = (x * texture->width) / WINDOW_W;
	int y_start = (WINDOW_H - h) / 2;

	for (uint32_t y = 0; y < h; y++)
	{
		uint32_t color = get_pixel(texture, texture_x, (int)src_f);
		mlx_put_pixel(cub->img, x, y_start + y, color);
		src_f += d_shift;
	}
}
