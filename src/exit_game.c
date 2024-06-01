/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exit_game.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/22 05:01:33 by sreerink      #+#    #+#                 */
/*   Updated: 2024/06/01 22:13:51 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	free_game(t_so_long *game)
{
	printf("Inside free_game() function\n");
	mlx_terminate(game->mlx);
	if (!game)
		return ;
	if (game->map->map_array)
		ft_free_array(game->map->map_array);
	if (game->map->file > 0)
		close(game->map->file);
	free(game->map);
	free(game->tiles);
	free_anim(game->player->a);
	free(game->player);
	free_anim(game->chest->a);
	free(game->chest);
	free(game->exit);
	free_anim(game->effect);
	free_anim(game->gold_chest);
}

void	error_exit(char *msg, char *p_msg, t_so_long *game)
{
	const char	*mlx_msg;

	free_game(game);
	write(STDERR_FILENO, "Error\n", 6);
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	if (p_msg)
		perror(p_msg);
	if (mlx_errno)
	{
		mlx_msg = mlx_strerror(mlx_errno);
		write(STDERR_FILENO, mlx_msg, ft_strlen(mlx_msg));
	}
	exit(EXIT_FAILURE);
}

void	exit_game(void *ptr)
{
	t_so_long	*game;

	game = (t_so_long *)ptr;
	printf("Inside exit_game() function\n");
	free_game(game);
	exit(EXIT_SUCCESS);
}
