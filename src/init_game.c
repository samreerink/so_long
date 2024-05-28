/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init_game.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 21:40:43 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/28 17:33:13 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
	game->exit = ft_calloc(1, sizeof(t_exit));
	if (!game->exit)
		error_exit(NULL, "ft_calloc");
	game->exit->exit_open = false;
	return (game);
}
