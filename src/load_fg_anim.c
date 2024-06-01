/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   load_fg_anim.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/28 18:23:34 by sreerink      #+#    #+#                 */
/*   Updated: 2024/06/01 21:39:32 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	load_fg_animations(t_so_long *game)
{
	t_sprite	*s;

	s = load_sprite_sheet("./assets/player_02.png", 92, 192, game->mlx);
	game->player->a = init_animation(s, 6, 0, 120);
	if (!game->player->a)
		error_exit(NULL, "init_animation", game);
	s = load_sprite_sheet("./assets/Effect.png", 192, 192, game->mlx);
	game->effect = init_animation(s, 10, 0, 120);
	if (!game->effect)
		error_exit(NULL, "init_animation", game);
	s = load_sprite_sheet("./assets/chest_02.png", 64, 64, game->mlx);
	game->gold_chest = init_animation(s, 4, 0, 120);
	if (!game->gold_chest)
		error_exit(NULL, "init_animation", game);
}
