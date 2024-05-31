/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   update_game.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/10 21:18:37 by sreerink      #+#    #+#                 */
/*   Updated: 2024/06/01 00:01:31 by sreerink      ########   odam.nl         */
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

void	chest_check(t_so_long *g)
{
	mlx_image_t	*c_frame;

	if (g->chest->open_chest)
	{
		c_frame = get_frame_num(g->chest->a, g->chest->a->current_frame);
		put_img(g->fg, c_frame, g->chest->open_y, g->chest->open_x);
		update_animation(g->chest->a, g->mlx->delta_time);
		if (!g->chest->a->current_frame)
		{
			c_frame = get_frame_num(g->chest->a, 3);
			put_img(g->bg, c_frame, g->chest->open_y, g->chest->open_x);
			g->chest->open_chest = false;
		}
	}
	if (g->chest->n_chest == 0)
	{
		g->exit->exit_open = true;
		put_img(g->bg, g->exit->open, g->exit->y_pos, g->exit->x_pos);
	}
}

void	game_win_loop(t_so_long *g)
{
	char		**map;
	mlx_image_t	*p_frame;
	mlx_image_t	*e_frame;
	mlx_image_t	*c_frame;

	map = g->map->map_array;
	g->player->y_pos = g->height / 2 - 64;
	g->player->x_pos = g->width / 2 - 192;
	p_frame = get_frame_num(g->player->a, g->player->a->current_frame);
	e_frame = get_frame_num(g->effect, g->effect->current_frame);
	c_frame = get_frame_num(g->gold_chest, g->gold_chest->current_frame);
	clear_image(g->bg);
	clear_image(g->fg);
	put_img(g->bg, e_frame, g->player->y_pos - 80, g->player->x_pos + 188);
	put_img(g->fg, c_frame, g->player->y_pos, g->player->x_pos + 250);
	put_img(g->fg, p_frame, g->player->y_pos, g->player->x_pos);
	update_animation(g->effect, g->mlx->delta_time);
	update_animation(g->gold_chest, g->mlx->delta_time);
	update_animation(g->player->a, g->mlx->delta_time);
}

void	game_loop(t_so_long *game)
{
	char		**map;
	mlx_image_t	*p_frame;

	map = game->map->map_array;
	p_frame = get_frame_num(game->player->a, game->player->a->current_frame);
	chest_check(game);
	clear_image(game->fg);
	put_img(game->fg, p_frame, game->player->y_pos, game->player->x_pos);
	update_animation(game->player->a, game->mlx->delta_time);
}

void	update(void *ptr)
{
	t_so_long	*game;

	game = (t_so_long *)ptr;
	if (game->game_won)
		game_win_loop(game);
	else
		game_loop(game);
}
