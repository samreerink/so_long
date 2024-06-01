/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init_map.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/27 21:21:34 by sreerink      #+#    #+#                 */
/*   Updated: 2024/06/01 20:06:21 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	write_map_array(char *map_file, t_so_long *game)
{
	char	*line;
	size_t	i;

	i = 0;
	game->map->map_array = ft_calloc(game->map->rows + 1, sizeof(char *));
	if (!game->map->map_array)
		error_exit(NULL, "ft_calloc", game);
	game->map->file = open(map_file, O_RDONLY);
	if (game->map->file == -1)
		error_exit(NULL, map_file, game);
	line = get_next_line(game->map->file);
	if (!line)
		error_exit(NULL, "get_next_line", game);
	while (line)
	{
		game->map->map_array[i] = ft_strdup(line);
		free(line);
		if (!game->map->map_array[i])
			error_exit(NULL, "ft_strdup", game);
		line = get_next_line(game->map->file);
		i++;
	}
	free(line);
	if (close(game->map->file) == -1)
		error_exit(NULL, "close", game);
}

void	init_map(char *map_file, t_so_long *game)
{
	char	*line;

	game->map->file = open(map_file, O_RDONLY);
	if (game->map->file == -1)
		error_exit(NULL, map_file, game);
	line = get_next_line(game->map->file);
	if (!line)
		error_exit("Invalid map\n", NULL, game);
	game->map->colums = ft_strlen(line);
	while (line)
	{
		game->map->rows++;
		free(line);
		line = get_next_line(game->map->file);
		if (game->map->colums != ft_strlen(line) && line)
			error_exit("Invalid map\n", NULL, game);
	}
	free(line);
	if (close(game->map->file) == -1)
		error_exit(NULL, "close", game);
	write_map_array(map_file, game);
	game->map->colums--;
}
