/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   draw_background.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/27 20:54:30 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/31 23:50:01 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	draw_chest(t_so_long *g)
{
	char		**map;
	size_t		j;
	size_t		i;
	uint32_t	y;
	uint32_t	x;

	j = 1;
	y = 92;
	map = g->map->map_array;
	while (map[j + 1])
	{
		i = 1;
		x = 72;
		while (map[j][i + 1] && map[j][i + 1] != '\n')
		{
			if (map[j][i] == 'C')
				put_img(g->bg, g->chest->a->frame->img, y, x);
			x += 64;
			i++;
		}
		y += 64;
		j++;
	}
}

void	start_exit_data(char c, size_t j, size_t i, t_so_long *g)
{
	if (c == 'P')
	{
		g->player->j_pos = j;
		g->player->i_pos = i;
		g->player->y_pos = j * 64;
		g->player->x_pos = i * 64 - 64;
	}
	else if (c == 'E')
	{
		g->exit->j_pos = j;
		g->exit->i_pos = i;
		g->exit->y_pos = j * 64 + 28;
		g->exit->x_pos = i * 64 + 8;
		put_img(g->bg, g->exit->closed, j * 64 + 28, i * 64 + 8);
	}
}

void	draw_background(t_so_long *game)
{
	char		**map;
	t_sprite	*s;

	map = game->map->map_array;
	draw_top_bg(map, game);
	draw_first_row(map, game);
	draw_between_rows(map, 92, game);
	draw_last_row(map, game);
	draw_bottom_bg(map, game);
	s = load_sprite_sheet("./assets/chest_01.png", 64, 64, game->mlx);
	game->chest->a = init_animation(s, 4, 0, 1);
	draw_chest(game);
}
