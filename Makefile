# **************************************************************************** #
#                                                                              #
#                                                        ::::::::              #
#    Makefile                                          :+:    :+:              #
#                                                     +:+                      #
#    By: sreerink <sreerink@student.codam.nl>        +#+                       #
#                                                   +#+                        #
#    Created: 2024/02/10 21:57:52 by sreerink      #+#    #+#                  #
#    Updated: 2024/06/14 22:33:07 by sreerink      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME= 		so_long

RM= 		rm -rf

FLAGS= 		-Wall -Werror -Wextra

SRC_DIR=	src

OBJ_DIR=	obj

SRCS=		$(addprefix $(SRC_DIR)/, main.c init_game.c animation.c \
		map_check.c update_game.c image_utils.c exit_game.c \
		draw_background.c draw_background_utils.c init_map.c \
		flood_fill.c ft_put_pixel.c load_fg_anim.c key_hook.c \
		key_hook_utils.c free_animation.c)	

OBJ=		$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

MLX=		./MLX42
MLX_REPO=	https://github.com/codam-coding-college/MLX42.git
MLX_BRANCH=	ca0f163
MLX_LIB=	$(MLX)/build/libmlx42.a
MLX_FLAGS=	$(MLX_LIB) -ldl -lglfw -pthread -lm

LIBFT=		./Libft
LIBFT_REPO=	https://github.com/samreerink/Libft.git
LIBFT_BRANCH= 81f7060
LIBFT_LIB=	$(LIBFT)/libft.a

HEADERS=	-I $(LIBFT) -I $(MLX)/include

all:	$(NAME)

$(MLX):
	git clone -b $(MLX_BRANCH) $(MLX_REPO) $(MLX)

$(LIBFT):
	git clone -b $(LIBFT_BRANCH) $(LIBFT_REPO) $(LIBFT)

$(MLX_LIB): | $(MLX)
	@if [ ! -f $(MLX_LIB) ]; then \
		cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4; \
	fi

$(LIBFT_LIB): | $(LIBFT)
	$(MAKE) -C $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAGS) -L$(LIBFT) -lft -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT) clean
	$(RM) $(MLX)/build

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
