/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/04/21 20:39:35 by sreerink      #+#    #+#                 */
/*   Updated: 2024/06/09 20:24:51 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char *argv[])
{
	t_so_long	*game;

	if (argc != 2)
		error_exit("Invalid amount of arguments\n", NULL, NULL);
	game = init_game(argv[1]);
	draw_background(game);
	load_fg_animations(game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_key_hook(game->mlx, key_update, game);
	mlx_close_hook(game->mlx, exit_game, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
