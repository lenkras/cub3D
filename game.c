#include "cub.h"

void draw(t_cub *cub);
void load_textures(t_cub *cub);
void determine_player_position(t_cub *cub);
void draw_ceiling_and_floor(t_cub *cub);
void view_direction(t_cub *cub);
void line(t_cub *cub, int w, float dist);
float view(t_cub *cub, float v);
void view_next(t_cub *cub, t_view *view);
void view_start(t_cub *cub, t_view *view, float angle);
float view_save_color(t_cub *cub, float dist, int color_idx, float w);

void draw(t_cub *cub)
{
    // Create a new image with MLX42
    cub->img = mlx_new_image(cub->mlx, WINDOW_W, WINDOW_H);
    if (!cub->img)
    {
        fprintf(stderr, "Failed to create an image\n");
        return;
    }

    // Call functions to draw content
    draw_ceiling_and_floor(cub);
    view_direction(cub);

    // Render the image to the window
    mlx_image_to_window(cub->mlx, cub->img, 0, 0);
}

void close_window(void *param)
{
    t_cub *cub = (t_cub *)param;
    mlx_terminate(cub->mlx);
    exit(0);
}

void    game(t_cub *cub)
{
    determine_player_position(cub);
    cub->mlx = mlx_init(WINDOW_W, WINDOW_H, TITLE, false);
    if (!cub->mlx)
    {
        fprintf(stderr, "MLX42 initialization failed\n");
        exit(EXIT_FAILURE);
    }
	load_textures(cub);
    mlx_close_hook(cub->mlx, close_window, cub);
	draw(cub);
    // Register key press event
    mlx_key_hook(cub->mlx, press_key, cub);

    // Handle the window close event
//    mlx_close_hook(cub->mlx, destroy, game);

    // Start the main loop
    mlx_loop(cub->mlx);

    // Clean up on exit
    mlx_terminate(cub->mlx);
}

