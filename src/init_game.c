/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init_game.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 21:40:43 by sreerink      #+#    #+#                 */
/*   Updated: 2024/06/01 20:42:29 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_window_and_images(t_so_long *game)
{
	game->width = (game->map->colums - 2) * 64 + 144;
	game->height = game->map->rows * 64 + 80;
	if (game->width < 500)
		game->width = 500;
	if (game->height < 300)
		game->height = 300;
	game->mlx = mlx_init(game->width, game->height, "so_long", false);
	if (!game->mlx)
		error_exit(NULL, NULL, game);
	game->bg = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->bg)
		error_exit(NULL, NULL, game);
	if (mlx_image_to_window(game->mlx, game->bg, 0, 0) < 0)
		error_exit(NULL, NULL, game);
	game->fg = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->fg)
		error_exit(NULL, NULL, game);
	if (mlx_image_to_window(game->mlx, game->fg, 0, 0) < 0)
		error_exit(NULL, NULL, game);
}

void	init_objects(t_so_long *game)
{
	game->tiles = ft_calloc(1, sizeof(t_bg_tiles));
	if (!game->tiles)
		error_exit(NULL, "ft_calloc", game);
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
		error_exit(NULL, "ft_calloc", game);
	game->chest = ft_calloc(1, sizeof(t_chest));
	if (!game->player)
		error_exit(NULL, "ft_calloc", game);
	game->exit = ft_calloc(1, sizeof(t_exit));
	if (!game->exit)
		error_exit(NULL, "ft_calloc", game);
	game->exit->exit_open = false;
}

void	load_background_assets(t_so_long *g)
{
	g->tiles->wall_l = load_png_to_image("./assets/tile009.png", g);
	g->tiles->wall_m = load_png_to_image("./assets/tile034.png", g);
	g->tiles->wall_top_l = load_png_to_image("./assets/tile025.png", g);
	g->tiles->wall_top_m = load_png_to_image("./assets/tile026.png", g);
	g->tiles->wall_top_r = load_png_to_image("./assets/tile027.png", g);
	g->tiles->wall_low_l = load_png_to_image("./assets/tile017_wood.png", g);
	g->tiles->wall_low_r = load_png_to_image("./assets/tile019_wood.png", g);
	g->tiles->wall_bottom_l = load_png_to_image("./assets/tile033.png", g);
	g->tiles->wall_bottom_r = load_png_to_image("./assets/tile035.png", g);
	g->tiles->floor = load_png_to_image("./assets/wooden.png", g);
	g->tiles->object = load_png_to_image("./assets/tile002.png", g);
	g->exit->closed = load_png_to_image("./assets/wooden_door_closed.png", g);
	g->exit->open = load_png_to_image("./assets/wooden_door_open.png", g);
}

t_so_long	*init_game(char *map_file)
{
	t_so_long	*game;

	if (!ft_check_end_str(map_file, ".ber"))
		error_exit("File format needs to be .ber\n", NULL, NULL);
	game = ft_calloc(1, sizeof(t_so_long));
	if (!game)
		error_exit(NULL, "ft_calloc", NULL);
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		error_exit(NULL, "ft_calloc", game);
	init_map(map_file, game);
	init_objects(game);
	check_map(game);
	init_window_and_images(game);
	load_background_assets(game);
	return (game);
}
