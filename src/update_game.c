/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   update_game.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/10 21:18:37 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/21 08:08:04 by sreerink      ########   odam.nl         */
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

void	key_update(mlx_key_data_t keydata, void* ptr)
{
	t_so_long	*game;
	char		**map;
	size_t		j;
	size_t		i;

	game = (t_so_long *)ptr;
	map = game->map->map_array;
	j = game->player->j_pos;
	i = game->player->i_pos;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && map[j][i + 1] != '1')
	{
		game->player->i_pos++;
		game->player->x_pos += 64;
		game->player->moves_n++;
	}
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS && map[j][i - 1] != '1')
	{
		game->player->i_pos--;
		game->player->x_pos -= 64;
		game->player->moves_n++;
	}
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS && map[j - 1][i] != '1')
	{
		game->player->j_pos--;
		game->player->y_pos -= 64;
		game->player->moves_n++;
	}
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS && map[j + 1][i] != '1')
	{
		game->player->j_pos++;
		game->player->y_pos += 64;
		game->player->moves_n++;
	}
}

void	update(void *ptr)
{
	t_so_long	*game;
	char		**map;
	mlx_image_t	*p_frame;

	game = (t_so_long *)ptr;
	map = game->map->map_array;
	p_frame = get_frame_num(game->player->a, game->player->a->current_frame);
	ft_memset(game->foreground->pixels, 0xFF000000, game->foreground->width * game->foreground->height * sizeof(uint32_t));
	put_img_to_img(game->foreground, p_frame, game->player->y_pos, game->player->x_pos);
	update_animation(game->player->a, game->mlx->delta_time);
}
