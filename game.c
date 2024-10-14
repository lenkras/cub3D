#include "cub.h"

void draw(t_cub *cub);
void key_press(mlx_key_data_t keydata, void* param);
void destroy_exit(void* param);

void    game(t_cub *cub)
{
	cub->mlx = mlx_init(WINDOW_W, WINDOW_H, TITLE, false);
    {
        fprintf(stderr, "MLX42 initialization failed\n");
        exit(EXIT_FAILURE);
    }
	load_textures(cub);
	draw(cub);
	
    // Register key press event
    mlx_key_hook(cub->mlx, key_press, game);

    // Handle the window close event
    mlx_close_hook(cub->mlx, destroy_exit, game);

    // Start the main loop
    mlx_loop(cub->mlx);

    // Clean up on exit
    mlx_terminate(cub->mlx);
}