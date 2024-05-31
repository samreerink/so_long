/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   key_hook.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/31 23:35:39 by sreerink      #+#    #+#                 */
/*   Updated: 2024/06/01 00:45:40 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	check_input_wasd(mlx_key_data_t k, char **map, t_so_long *g)
{
	size_t		j;
	size_t		i;

	j = g->player->j_pos;
	i = g->player->i_pos;
	if (k.key == MLX_KEY_D \
	&& k.action == MLX_PRESS && map[j][i + 1] != '1')
		move_right(g);
	else if (k.key == MLX_KEY_A \
	&& k.action == MLX_PRESS && map[j][i - 1] != '1')
		move_left(g);
	else if (k.key == MLX_KEY_W \
	&& k.action == MLX_PRESS && map[j - 1][i] != '1')
		move_up(g);
	else if (k.key == MLX_KEY_S \
	&& k.action == MLX_PRESS && map[j + 1][i] != '1')
		move_down(g);
}

void	key_update(mlx_key_data_t keydata, void *ptr)
{
	t_so_long	*g;
	char		**map;
	size_t		j;
	size_t		i;

	g = (t_so_long *)ptr;
	map = g->map->map_array;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit_game(g);
	if (g->game_won)
		return ;
	check_input_wasd(keydata, map, g);
	j = g->player->j_pos;
	i = g->player->i_pos;
	if (map[j][i] == 'C')
	{
		map[j][i] = '0';
		g->chest->open_chest = true;
		g->chest->open_y = j * 64 + 28;
		g->chest->open_x = i * 64 + 8;
		g->chest->n_chest--;
	}
	else if (map[j][i] == 'E' && g->exit->exit_open)
		g->game_won = true;
}
