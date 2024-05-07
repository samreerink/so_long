/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/04/21 20:39:35 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/07 22:14:09 by sreerink      ########   odam.nl         */
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
	t_animation	*fox_1;
	t_sprite_sheet	*sprite_sheet;

	game = init_game();
	sprite_sheet = load_sprite_sheet("./assets/fox.png", 32, 32, game->mlx);
	fox_1 = init_animation(sprite_sheet, 14, 1, game->mlx);
/*	if (mlx_image_to_window(game->mlx, fox_1->frame->img, 0, 0) < 0)
		error_exit();*/
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
