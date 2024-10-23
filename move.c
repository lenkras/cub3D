#include "cub.h"

// int key(int keycode, t_cub *cub);

// void update_gaze(t_cub *cub, float angle_change)
// {
//     cub->gaze += angle_change;

//     // Normalize the gaze angle to be between 0 and 2*PI
//     if (cub->gaze < 0)
//         cub->gaze += 2 * M_PI;
//     else if (cub->gaze >= 2 * M_PI)
//         cub->gaze -= 2 * M_PI;
// }

void press_key(mlx_key_data_t keydata, void* param) {
    t_cub *cub = (t_cub *)param;

    if (cub == NULL) {
        fprintf(stderr, "Invalid cub pointer\n");
        return;
    }

    if (keydata.action == MLX_PRESS) {
        // Move up (W key)
        if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) {
            cub->player_w += cos(cub->gaze) * MOVE_SPEED; // Move in the gaze direction
            cub->player_h += sin(cub->gaze) * MOVE_SPEED; // Move in the gaze direction
        }
        // Move down (S key)
        else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) {
            cub->player_w -= cos(cub->gaze) * MOVE_SPEED; // Move backward
            cub->player_h -= sin(cub->gaze) * MOVE_SPEED; // Move backward
        }
        // Move left (A key)
        else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT) {
            cub->player_w -= cos(cub->gaze + M_PI / 2) * MOVE_SPEED; // Strafe left
            cub->player_h -= sin(cub->gaze + M_PI / 2) * MOVE_SPEED; // Strafe left
        }
        // Move right (D key)
        else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) {
            cub->player_w += cos(cub->gaze + M_PI / 2) * MOVE_SPEED; // Strafe right
            cub->player_h += sin(cub->gaze + M_PI / 2) * MOVE_SPEED; // Strafe right
        }
        // // Turn left (Q key)
        // else if (keydata.key == MLX_KEY_Q) {
        //     update_gaze(cub, -AS); // Rotate left
        // }
        // // Turn right (E key)
        // else if (keydata.key == MLX_KEY_E) {
        //     update_gaze(cub, AS); // Rotate right
        // }
        // Close the window (ESC key)
        else if (keydata.key == MLX_KEY_ESCAPE) {
            mlx_close_window(cub->mlx);
        }

        draw(cub); // Redraw the screen after movement
    }
}

// void press_key(mlx_key_data_t keydata, void* param) {
//     t_cub *cub = (t_cub *)param;

//     if (cub == NULL) {
//         fprintf(stderr, "Invalid cub pointer\n");
//         return;
//     }
//     if (keydata.action == MLX_PRESS) {
//         // Move up (W key)
//         if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) {
//             cub->player_h -= MOVE_SPEED;
//         }
//         // Move down (S key)
//         else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) {
//             cub->player_h += MOVE_SPEED;
//         }
//         // Move left (A key)
//         else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT) {
//             cub->player_w -= MOVE_SPEED;
//         }
//         // Move right (D key)
//         else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) {
//             cub->player_w += MOVE_SPEED; 
//         }
//         // Close the window (ESC key)
//         else if (keydata.key == MLX_KEY_ESCAPE) {
//             mlx_close_window(cub->mlx);
//         }

//         draw(cub);
//     }
// }


