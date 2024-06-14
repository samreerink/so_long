# **************************************************************************** #
#                                                                              #
#                                                        ::::::::              #
#    Makefile                                          :+:    :+:              #
#                                                     +:+                      #
#    By: sreerink <sreerink@student.codam.nl>        +#+                       #
#                                                   +#+                        #
#    Created: 2024/02/10 21:57:52 by sreerink      #+#    #+#                  #
#    Updated: 2024/06/14 22:12:22 by sreerink      ########   odam.nl          #
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

MLX_LIB=	$(MLX)/build/libmlx42.a

MLX_FLAGS=	$(MLX_LIB) -ldl -lglfw -pthread -lm

LIBFT=		./Libft/libft.a

HEADERS=	-I ./Libft -I $(MLX)/include


all:	$(NAME)

$(MLX_LIB):
	@if [ ! -f $(MLX_LIB) ]; then \
		cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4; \
	fi

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./Libft

$(NAME): 	$(LIBFT) $(MLX_LIB) $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAGS) -L./Libft -lft -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_DIR)
	$(RM) $(MLX)/build
	$(MAKE) -C ./Libft clean

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) -C ./Libft fclean

re:		fclean all

.PHONY:	all clean fclean re
