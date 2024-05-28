/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init_map.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/27 21:21:34 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/27 21:21:36 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	write_map_array(char *map_file, t_so_long *game)
{
	int	file;
	char	*line;
	size_t	i;

	i = 0;
	game->map->map_array = ft_calloc(game->map->rows + 1, sizeof(char *));
	if (!game->map->map_array)
		error_exit(NULL, "ft_calloc");
	file = open(map_file, O_RDONLY);
	if (file == -1)
		error_exit(NULL, map_file);
	line = get_next_line(file);
	if (!line)
		error_exit(NULL, "get_next_line");
	while (line)
	{
		game->map->map_array[i] = ft_strdup(line);
		if (!game->map->map_array[i])
			error_exit(NULL, "ft_strdup");
		free(line);
		line = get_next_line(file);
		i++;
	}
	free(line);
	close(file);
}

void	init_map(char *map_file, t_so_long *game)
{
	int	file;
	char	*line;

	file = open(map_file, O_RDONLY);
	if (file == -1)
		error_exit(NULL, map_file);
	line = get_next_line(file);
	if (!line)
		error_exit("Invalid map\n", NULL);
	game->map->colums = ft_strlen(line);
	while (line)
	{
		game->map->rows++;
		free(line);
		line = get_next_line(file);
		if (game->map->colums != ft_strlen(line) && line)
			error_exit("Invalid map\n", NULL);
	}
	free(line);
	if (close(file) == -1)
		error_exit(NULL, "close");
	write_map_array(map_file, game);
	game->map->colums--;
}
