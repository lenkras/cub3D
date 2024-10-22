#include "cub.h"

// int key(int keycode, t_cub *cub);


void press_key(mlx_key_data_t keydata, void* param) {
    t_cub *cub = (t_cub *)param;

    if (keydata.action == MLX_PRESS) {
        // Move up (W key)
        if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) {
            cub->player_h -= MOVE_SPEED;
        }
        // Move down (S key)
        else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) {
            cub->player_h += MOVE_SPEED;
        }
        // Move left (A key)
        else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT) {
            cub->player_w -= MOVE_SPEED;
        }
        // Move right (D key)
        else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) {
            cub->player_w += MOVE_SPEED; 
        }
        // Close the window (ESC key)
        else if (keydata.key == MLX_KEY_ESCAPE) {
            mlx_close_window(cub->mlx);
        }

        draw(cub);
    }
}
