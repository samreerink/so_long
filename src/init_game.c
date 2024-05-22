/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init_game.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 21:40:43 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/22 04:47:24 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	check_line(char *line, t_map *map)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'C')
			map->c_amount++;
		else if (line[i] == 'P')
			map->p_amount++;
		else if (line[i] == 'E')
			map->e_amount++;
		else if (line[i] != '0' && line[i] != '1' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

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
	if (close(file) == -1)
		error_exit(NULL, "close");
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
		error_exit(NULL, "get_next_line");
	game->map->colums = ft_strlen(line);
	while (line)
	{
		game->map->rows++;
		if (!check_line(line, game->map))
			error_exit("Invalid map\n", NULL);
		free(line);
		line = get_next_line(file);
		if (game->map->colums != ft_strlen(line) && line)
			error_exit("Invalid map\n", NULL);
	}
	free(line);
	if (close(file) == -1)
		error_exit(NULL, "close");
	if (game->map->p_amount > 1 || game->map->e_amount > 1 \
	|| game->map->p_amount == 0 || game->map->e_amount == 0)
		error_exit("Invalid map\n", NULL);
	write_map_array(map_file, game);
	game->map->colums--;
}

t_so_long	*init_game(char *map_file)
{
	t_so_long	*game;

	game = ft_calloc(1, sizeof(t_so_long));
	if (!game)
		error_exit(NULL, "ft_calloc");
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		error_exit(NULL, "ft_calloc");
	init_map(map_file, game);
	game->width = (game->map->colums - 2) * 64 + 144;
	game->height = game->map->rows * 64 + 80;
	if (game->width < 500)
		game->width = 500;
	if (game->height < 300)
		game->height = 300;
	game->mlx = mlx_init(game->width, game->height, "so_long", false);
	if (!game->mlx)
		error_exit(NULL, NULL);
	game->background = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->background)
		error_exit(NULL, NULL);
	if (mlx_image_to_window(game->mlx, game->background, 0, 0) < 0)
		error_exit(NULL, NULL);
	game->foreground = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->foreground)
		error_exit(NULL, NULL);
	if (mlx_image_to_window(game->mlx, game->foreground, 0, 0) < 0)
		error_exit(NULL, NULL);
	game->tiles = ft_calloc(1, sizeof(t_bg_tiles));
	if (!game->tiles)
		error_exit(NULL, "ft_calloc");
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
		error_exit(NULL, "ft_calloc");
	game->chest = ft_calloc(1, sizeof(t_chest));
	if (!game->player)
		error_exit(NULL, "ft_calloc");
	game->chest->n_chest = game->map->c_amount;
	game->exit = ft_calloc(1, sizeof(t_exit));
	if (!game->exit)
		error_exit(NULL, "ft_calloc");
	game->exit->exit_open = false;
	return (game);
}
