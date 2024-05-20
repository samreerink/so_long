/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   so_long.h                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/04/21 20:52:34 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/20 19:18:09 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "./animation.h"
# include "../Libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

#define WIDTH 2000
#define HEIGTH 2000

typedef struct s_map {
	char	**map_array;
	size_t	c_amount;
	size_t	p_amount;
	size_t	e_amount;
	size_t	rows;
} t_map;

typedef struct s_bg_tiles {
	mlx_image_t	*wall_top_l;
	mlx_image_t	*wall_top_m;
	mlx_image_t	*wall_top_r;
	mlx_image_t	*wall_l;
	mlx_image_t	*wall_m;
	mlx_image_t	*floor;
} t_bg_tiles;

typedef struct s_player {
	t_animation	*a;
	uint32_t	y_pos;
	uint32_t	x_pos;
} t_player;

typedef struct s_so_long {
	mlx_t		*mlx;
	mlx_image_t	*background;
	mlx_image_t	*foreground;
	t_bg_tiles	*tiles;
	t_map		*map;
	t_player	*player;
} t_so_long;


// Functions

void		error_exit(char *msg, char *p_msg);

t_so_long	*init_game(char *map_file);

void		update(void *ptr);

void		put_img_to_img(mlx_image_t *dst, mlx_image_t *src, uint32_t y, uint32_t x);

#endif
