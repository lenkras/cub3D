#include "cub.h"

void draw(t_cub *cub);
void load_textures(t_cub *cub);
//void determine_player_position(t_cub *cub);
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
//    view_direction(cub);

    // Render the image to the window
    mlx_image_to_window(cub->mlx, cub->img, 0, 0);
}


void    game(t_cub *cub)
{
    //determine_player_position(cub);
    cub->mlx = mlx_init(WINDOW_W, WINDOW_H, TITLE, false);
    if (!cub->mlx)
    {
        fprintf(stderr, "MLX42 initialization failed\n");
        exit(EXIT_FAILURE);
    }
	load_textures(cub);
	draw(cub);
	
    // Register key press event
 //   mlx_key_hook(cub->mlx, press_key, game);

    // Handle the window close event
//    mlx_close_hook(cub->mlx, destroy, game);

    // Start the main loop
    mlx_loop(cub->mlx);

    // Clean up on exit
    mlx_terminate(cub->mlx);
}

void draw_ceiling_and_floor(t_cub *cub)
{
    unsigned int *dst;
    unsigned int i;
    unsigned int color_ceiling;
    unsigned int color_floor;

    // Combine RGB values into a single integer for ceiling color
    color_ceiling = (cub->C_R << 16) | (cub->C_G << 8) | cub->C_B;

    // Combine RGB values into a single integer for floor color
    color_floor = (cub->F_R << 16) | (cub->F_G << 8) | cub->F_B;

    // Access pixel buffer from the MLX42 image structure
    dst = (unsigned int *) cub->img->pixels;

    // Draw the ceiling (first half of the screen)
    i = WINDOW_W * WINDOW_H / 2;
    while (i-- > 0)
        *dst++ = color_ceiling;

    // Draw the floor (second half of the screen)
    i = WINDOW_W * WINDOW_H / 2;
    while (i-- > 0)
        *dst++ = color_floor;
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
    if (h > WINDOW_H)
    {
        src_f = 0.5f * (h - WINDOW_H) / h * texture->height;
        h = WINDOW_H;
    }

    // Source: Texture pixels, start from the texture's specified width position
    src = (uint32_t *) texture->pixels + (int)((float) cub->txt_w * texture->width);

    // Destination: Target pixels in the window image
    dst = (uint32_t *) cub->img->pixels + w + (WINDOW_H - h) / 2 * WINDOW_W;

    // Copy texture to the screen for the calculated height
    while (h-- > 0)
    {
        *dst = *(src + ((int)src_f) * texture->width);  // Assign the pixel from texture
        dst += WINDOW_W;                                // Move to the next line in the window
        src_f += d_shift;                               // Increment source texture vertical position
    }
}

void view_direction(t_cub *cub)
{
    int x;
    float dv;
    float v;

    v = cub->player - FOV / 2;
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

    view_start(cub, &vi, v);
    while (1)
    {
        view_next(cub, &vi);
        if (vi.v_dist < vi.h_dist)
        {
            if (cub->map[(int)vi.v_y][(int)vi.v_x + (vi.sx - 1) / 2] == '1')
                return view_save_color(cub, vi.v_dist, vi.sx + 1, vi.v_w);
            else
                vi.v_x += vi.sx;
        }
        else
        {
            if (cub->map[(int)vi.h_y + (vi.sy - 1) / 2][(int)vi.h_x] == '1')
                return view_save_color(cub, vi.h_dist, vi.sy + 2, vi.h_w);
            else
                vi.h_y += vi.sy;
        }
    }
}

void view_start(t_cub *cub, t_view *view, float angle)
{
    view->dx = cos(angle);
    view->dy = -sin(angle);
    view->sx = check_sign(view->dx);
    view->sy = check_sign(view->dy);
    
    view->v_x = (int) cub->player_w;
    if (view->sx > 0)
        view->v_x += 1.0f;

    view->h_y = (int) cub->player_h;
    if (view->sy > 0)
        view->h_y += 1.0f;
}

void view_next(t_cub *cub, t_view *view)
{
    if (view->sx != 0)
    {
        view->v_y = cub->player_h + view->dy / view->dx * (view->v_x - cub->player_w);
        view->v_dist = sqrt(pow(cub->player_w - view->v_x, 2.0) + pow(cub->player_h - view->v_y, 2.0));
        view->v_w = view->v_y - (int) view->v_y;
        if (view->sx > 0)
            view->v_w = 1 - view->v_w;
    }
    else
        view->v_dist = INFINITY;

    if (view->sy != 0)
    {
        view->h_x = cub->player_w + view->dx / view->dy * (view->h_y - cub->player_h);
        view->h_dist = sqrt(pow(cub->player_w - view->h_x, 2.0) + pow(cub->player_h - view->h_y, 2.0));
        view->h_w = view->h_x - (int) view->h_x;
        if (view->sy < 0)
            view->h_w = 1 - view->h_w;
    }
    else
        view->h_dist = INFINITY;
}

 float view_save_color(t_cub *cub, float dist, int color_idx, float w)
{
    cub->txt_idx = color_idx;
    cub->txt_w = w;
    return dist;
}

void load_textures(t_cub *cub)
{
    // Load the North texture
    cub->txt[0] = mlx_load_png(cub->NO_array);
    if (!cub->txt[0])
    {
        fprintf(stderr, "Failed to load the North texture\n");
        exit(EXIT_FAILURE);
    }

    // Load the South texture
    cub->txt[1] = mlx_load_png(cub->SO_array);
    if (!cub->txt[1])
    {
        fprintf(stderr, "Failed to load the South texture\n");
        exit(EXIT_FAILURE);
    }

    // Load the West texture
    cub->txt[2] = mlx_load_png(cub->WE_array);
    if (!cub->txt[2])
    {
        fprintf(stderr, "Failed to load the West texture\n");
        exit(EXIT_FAILURE);
    }

    // Load the East texture
    cub->txt[3] = mlx_load_png(cub->EA_array);
    if (!cub->txt[3])
    {
        fprintf(stderr, "Failed to load the East texture\n");
        exit(EXIT_FAILURE);
    }
}