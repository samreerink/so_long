/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   update_game.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/10 21:18:37 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/20 19:21:09 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

mlx_image_t	*get_frame_num(t_animation *a, int cur_frame)
{
	t_frame	*temp;

	temp = a->frame;
	while (cur_frame > 0)
	{
		temp = temp->next;
		cur_frame--;
	}
	return (temp->img);
}

void	update(void *ptr)
{
	t_so_long	*game;
	mlx_image_t	*frame;

	game = (t_so_long *)ptr;
	frame = get_frame_num(game->player->a, game->player->a->current_frame);
	put_img_to_img(game->foreground, frame, game->player->y_pos, game->player->x_pos);
	update_animation(game->player->a, game->mlx->delta_time);
}
