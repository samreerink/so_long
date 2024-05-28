/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/04/21 20:39:35 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/28 17:29:49 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char *argv[])
{
	t_so_long	*game;
	t_sprite	*sprite_sheet;

	if (argc != 2)
		error_exit("Invalid amount of arguments\n", NULL);
	game = init_game(argv[1]);
	check_map(game);
	load_background_assets(game);
	draw_background(game);
	sprite_sheet = load_sprite_sheet("./assets/player_02.png", 92, 192, game->mlx);
	game->player->a = init_animation(sprite_sheet, 6, 0, 120);
	sprite_sheet = load_sprite_sheet("./assets/chest_01.png", 64, 64, game->mlx);
	game->chest->a = init_animation(sprite_sheet, 4, 0, 1);
	draw_chest(game);
	sprite_sheet = load_sprite_sheet("./assets/Effect.png", 192, 192, game->mlx);
	game->effect = init_animation(sprite_sheet, 10, 0, 120);
	sprite_sheet = load_sprite_sheet("./assets/chest_02.png", 64, 64, game->mlx);
	game->gold_chest = init_animation(sprite_sheet, 4, 0, 120);
	mlx_loop_hook(game->mlx, update, game);
	mlx_key_hook(game->mlx, key_update, game);
	mlx_close_hook(game->mlx, exit_game, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
