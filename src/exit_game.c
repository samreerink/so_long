/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exit_game.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/22 05:01:33 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/22 05:14:49 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	error_exit(char *msg, char *p_msg)
{
	const char	*mlx_msg;

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
}
