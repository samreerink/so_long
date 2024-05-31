/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   draw_background_utils.c                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/27 21:02:01 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/31 23:50:21 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	draw_top_bg(char **map, t_so_long *game)
{
	size_t		i;
	uint32_t	x;

	i = 1;
	x = 72;
	while (map[0][i + 1] && map[0][i + 1] != '\n')
	{
		put_img(game->bg, game->tiles->wall_top_m, 0, x);
		x += 64;
		i++;
	}
	put_img(game->bg, game->tiles->wall_top_l, 0, 36);
	put_img(game->bg, game->tiles->wall_top_r, 0, x - 28);
}

void	draw_first_row(char **map, t_so_long *game)
{
	size_t		i;
	uint32_t	x;

	i = 1;
	x = 72;
	while (map[0][i + 1] && map[0][i + 1] != '\n')
	{
		put_img(game->bg, game->tiles->wall_m, 28, x);
		x += 64;
		i++;
	}
	put_img(game->bg, game->tiles->wall_l, 28, 36);
	put_img(game->bg, game->tiles->wall_l, 28, x);
}

void	draw_between_rows(char	**map, uint32_t y, t_so_long *game)
{
	size_t		i;
	size_t		j;
	uint32_t	x;

	j = 1;
	while (map[j + 1])
	{
		i = 1;
		x = 72;
		while (map[j][i + 1] && map[j][i + 1] != '\n')
		{
			put_img(game->bg, game->tiles->floor, y, x);
			if (map[j][i] == '1')
				put_img(game->bg, game->tiles->object, y, x);
			else if (map[j][i] == 'P' || map[j][i] == 'E')
				start_exit_data(map[j][i], j, i, game);
			x += 64;
			i++;
		}
		put_img(game->bg, game->tiles->wall_l, y, 36);
		put_img(game->bg, game->tiles->wall_l, y, x);
		y += 64;
		j++;
	}
}

void	draw_last_row(char **map, t_so_long *game)
{
	size_t		i;
	uint32_t	y;
	uint32_t	x;

	i = 1;
	x = 72;
	y = (game->map->rows - 1) * 64 + 22;
	while (map[0][i + 1] && map[0][i + 1] != '\n')
	{
		put_img(game->bg, game->tiles->wall_top_m, y, x);
		x += 64;
		i++;
	}
	put_img(game->bg, game->tiles->wall_low_l, y - 36, 36);
	put_img(game->bg, game->tiles->wall_low_r, y - 36, x - 28);
}

void	draw_bottom_bg(char **map, t_so_long *game)
{
	size_t		i;
	uint32_t	y;
	uint32_t	x;

	i = 1;
	x = 72;
	y = (game->map->rows - 1) * 64 + 50;
	while (map[0][i + 1] && map[0][i + 1] != '\n')
	{
		put_img(game->bg, game->tiles->wall_m, y, x);
		x += 64;
		i++;
	}
	put_img(game->bg, game->tiles->wall_bottom_l, y, 36);
	put_img(game->bg, game->tiles->wall_bottom_r, y, x - 28);
}
