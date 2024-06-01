/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   key_hook_utils.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/06/01 00:45:02 by sreerink      #+#    #+#                 */
/*   Updated: 2024/06/01 22:18:55 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_player_moves(size_t n_moves)
{
	char	*str;

	str = ft_itoa(n_moves);
	write(STDIN_FILENO, "Player move count = ", 20);
	write(STDIN_FILENO, str, ft_strlen(str));
	write(STDIN_FILENO, "\n", 1);
	free(str);
}

void	move_right(t_so_long *game)
{
	game->player->i_pos++;
	game->player->x_pos += 64;
	game->player->moves_n++;
	print_player_moves(game->player->moves_n);
}

void	move_left(t_so_long *game)
{
	game->player->i_pos--;
	game->player->x_pos -= 64;
	game->player->moves_n++;
	print_player_moves(game->player->moves_n);
}

void	move_up(t_so_long *game)
{
	game->player->j_pos--;
	game->player->y_pos -= 64;
	game->player->moves_n++;
	print_player_moves(game->player->moves_n);
}

void	move_down(t_so_long *game)
{
	game->player->j_pos++;
	game->player->y_pos += 64;
	game->player->moves_n++;
	print_player_moves(game->player->moves_n);
}
