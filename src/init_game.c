/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init_game.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 21:40:43 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/07 22:09:05 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_so_long	*init_game(void)
{
	t_so_long	*game;

	game = malloc(sizeof(t_so_long));
	if (!game)
		error_exit();
	game->mlx = mlx_init(WIDTH, HEIGTH, "so_long", false);
	if (!game->mlx)
		error_exit();
	game->background = NULL;
	game->foreground = mlx_new_image(game->mlx, WIDTH, HEIGTH);
	if (!game->foreground)
		error_exit();
	if (mlx_image_to_window(game->mlx, game->foreground, 0, 0) < 0)
		error_exit();
	return (game);
}