void draw_ceiling_and_floor(t_cub *cub)
{
     printf("Drawing ceiling and floor...\n");
    // unsigned int *dst;
    // unsigned int i;
    unsigned int color_ceiling;
    unsigned int color_floor;

    // Combine RGB values into a single integer for ceiling color
    color_ceiling = (cub->C_R << 24) | (cub->C_G << 16) | (cub->C_B << 8) | 0xFF;

    // Combine RGB values into a single integer for floor color
    color_floor = (cub->F_R << 24) | (cub->F_G << 16) | (cub->F_B << 8) | 0xFF;
    // printf("Ceiling Color: %u, Floor Color: %u\n", color_ceiling, color_floor);

    // Access pixel buffer from the MLX42 image structure
    // dst = (unsigned int *) cub->img->pixels;

    // // Draw the ceiling (first half of the screen)
    // i = WINDOW_W * WINDOW_H / 2;
    // while (i-- > 0)
    //     *dst++ = color_ceiling;

    // // Draw the floor (second half of the screen)
    // i = WINDOW_W * WINDOW_H / 2;
    // while (i-- > 0)
    //     *dst++ = color_floor;

    unsigned int y = 0;
    while (y < WINDOW_H / 2) {
        unsigned int x = 0;
        while (x < WINDOW_W) {
            mlx_put_pixel(cub->img, x, y, color_ceiling);
            x++;
        }
        y++;
    }

    // Draw the floor (second half of the screen)
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

void line(t_cub *cub, int w, float dist)
{
    uint32_t *dst;
    uint32_t *src;
    unsigned int h;
    float src_f;
    float d_shift;
    mlx_texture_t *texture = cub->txt[cub->txt_idx]; // Access the current texture

    // Calculate the height of the line based on distance
    h = (float) WINDOW_H / dist;
    src_f = 0.0f;
    d_shift = (float) texture->height / h;

    // If the line is taller than the window, adjust the starting point
    if (h > WINDOW_H) {
        src_f = 0.5f * (h - WINDOW_H) / h * texture->height;
        h = WINDOW_H;
    }

    // Ensure src_f doesn't exceed texture height
    if ((int)src_f < (int)texture->height) {  // Fix the signedness issue here
        src = (uint32_t *) texture->pixels + (int)((float) cub->txt_w * texture->width);
        dst = (uint32_t *) cub->img->pixels + w + (WINDOW_H - h) / 2 * WINDOW_W;

        // Copy texture to the screen for the calculated height
        while (h-- > 0) {
            *dst = *(src + ((int)src_f) * texture->width);  // Assign the pixel from texture
            dst += WINDOW_W;                                // Move to the next line in the window
            src_f += d_shift;                               // Increment source texture vertical position
        }
    }
}



void view_direction(t_cub *cub)
{
    int x;
    float dv;
    float v;

    v = cub->gaze - FOV / 2;
    dv = FOV / (WINDOW_W - 1);
    x = -1;
    while (++x < WINDOW_W)
    {
        line(cub, x, view(cub, v) * cos(cub->player - v));
        v += dv;
    }
}

float view(t_cub *cub, float v)
{
    t_view vi;
    view_start(cub, &vi, v);  // Initialize ray direction and positions
    
    while (1)
    {
        view_next(cub, &vi);  // Find the next grid line intersection

        // Check if a vertical wall was hit
        if (vi.v_dist < vi.h_dist)
        {
            if (cub->map[(int)vi.v_y][(int)vi.v_x + (vi.sx - 1) / 2] == '1')
            {
                printf("Vertical wall hit at distance: %f\n", vi.v_dist);
                return view_save_color(cub, vi.v_dist, vi.sx + 1, vi.v_w);
            }
            else
            {
                vi.v_x += vi.sx;  // Move to the next vertical grid line
            }
        }
        // Check if a horizontal wall was hit
        else
        {
            if (cub->map[(int)vi.h_y + (vi.sy - 1) / 2][(int)vi.h_x] == '1')
            {
                printf("Horizontal wall hit at distance: %f\n", vi.h_dist);
                return view_save_color(cub, vi.h_dist, vi.sy + 2, vi.h_w);
            }
            else
            {
                vi.h_y += vi.sy;  // Move to the next horizontal grid line
            }
        }
    }
}


void view_start(t_cub *cub, t_view *view, float angle)
{
    view->dx = cos(angle);
    view->dy = -sin(angle);
    view->sx = check_sign(view->dx);
    view->sy = check_sign(view->dy);
    
    view->v_x = cub->p_x;
    if (view->sx > 0)
        view->v_x += 1.0f;

    view->h_y = (int) cub->p_y;
    if (view->sy > 0)
        view->h_y += 1.0f;
}

void view_next(t_cub *cub, t_view *view)
{
    if (view->sx != 0)
    {
        view->v_y = cub->p_y + view->dy / view->dx * (view->v_x - cub->p_x);
        view->v_dist = sqrt(pow(cub->p_x - view->v_x, 2.0) + pow(cub->p_y - view->v_y, 2.0));
        printf("Next vertical distance: %f\n", view->v_dist);
    }
    else
        view->v_dist = INFINITY;

    if (view->sy != 0)
    {
        view->h_x = cub->p_x + view->dx / view->dy * (view->h_y - cub->p_y);
        view->h_dist = sqrt(pow(cub->p_x - view->h_x, 2.0) + pow(cub->p_y - view->h_y, 2.0));

        // Add detailed debugging here
        printf("Next horizontal distance: %f\n", view->h_dist);
        printf("Horizontal ray dx: %f, dy: %f\n", view->dx, view->dy);
        printf("Horizontal player_w: %f, player_h: %f, h_x: %f, h_y: %f\n", cub->p_x, cub->p_y, view->h_x, view->h_y);
    }
    else
        view->h_dist = INFINITY;
}


float view_save_color(t_cub *cub, float dist, int color_idx, float w)
{
    // Debugging: Log the distance, color index, and width coordinate
    printf("Saving color: \n");
    printf("  Distance to wall: %f\n", dist);
    printf("  Selected texture index: %d\n", color_idx);
    printf("  Texture horizontal position (txt_w): %f\n", w);

    // Set the texture index (which texture to use for this wall)
    cub->txt_idx = color_idx;  

    // Ensure that the texture index is within bounds (0 to 3 for North, South, West, East)
    if (cub->txt_idx < 0 || cub->txt_idx >= 4) {
        fprintf(stderr, "Error: Invalid texture index %d\n", cub->txt_idx);
        exit(EXIT_FAILURE);
    }

    // Set the texture horizontal position (w)
    cub->txt_w = (int)w;  // Ensure cub->txt_w is an integer

    // Ensure that the horizontal texture position is within valid bounds
    if ((int)cub->txt_w < 0 || (int)cub->txt_w >= (int)cub->txt[cub->txt_idx]->width) {  // Fix the signedness issue here
        fprintf(stderr, "Warning: Texture width coordinate out of bounds: %d\n", cub->txt_w);  // Fix the format specifier
    }

    // Return the distance to the wall for use in rendering
    return dist;
}


void load_textures(t_cub *cub)
{
    // Load the North texture
    printf("Loading North texture from: %s\n", cub->NO_array);
    cub->txt[0] = mlx_load_png(cub->NO_array);
    if (!cub->txt[0])
    {
        fprintf(stderr, "Failed to load the North texture from %s\n", cub->NO_array);
        exit(EXIT_FAILURE);
    }
    printf("North texture loaded: Width = %d, Height = %d\n", cub->txt[0]->width, cub->txt[0]->height);

    // Load the South texture
    printf("Loading South texture from: %s\n", cub->SO_array);
    cub->txt[1] = mlx_load_png(cub->SO_array);
    if (!cub->txt[1])
    {
        fprintf(stderr, "Failed to load the South texture from %s\n", cub->SO_array);
        exit(EXIT_FAILURE);
    }
    printf("South texture loaded: Width = %d, Height = %d\n", cub->txt[1]->width, cub->txt[1]->height);

    // Load the West texture
    printf("Loading West texture from: %s\n", cub->WE_array);
    cub->txt[2] = mlx_load_png(cub->WE_array);
    if (!cub->txt[2])
    {
        fprintf(stderr, "Failed to load the West texture from %s\n", cub->WE_array);
        exit(EXIT_FAILURE);
    }
    printf("West texture loaded: Width = %d, Height = %d\n", cub->txt[2]->width, cub->txt[2]->height);

    // Load the East texture
    printf("Loading East texture from: %s\n", cub->EA_array);
    cub->txt[3] = mlx_load_png(cub->EA_array);
    if (!cub->txt[3])
    {
        fprintf(stderr, "Failed to load the East texture from %s\n", cub->EA_array);
        exit(EXIT_FAILURE);
    }
    printf("East texture loaded: Width = %d, Height = %d\n", cub->txt[3]->width, cub->txt[3]->height);
}

void view_set_angle(t_cub *cub, const char c)
{
    if (c == 'E')
        cub->player = 0.0f * M_PI; // Set view angle to East
    else if (c == 'N')
        cub->player = 0.5f * M_PI; // Set view angle to North
    else if (c == 'W')
        cub->player = 1.0f * M_PI; // Set view angle to West
    else if (c == 'S')
        cub->player = -0.5f * M_PI; // Set view angle to South
}


void determine_player_position(t_cub *cub)
{
    cub->p_x = (float) cub->player_w + 0.5f; // Set player x-position
    cub->p_y = (float) cub->player_h + 0.5f; // Set player y-position
    view_set_angle(cub, cub->map[cub->player_w][cub->player_h]); // Set the view angle based on map character
}
