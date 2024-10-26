#include "cub.h"

void load_textures(t_cub *cub);
void determine_player_position(t_cub *cub);
void draw_ceiling_and_floor(t_cub *cub);
void view_direction(t_cub *cub);
void line(t_cub *cub, int w, float dist);
float view(t_cub *cub, float v);
void view_next(t_cub *cub, t_view *view);
void view_start(t_cub *cub, t_view *view, float angle);

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


void close_window(void *param)
{
    t_cub *cub = (t_cub *)param;
    mlx_terminate(cub->mlx);
//    exit(0);
}

void	render(t_cub *cub)
{
	ft_memset(cub->img->pixels, 0, (cub->img->width * cub->img->height)
		* sizeof(int32_t));
    draw_ceiling_and_floor(cub);
    view_direction(cub);
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
//	draw(cub);
    cub->img = mlx_new_image(cub->mlx, WINDOW_W, WINDOW_H);
    if (!cub->img)
    {
        fprintf(stderr, "Failed to create an image\n");
        return;
    }

    // Call functions to draw content
//    draw_ceiling_and_floor(cub);
//    view_direction(cub);
    mlx_image_to_window(cub->mlx, cub->img, 0, 0);

    mlx_key_hook(cub->mlx, press_key, cub);
//    mlx_loop_hook(cub->mlx, (void *) press_key, cub);
    mlx_loop_hook(cub->mlx, (void *)render, cub);
    mlx_loop(cub->mlx);
//    mlx_close_hook(cub->mlx, close_window, cub);
    // Clean up on exit
//    mlx_terminate(cub->mlx);
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

// void	line(t_cub *cub, int x, float dist)
// {
// 	mlx_texture_t	*texture = cub->txt[cub->txt_idx]; // Текстура в формате mlx_texture_t
// 	uint32_t		h;
// 	float			src_f;
// 	float			d_shift;
// //	uint32_t		texture_width = texture->width;
// 	uint32_t		texture_height = texture->height;

// 	h = (float) WINDOW_H / dist;
// 	src_f = 0.0f;
// 	d_shift = (float) texture_height / h;

// 	if (h > WINDOW_H)
// 	{
// 		src_f = 0.5f * (h - WINDOW_H) / h * texture_height;
// 		h = WINDOW_H;
// 	}

// 	// Вычисляем начальную вертикальную позицию для центрирования
// 	int y_start = (WINDOW_H - h) / 2;

// 	// Цикл отрисовки линии
// 	for (uint32_t y = 0; y < h; y++)
// 	{
// 		// Индекс текущего пикселя текстуры
// 	//	uint32_t color = ((uint32_t *)texture->pixels)[((int)src_f) * texture_width + cub->txt_w];
//         uint32_t color = get_pixel(texture, cub->txt_w, (int)src_f);

// 		// Отрисовываем пиксель в позиции (w, y_start + y) на основном изображении cub->img
// 		mlx_put_pixel(cub->img, x, y_start + y, color);

// 		// Продвигаем src_f на следующий пиксель текстуры
// 		src_f += d_shift;
// 	}
// }


void	line(t_cub *cub, int x, float dist)
{
	mlx_texture_t	*texture = cub->txt[cub->txt_idx]; // Текущая текстура
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

	// Определяем, какой столбец текстуры использовать
	int texture_x = (x * texture->width) / WINDOW_W;

	// Вычисляем начальную вертикальную позицию для центрирования
	int y_start = (WINDOW_H - h) / 2;

	// Цикл отрисовки линии
	for (uint32_t y = 0; y < h; y++)
	{
		// Получаем цвет пикселя текстуры, используя фиксированное значение texture_x и изменяющееся src_f
		uint32_t color = get_pixel(texture, texture_x, (int)src_f);

		// Отрисовываем пиксель в позиции (x, y_start + y) на основном изображении cub->img
		mlx_put_pixel(cub->img, x, y_start + y, color);

		// Продвигаем src_f на следующий пиксель текстуры
		src_f += d_shift;
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
        line(cub, x, view(cub, v) * cos(cub->gaze - v));
        v += dv;
    }
}

float	view(t_cub *cub, float v)
{
	t_view	view;

	// Инициализация начальных параметров для луча
	view_start(cub, &view, v);

	// Основной цикл для расчета пересечений луча с вертикальными и горизонтальными линиями
	while (1)
	{
		view_next(cub, &view);

		// Проверка на пересечение с вертикальной линией (стеной)
		if (view.v_dist < view.h_dist)
		{
			// Если достигли стены
			if (cub->map[(int)view.v_y][(int)view.v_x + (view.sx - 1) / 2] == '1')
			{
				// Сохраняем параметры цвета и возвращаем расстояние
				cub->txt_idx = view.sx + 1;
				cub->txt_w = view.v_w;
				return (view.v_dist);
			}
			else
			{
				// Если не стена, сдвигаемся на следующий шаг по вертикали
				view.v_x += view.sx;
			}
		}
		// Проверка на пересечение с горизонтальной линией (стеной)
		else
		{
			// Если достигли стены
			if (cub->map[(int)view.h_y + (view.sy - 1) / 2][(int)view.h_x] == '1')
			{
				// Сохраняем параметры цвета и возвращаем расстояние
				cub->txt_idx = view.sy + 2;
				cub->txt_w = view.h_w;
				return (view.h_dist);
			}
			else
			{
				// Если не стена, сдвигаемся на следующий шаг по горизонтали
				view.h_y += view.sy;
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

    view->v_x = (int) cub->p_x;
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
        // Calculate the next vertical distance intersection
        view->v_y = cub->p_y + view->dy / view->dx * (view->v_x - cub->p_x);
        view->v_dist = sqrt(pow(cub->p_x - view->v_x, 2.0) + pow(cub->p_y - view->v_y, 2.0));
        if (view->sx > 0)
            view->v_w = 1 - view->v_w;
        // Debug output for vertical distance calculations
        //printf("Next vertical distance: %f (v_x: %f, v_y: %f)\n", view->v_dist, view->v_x, view->v_y);
        
    }
    else
        view->v_dist = INFINITY;

    if (view->sy != 0)
    {
        // Calculate the next horizontal distance intersection
        view->h_x = cub->p_x + view->dx / view->dy * (view->h_y - cub->p_y);
        view->h_dist = sqrt(pow(cub->p_x - view->h_x, 2.0) + pow(cub->p_y - view->h_y, 2.0));
        view->h_w = view->h_x - (int) view->h_x;
        if (view->sy < 0)
			view->h_w = 1 - view->h_w;
        // Debug output for horizontal distance calculations
        //printf("Next horizontal distance: %f (h_x: %f, h_y: %f)\n", view->h_dist, view->h_x, view->h_y);
    }
    else
        view->h_dist = INFINITY;
}



void load_textures(t_cub *cub)
{
    cub->txt = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 5);
    if (!cub->txt)
    {
        printf("Can't malloc memmory for textures!");
        exit(1);
    }
    // Load the North texture
   // printf("Loading North texture from: %s\n", cub->NO_array);
    cub->txt[0] = mlx_load_png(cub->NO_array);
    if (!cub->txt[0])
    {
        fprintf(stderr, "Failed to load the North texture from %s\n", cub->NO_array);
        exit(EXIT_FAILURE);
    }
    //printf("North texture loaded: Width = %d, Height = %d\n", cub->txt[0]->width, cub->txt[0]->height);

    // Load the South texture
    //printf("Loading South texture from: %s\n", cub->SO_array);
    cub->txt[1] = mlx_load_png(cub->SO_array);
    if (!cub->txt[1])
    {
        fprintf(stderr, "Failed to load the South texture from %s\n", cub->SO_array);
        exit(EXIT_FAILURE);
    }
    //printf("South texture loaded: Width = %d, Height = %d\n", cub->txt[1]->width, cub->txt[1]->height);

    // Load the West texture
   // printf("Loading West texture from: %s\n", cub->WE_array);
    cub->txt[2] = mlx_load_png(cub->WE_array);
    if (!cub->txt[2])
    {
        fprintf(stderr, "Failed to load the West texture from %s\n", cub->WE_array);
        exit(EXIT_FAILURE);
    }
   // printf("West texture loaded: Width = %d, Height = %d\n", cub->txt[2]->width, cub->txt[2]->height);

    // Load the East texture
    //printf("Loading East texture from: %s\n", cub->EA_array);
    cub->txt[3] = mlx_load_png(cub->EA_array);
    if (!cub->txt[3])
    {
        fprintf(stderr, "Failed to load the East texture from %s\n", cub->EA_array);
        exit(EXIT_FAILURE);
    }
    //printf("East texture loaded: Width = %d, Height = %d\n", cub->txt[3]->width, cub->txt[3]->height);
}

void view_set_angle(t_cub *cub, const char c)
{
    if (c == 'E')
        cub->gaze = 0.0f * M_PI; // Set view angle to East
    else if (c == 'N')
        cub->gaze = 0.5f * M_PI; // Set view angle to North
    else if (c == 'W')
        cub->gaze = 1.0f * M_PI; // Set view angle to West
    else if (c == 'S')
        cub->gaze = -0.5f * M_PI; // Set view angle to South
    printf("\nSet view angle to %c = %f\n", c, cub->gaze);
}


void determine_player_position(t_cub *cub)
{
    // Debugging: Print initial player position
    printf("Initial player position at map[%d][%d]: %c\n", cub->player_h, cub->player_w, cub->map[cub->player_h][cub->player_w]);

    cub->p_x = (float)cub->player_w + 0.5f; // Set player x-position
    cub->p_y = (float)cub->player_h + 0.5f; // Set player y-position
    view_set_angle(cub, cub->map[cub->player_h][cub->player_w]); // Set view angle based on map character
}

