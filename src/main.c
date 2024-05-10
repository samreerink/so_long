/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/04/21 20:39:35 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/10 22:57:17 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	error_exit(void)
{
	const char	*msg;

	if (mlx_errno)
	{
		msg = mlx_strerror(mlx_errno);
		write(STDERR_FILENO, msg, ft_strlen(msg));
	}
	exit(EXIT_FAILURE);
}

int	main(void)
{
	t_so_long	*game;
	t_sprite_sheet	*sprite_sheet;

	game = init_game();
	sprite_sheet = load_sprite_sheet("./assets/fox.png", 32, 32, game->mlx);
	game->a = init_animation(sprite_sheet, 14, 1, 120, game->mlx);
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
