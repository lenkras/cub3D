/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:12:49 by epolkhov          #+#    #+#             */
/*   Updated: 2024/10/20 22:10:24 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# define MAX_FILE_SIZE 1024

typedef struct s_flag
{
	int	NO_flag;
	int	SO_flag;
	int	EA_flag;
	int	WE_flag;
	int	F_flag;
	int	C_flag;
}	t_flag;

typedef struct  s_cub
{
	char	**map;
	int		height;
	int		width;
	int		player;
	int		player_w;
	int		player_h;
	char	*file;
	char	*NO_array;
	char	*SO_array;
	char	*WE_array;
	char	*EA_array;
	char	*F_array;
	char	*C_array;
	int		F_R;
	int		F_G;
	int		F_B;
	int		C_R;
	int		C_G;
	int		C_B;
	t_flag	flags;
	//Denis added
	mlx_t	*mlx; //mlx pointer
	mlx_image_t	*img; //image pointer
	mlx_texture_t *txt[4]; // textures
	int txt_idx; //index of the current texture
	int txt_w; //width offset in the texture
	float	p_x; //player's position
	float	p_y; //player's position
	float	gaze; //player's direction
	
} t_cub;

void	free_array(char **arr);
void	free_all(t_cub *cub);
int		is_all_digits(char *str);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
int		has_space(char c);
int		check_file_permission(const char *filepath);

char	*open_file(char *argv);
void	init_main_struct(t_cub *cub);
void	init_flag_struct(t_cub *cub);

int		north_array(char *line, t_cub *cub);
int		south_array(char *line, t_cub *cub);
int		west_array(char *line, t_cub *cub);
int		east_array(char *line, t_cub *cub);
int		split_toRGB_floor(char *array, t_cub *cub);
int		split_toRGB_ceiling(char *array, t_cub *cub);
int		floor_array(char *line, t_cub *cub);
int		ceiling_array(char *line, t_cub *cub);
void	copy_map(char **array, t_cub *cub, int start);
int		find_map_start(char *line);
int		check_all_flags_infile(t_cub *cub);

int	check_max_width_of_map(t_cub *cub);
void	replace_spaces(t_cub *cub);
int	is_map_valid(t_cub *cub);

//Denis added
# define WINDOW_W	640
# define WINDOW_H	480
# define TITLE		"cub3d"
# define AS		0.02f // Angular Speed
# define LS		0.3f // Linear Speed
# define FOV	1.047f // Field Of View

typedef struct s_view
{
    float dx;          // Delta x (ray direction on x-axis)
    float dy;          // Delta y (ray direction on y-axis)
    int sx;            // Step in x direction (1 or -1)
    int sy;            // Step in y direction (1 or -1)
    float h_x;       // Horizontal intersection x-coordinate
    float h_y;       // Horizontal intersection y-coordinate
    float v_x;      // Vertical intersection x-coordinate
    float v_y;      // Vertical intersection y-coordinate
    float v_dist;   // Distance to the vertical intersection
    float h_dist;    // Distance to the horizontal intersection
    float v_w;      // Texture offset for vertical intersection
    float h_w;       // Texture offset for horizontal intersection
} t_view;

int check_sign(float f); // float check return positiv, negativ or zero
// int key(int keycode, t_cub *cub);
void press_key(mlx_key_data_t keydata, void* param);
void destroy(void* param); 
void    game(t_cub *cub);
#endif