/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   so_long.h                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/04/21 20:52:34 by sreerink      #+#    #+#                 */
/*   Updated: 2024/06/14 21:40:32 by sreerink      ########   odam.nl         */
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

typedef struct s_map
{
	int		file;
	char	**map_array;
	size_t	c_amount;
	size_t	p_amount;
	size_t	e_amount;
	size_t	rows;
	size_t	colums;
	size_t	player_j;
	size_t	player_i;
}	t_map;

typedef struct s_bg_tiles
{
	mlx_image_t	*wall_top_l;
	mlx_image_t	*wall_top_m;
	mlx_image_t	*wall_top_r;
	mlx_image_t	*wall_l;
	mlx_image_t	*wall_m;
	mlx_image_t	*wall_low_l;
	mlx_image_t	*wall_low_r;
	mlx_image_t	*wall_bottom_l;
	mlx_image_t	*wall_bottom_r;
	mlx_image_t	*floor;
	mlx_image_t	*object;
}	t_bg_tiles;

typedef struct s_player
{
	t_animation	*a;
	size_t		moves_n;
	size_t		j_pos;
	size_t		i_pos;
	uint32_t	y_pos;
	uint32_t	x_pos;
}	t_player;

typedef struct s_chest
{
	t_animation	*a;
	bool		open_chest;
	uint32_t	open_y;
	uint32_t	open_x;
	size_t		n_chest;
}	t_chest;

typedef struct s_exit
{
	mlx_image_t	*closed;
	mlx_image_t	*open;
	uint32_t	y_pos;
	uint32_t	x_pos;
	size_t		j_pos;
	size_t		i_pos;
	bool		exit_open;
}	t_exit;

typedef struct s_so_long
{
	mlx_t		*mlx;
	mlx_image_t	*bg;
	mlx_image_t	*fg;
	t_bg_tiles	*tiles;
	t_map		*map;
	t_player	*player;
	t_chest		*chest;
	t_exit		*exit;
	bool		game_won;
	t_animation	*effect;
	t_animation	*gold_chest;
	uint32_t	width;
	uint32_t	height;
}	t_so_long;

// Functions

void		error_exit(char *msg, char *p_msg, t_so_long *game);

void		exit_game(void *ptr);

t_so_long	*init_game(char *map_file);

void		check_map(t_so_long *game);

void		key_update(mlx_key_data_t keydata, void *ptr);

void		update(void *ptr);

mlx_image_t	*load_png_to_image(char *path_png, t_so_long *game);

void		px_to_px(mlx_image_t *d, mlx_image_t *s, \
			uint32_t i_dst, uint32_t i_src);

void		clear_image(mlx_image_t *img);

void		put_img(mlx_image_t *dst, mlx_image_t *src, uint32_t y, uint32_t x);

void		init_map(char *map_file, t_so_long *game);

void		flood_fill_map(char **map, size_t j, size_t i);

bool		check_flood_map(char **map_copy);

void		draw_background(t_so_long *game);

void		draw_top_bg(char **map, t_so_long *game);

void		draw_first_row(char **map, t_so_long *game);

void		draw_between_rows(char	**map, uint32_t y, t_so_long *game);

void		draw_last_row(char **map, t_so_long *game);

void		draw_bottom_bg(char **map, t_so_long *game);

void		draw_chest(t_so_long *game);

void		start_exit_data(char c, size_t j, size_t i, t_so_long *g);

void		load_fg_animations(t_so_long *game);

void		move_right(t_so_long *game);

void		move_left(t_so_long *game);

void		move_up(t_so_long *game);

void		move_down(t_so_long *game);

#endif
