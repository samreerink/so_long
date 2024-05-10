/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   update_game.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/10 21:18:37 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/10 22:53:55 by sreerink      ########   odam.nl         */
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
	frame = get_frame_num(game->a, game->a->current_frame);
	put_img_to_img(game->foreground, frame, 0, 0);
	update_animation(game->a, game->mlx->delta_time);
}
