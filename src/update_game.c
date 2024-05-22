/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   update_game.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/10 21:18:37 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/22 05:01:00 by sreerink      ########   odam.nl         */
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

void	key_update(mlx_key_data_t keydata, void *ptr)
{
	t_so_long	*game;
	char		**map;
	size_t		j;
	size_t		i;

	game = (t_so_long *)ptr;
	map = game->map->map_array;
	j = game->player->j_pos;
	i = game->player->i_pos;
	if (game->game_won)
		return ;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && map[j][i + 1] != '1')
	{
		game->player->i_pos++;
		game->player->x_pos += 64;
		game->player->moves_n++;
		i++;
	}
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS && map[j][i - 1] != '1')
	{
		game->player->i_pos--;
		game->player->x_pos -= 64;
		game->player->moves_n++;
		i--;
	}
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS && map[j - 1][i] != '1')
	{
		game->player->j_pos--;
		game->player->y_pos -= 64;
		game->player->moves_n++;
		j--;
	}
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS && map[j + 1][i] != '1')
	{
		game->player->j_pos++;
		game->player->y_pos += 64;
		game->player->moves_n++;
		j++;
	}
	if (map[j][i] == 'C')
	{
		map[j][i] = '0';
		game->chest->open_chest = true;
		game->chest->open_y = j * 64 + 28;
		game->chest->open_x = i * 64 + 8;
		game->chest->n_chest--;
		printf("chest_n = %zu\n", game->chest->n_chest);
	}
	else if (map[j][i] == 'E' && game->exit->exit_open)
		game->game_won = true;
}

void	game_win_loop(t_so_long *game)
{
	char		**map;
	mlx_image_t	*p_frame;
	mlx_image_t	*e_frame;
	mlx_image_t	*c_frame;

	map = game->map->map_array;
	game->player->y_pos = game->height / 2 - 64;
	game->player->x_pos = game->width / 2 - 192;
	p_frame = get_frame_num(game->player->a, game->player->a->current_frame);
	e_frame = get_frame_num(game->effect, game->effect->current_frame);
	c_frame = get_frame_num(game->gold_chest, game->gold_chest->current_frame);
	ft_memset(game->background->pixels, 0xFF000000, game->background->width * game->background->height * sizeof(uint32_t));
	ft_memset(game->foreground->pixels, 0xFF000000, game->foreground->width * game->foreground->height * sizeof(uint32_t));
	put_img_to_img(game->background, e_frame, game->player->y_pos - 80, game->player->x_pos + 188);
	put_img_to_img(game->foreground, c_frame, game->player->y_pos, game->player->x_pos + 250);
	put_img_to_img(game->foreground, p_frame, game->player->y_pos, game->player->x_pos);
	update_animation(game->effect, game->mlx->delta_time);
	update_animation(game->gold_chest, game->mlx->delta_time);
	update_animation(game->player->a, game->mlx->delta_time);
}

void	game_loop(t_so_long *game)
{
	char		**map;
	mlx_image_t	*p_frame;
	mlx_image_t	*c_frame;

	map = game->map->map_array;
	p_frame = get_frame_num(game->player->a, game->player->a->current_frame);
	if (game->chest->open_chest)
	{
		c_frame = get_frame_num(game->chest->a, game->chest->a->current_frame);
		put_img_to_img(game->foreground, c_frame, game->chest->open_y, game->chest->open_x);
		update_animation(game->chest->a, game->mlx->delta_time);
		if (!game->chest->a->current_frame)
		{
			c_frame = get_frame_num(game->chest->a, 3);
			put_img_to_img(game->background, c_frame, game->chest->open_y, game->chest->open_x);
			game->chest->open_chest = false;
		}
	}
	if (game->chest->n_chest == 0)
	{
		game->exit->exit_open = true;
		put_img_to_img(game->background, game->exit->open, game->exit->y_pos, game->exit->x_pos);
	}
	ft_memset(game->foreground->pixels, 0xFF000000, game->foreground->width * game->foreground->height * sizeof(uint32_t));
	put_img_to_img(game->foreground, p_frame, game->player->y_pos, game->player->x_pos);
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
