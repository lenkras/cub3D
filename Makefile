NAME = cub
FLAGS = -Wall -Wextra -Werror 
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_DIR = ./MLX42
MLX42_LIB = $(MLX_DIR)/build/libmlx42.a
MLX42_INCLUDE = -I$(MLX_DIR)/include -ldl -lglfw -pthread -lm

SRCS = cub.c \
		utils_functions.c \
		parsing.c \
		process_file.c \
		parse_rgb_for_floor_ceiling.c \
		initialising.c \
		map_validation.c \
		game.c \
		move.c \
		clean.c \
		utils_for_parsing.c \
		utils_for_game.c \
		parse_north_texture.c \
		parse_south_texture.c \
		parse_east_texture.c \
		parse_west_texture.c \
		parse_ceiling.c \
		parse_floor.c \
		check_content.c \
		check_path.c \
		view.c \
		draw.c \
		textures.c\

		
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX42_LIB)
	gcc $(FLAGS) $(OBJS) $(LIBFT_LIB) $(MLX42_LIB) -o $(NAME) $(MLX42_INCLUDE)

$(LIBFT_LIB): $(LIBFT_DIR)
	make -C $(LIBFT_DIR)

$(MLX42_LIB): $(MLX_DIR)
	cmake -B $(MLX_DIR)/build -S $(MLX_DIR) && cmake --build $(MLX_DIR)/build -j4

%.o: %.c
	gcc $(FLAGS) $(MLX42_INCLUDE) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(MLX_DIR)/build
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(MLX_DIR)/build
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re