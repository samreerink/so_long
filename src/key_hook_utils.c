/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   key_hook_utils.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/06/01 00:45:02 by sreerink      #+#    #+#                 */
/*   Updated: 2024/06/01 00:45:36 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	move_right(t_so_long *game)
{
	game->player->i_pos++;
	game->player->x_pos += 64;
	game->player->moves_n++;
}

void	move_left(t_so_long *game)
{
	game->player->i_pos--;
	game->player->x_pos -= 64;
	game->player->moves_n++;
}

void	move_up(t_so_long *game)
{
	game->player->j_pos--;
	game->player->y_pos -= 64;
	game->player->moves_n++;
}

void	move_down(t_so_long *game)
{
	game->player->j_pos++;
	game->player->y_pos += 64;
	game->player->moves_n++;
}
