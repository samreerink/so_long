/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   map_check.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/24 20:06:54 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/28 16:20:28 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	store_player_data(t_map *m, size_t j, size_t i)
{
	m->p_amount++;
	m->player_j = j;
	m->player_i = i;
}

bool	check_between_line(t_map *m)
{
	size_t	j;
	size_t	i;
	char	**array;

	j = 1;
	array = m->map_array;
	while (array[j])
	{
		i = 0;
		while (array[j][i])
		{
			if (array[j][i] == 'C')
				m->c_amount++;
			else if (array[j][i] == 'P')
				store_player_data(m, j, i);
			else if (array[j][i] == 'E')
				m->e_amount++;
			else if (array[j][i] != '0' && array[j][i] != '1' \
				&& array[j][i] != '\n')
				return (false);
			i++;
		}
		j++;
	}
	return (true);
}

bool	check_n_chars(t_map *m)
{
	if (m->p_amount > 1 || m->e_amount > 1 \
	|| m->p_amount == 0 || m->e_amount == 0)
		return (false);
	return (true);
}

bool	check_walls(t_map *m)
{
	size_t	i;

	i = 0;
	while (m->map_array[0][i + 1])
	{
		if (m->map_array[0][i] != '1' || m->map_array[m->rows - 1][i] != '1')
			return (false);
		i++;
	}
	i = 1;
	while (m->map_array[i])
	{
		if (m->map_array[i][0] != '1' || m->map_array[i][m->colums - 1] != '1')
			return (false);
		i++;
	}
	return (true);
}

void	check_map(t_so_long *game)
{
	char	**map_copy;

	if (!check_between_line(game->map))
		error_exit("Invalid map\n", NULL);
	if (!check_n_chars(game->map))
		error_exit("Invalid map\n", NULL);
	game->chest->n_chest = game->map->c_amount;
	if (!check_walls(game->map))
		error_exit("Invalid map\n", NULL);
	map_copy = ft_copy_array(game->map->map_array);
	if (!map_copy)
		error_exit(NULL, "ft_copy_array");
	flood_fill_map(map_copy, game->map->player_j, game->map->player_i);
	if (!check_flood_map(map_copy))
	{
		ft_free_array(map_copy);
		error_exit("Invalid map\n", NULL);
	}
	ft_free_array(map_copy);
}
