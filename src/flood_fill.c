/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   flood_fill.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/27 21:14:59 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/27 21:15:27 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	flood_fill_map(char **map, size_t j, size_t i)
{
	if (map[j][i] == '1' || map[j][i] == 'X')
		return ;
	map[j][i] = 'X';
	flood_fill_map(map, j, i - 1);
	flood_fill_map(map, j, i + 1);
	flood_fill_map(map, j - 1, i);
	flood_fill_map(map, j + 1, i);
}

bool	check_flood_map(char **map_copy)
{
	size_t	j;
	size_t	i;

	j = 1;
	while (map_copy[j])
	{
		i = 0;
		while (map_copy[j][i])
		{
			if (map_copy[j][i] == 'C' || map_copy[j][i] == 'E')
				return (false);
			i++;
		}
		j++;
	}
	return (true);
}
