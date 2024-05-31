# **************************************************************************** #
#                                                                              #
#                                                        ::::::::              #
#    Makefile                                          :+:    :+:              #
#                                                     +:+                      #
#    By: sreerink <sreerink@student.codam.nl>        +#+                       #
#                                                   +#+                        #
#    Created: 2024/02/10 21:57:52 by sreerink      #+#    #+#                  #
#    Updated: 2024/06/01 00:48:01 by sreerink      ########   odam.nl          #
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
		key_hook_utils.c)	

OBJ=		$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

MLX=		./MLX42

LIBS_MLX=	$(MLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

LIBFT=		./Libft/libft.a

HEADERS=	-I ./Libft -I $(MLX)/include


all:	mlx $(NAME)

mlx:
	@cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./Libft

$(NAME): 	$(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBS_MLX) -L./Libft -lft -o $(NAME)

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
