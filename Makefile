NAME = cub
FLAGS = -Wall -Wextra -Werror 
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_DIR = ./MLX42
MLX42_LIB = $(MLX_DIR)/build/libmlx42.a
MLX42_INCLUDE = -I./include
MLX42_FLAGS =  -lglfw -L"/Users/epolkhov/.brew/opt/glfw/lib/"

SRCS = main.c \
		
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX42_LIB)
	cc $(FLAGS) $(OBJS) $(LIBFT_LIB) $(MLX42_LIB) $(MLX42_FLAGS) -o $(NAME)

$(LIBFT_LIB): $(LIBFT_DIR)
	make -C $(LIBFT_DIR)

$(MLX42_LIB): $(MLX_DIR)
	cmake -B $(MLX_DIR)/build -S $(MLX_DIR) && cmake --build $(MLX_DIR)/build -j4

%.o: %.c
	cc $(FLAGS) $(MLX42_INCLUDE) -c $< -o $@

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