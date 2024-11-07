/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 19:03:41 by epolkhov          #+#    #+#             */
/*   Updated: 2024/11/05 22:05:31 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# define MAX_FILE_SIZE 1024
# define MOVE_SPEED 5.0f      // Speed of player
# define WINDOW_W 1600
# define WINDOW_H 1200
# define TITLE "cub3d"
# define AS 0.02f             // Angular Speed
# define LS 0.3f              // Linear Speed
# define FOV 1.047f           // Field Of View
# define M_PI 3.14159265358979323846

typedef struct s_line_params
{
	uint32_t	h;
	float		src_f;
	float		d_shift;
	int			texture_x;
	int			y_start;
}	t_line_params;

typedef struct s_flag
{
	int	no_flag;
	int	so_flag;
	int	ea_flag;
	int	we_flag;
	int	f_flag;
	int	c_flag;
}	t_flag;

typedef struct s_cub
{
	char			**map;
	int				height;
	int				width;
	int				player;
	int				player_w;
	int				player_h;
	char			*file;
	char			*no_array;
	char			*so_array;
	char			*we_array;
	char			*ea_array;
	char			*f_array;
	char			*c_array;
	int				f_r;
	int				f_g;
	int				f_b;
	int				c_r;
	int				c_g;
	int				c_b;
	int				valid;
	t_flag			flags;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	**txt;
	int				txt_idx;
	float			txt_w;
	float			p_x;
	float			p_y;
	float			gaze;
}	t_cub;

typedef struct s_view
{
	float	dx;
	float	dy;
	int		sx;
	int		sy;
	float	h_x;
	float	h_y;
	float	v_x;
	float	v_y;
	float	v_dist;
	float	h_dist;
	float	v_w;
	float	h_w;
}	t_view;

// Parsing functions
char	*open_file(char *argv);
void	init_main_struct(t_cub *cub);
void	init_flag_struct(t_cub *cub);
int		split_by_new_line(t_cub *cub);
int		north_array(char *line, t_cub *cub);
int		south_array(char *line, t_cub *cub);
int		west_array(char *line, t_cub *cub);
int		east_array(char *line, t_cub *cub);
int		split_to_rgb_floor(char *array, t_cub *cub);
int		split_to_rgb_ceiling(char *array, t_cub *cub);
int		floor_array(char *line, t_cub *cub);
int		ceiling_array(char *line, t_cub *cub);
void	copy_map(char **array, t_cub *cub, int start);
int		find_map_start(char *line);
int		check_all_flags_infile(t_cub *cub);
int		check_max_width_of_map(t_cub *cub);
void	replace_spaces(t_cub *cub);
int		is_map_valid(t_cub *cub);
int		check_file_permission(const char *filepath);
int		check_file_data(char *array);
int		check_format(char *file_name);
int		check_consecutive_newlines_in_map(char *file);
int		check_with_floodfill(t_cub *cub, char **map_copy);
int		check_map_content(t_cub *cub);
int		check_path(t_cub *cub);
char	*print_readfile_error(int bytes_read, int fd, char *data);
void	handle_error(char *msg, int fd, char *data);

// Game functions
int		check_sign(float f);
void	press_key(mlx_key_data_t keydata, void *param);
void	game(t_cub *cub);
float	view(t_cub *cub, float v);
int		get_rgba(int r, int g, int b, int a);
int		load_textures(t_cub *cub);
void	determine_player_position(t_cub *cub);
void	draw_ceiling_and_floor(t_cub *cub);
void	view_direction(t_cub *cub);
//void	line(t_cub *cub, int w, float dist);
void ft_line(t_cub *cub, int w, float dist);
void	view_next(t_cub *cub, t_view *view);
void	view_start(t_cub *cub, t_view *view, float angle);

// Utils and cleaning functions
void	free_array(char **arr);
void	free_all(t_cub *cub);
void	destroy_textures(t_cub *cub);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
int		has_space(char c);
int		is_all_digits(char *str);
int		check_consecutive_newlines_in_map(char *file);

#endif
