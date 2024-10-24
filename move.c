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

void update_gaze(t_cub *cub, float angle_change);

void press_key(mlx_key_data_t keydata, void* param) {
    t_cub *cub = (t_cub *)param;

    if (cub == NULL) {
        fprintf(stderr, "Invalid cub pointer\n");
        return;
    }

    if (keydata.action == MLX_PRESS) {
        // Move up (W key)
        if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) {
            if (cub->map[(int)(cub->p_y + sin(cub->gaze) * MOVE_SPEED)][(int)(cub->p_x + cos(cub->gaze) * MOVE_SPEED)] != '1') {
                cub->p_x += cos(cub->gaze) * MOVE_SPEED; // Move in the gaze direction
                cub->p_y += sin(cub->gaze) * MOVE_SPEED; // Move in the gaze direction
            }
        }
        // Move down (S key)
        else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) {
            if (cub->map[(int)(cub->p_y - sin(cub->gaze) * MOVE_SPEED)][(int)(cub->p_x - cos(cub->gaze) * MOVE_SPEED)] != '1') {
                cub->p_x -= cos(cub->gaze) * MOVE_SPEED; // Move backward
                cub->p_y -= sin(cub->gaze) * MOVE_SPEED; // Move backward
            }
        }
        // Move left (A key)
        else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT) {
            update_gaze(cub, -AS);
        }
        // Move right (D key)
        else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) {
            update_gaze(cub, AS);
        }
        // Turn left (Q key)
        else if (keydata.key == MLX_KEY_Q) {
            update_gaze(cub, -AS); // Rotate left
        }
        // Turn right (E key)
        else if (keydata.key == MLX_KEY_E) {
            update_gaze(cub, AS); // Rotate right
        }
        // Close the window (ESC key)
        else if (keydata.key == MLX_KEY_ESCAPE) {
            mlx_close_window(cub->mlx);
        }

        draw(cub); // Redraw the screen after movement or rotation
    }
}
/* last
void press_key(mlx_key_data_t keydata, void* param) {
    t_cub *cub = (t_cub *)param;

    if (cub == NULL) {
        fprintf(stderr, "Invalid cub pointer\n");
        return;
    }

    if (keydata.action == MLX_PRESS) {
        // Move up (W key)
        if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) {
            if (cub->map[(int)(cub->p_y + sin(cub->gaze) * MOVE_SPEED)][(int)(cub->p_x + cos(cub->gaze) * MOVE_SPEED)] != '1') {
                cub->p_x += cos(cub->gaze) * MOVE_SPEED; // Move in the gaze direction
                cub->p_y += sin(cub->gaze) * MOVE_SPEED; // Move in the gaze direction
            }
        }
        // Move down (S key)
        else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) {
            if (cub->map[(int)(cub->p_y - sin(cub->gaze) * MOVE_SPEED)][(int)(cub->p_x - cos(cub->gaze) * MOVE_SPEED)] != '1') {
                cub->p_x -= cos(cub->gaze) * MOVE_SPEED; // Move backward
                cub->p_y -= sin(cub->gaze) * MOVE_SPEED; // Move backward
            }
        }
        // Move left (A key)
        else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT) {
            if (cub->map[(int)(cub->p_y + sin(cub->gaze + M_PI / 2) * MOVE_SPEED)][(int)(cub->p_x + cos(cub->gaze + M_PI / 2) * MOVE_SPEED)] != '1') {
                cub->p_x -= cos(cub->gaze + M_PI / 2) * MOVE_SPEED; // Strafe left
                cub->p_y -= sin(cub->gaze + M_PI / 2) * MOVE_SPEED; // Strafe left
            }
        }
        // Move right (D key)
        else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) {
            if (cub->map[(int)(cub->p_y + sin(cub->gaze - M_PI / 2) * MOVE_SPEED)][(int)(cub->p_x + cos(cub->gaze - M_PI / 2) * MOVE_SPEED)] != '1') {
                cub->p_x += cos(cub->gaze + M_PI / 2) * MOVE_SPEED; // Strafe right
                cub->p_y += sin(cub->gaze + M_PI / 2) * MOVE_SPEED; // Strafe right
            }
        }
        // Turn left (Q key)
        else if (keydata.key == MLX_KEY_Q) {
            update_gaze(cub, -AS); // Rotate left
        }
        // Turn right (E key)
        else if (keydata.key == MLX_KEY_E) {
            update_gaze(cub, AS); // Rotate right
        }
        // Close the window (ESC key)
        else if (keydata.key == MLX_KEY_ESCAPE) {
            mlx_close_window(cub->mlx);
        }

        draw(cub); // Redraw the screen after movement or rotation
    }
}
*/
void update_gaze(t_cub *cub, float angle_change) {
    // Update the player's gaze angle by adding the change
    cub->gaze += angle_change;

    // Normalize the gaze angle to be between 0 and 2 * M_PI
    if (cub->gaze < 0)
        cub->gaze += 2 * M_PI;
    else if (cub->gaze >= 2 * M_PI)
        cub->gaze -= 2 * M_PI;
}


/*
void press_key(mlx_key_data_t keydata, void* param) {
    t_cub *cub = (t_cub *)param;

    if (cub == NULL) {
        fprintf(stderr, "Invalid cub pointer\n");
        return;
    }

    if (keydata.action == MLX_PRESS) {
        // Move up (W key)
        if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) {
            cub->p_x += cos(cub->gaze) * MOVE_SPEED; // Move in the gaze direction
            cub->p_y += sin(cub->gaze) * MOVE_SPEED; // Move in the gaze direction
        }
        // Move down (S key)
        else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) {
            cub->p_x -= cos(cub->gaze) * MOVE_SPEED; // Move backward
            cub->p_y -= sin(cub->gaze) * MOVE_SPEED; // Move backward
        }
        // Move left (A key)
        else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT) {
            cub->p_x -= cos(cub->gaze + M_PI / 2) * MOVE_SPEED; // Strafe left
            cub->p_y -= sin(cub->gaze + M_PI / 2) * MOVE_SPEED; // Strafe left
        }
        // Move right (D key)
        else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) {
            cub->p_x += cos(cub->gaze + M_PI / 2) * MOVE_SPEED; // Strafe right
            cub->p_y += sin(cub->gaze + M_PI / 2) * MOVE_SPEED; // Strafe right
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
*/
// void press_key(mlx_key_data_t keydata, void* param) {
//     t_cub *cub = (t_cub *)param;

//     if (cub == NULL) {
//         fprintf(stderr, "Invalid cub pointer\n");
//         return;
//     }
//     if (keydata.action == MLX_PRESS) {
//         // Move up (W key)
//         if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) {
//             cub->p_y -= MOVE_SPEED;
//         }
//         // Move down (S key)
//         else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) {
//             cub->p_y += MOVE_SPEED;
//         }
//         // Move left (A key)
//         else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT) {
//             cub->p_x -= MOVE_SPEED;
//         }
//         // Move right (D key)
//         else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) {
//             cub->p_x += MOVE_SPEED; 
//         }
//         // Close the window (ESC key)
//         else if (keydata.key == MLX_KEY_ESCAPE) {
//             mlx_close_window(cub->mlx);
//         }

//         draw(cub);
//     }
// }


