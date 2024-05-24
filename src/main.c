/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/04/21 20:39:35 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/24 22:27:43 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	load_background_assets(t_so_long *game)
{
	game->tiles->wall_l = load_png_to_image("./assets/tile009.png", game);
	game->tiles->wall_m = load_png_to_image("./assets/tile034.png", game);
	game->tiles->wall_top_l = load_png_to_image("./assets/tile025.png", game);
	game->tiles->wall_top_m = load_png_to_image("./assets/tile026.png", game);
	game->tiles->wall_top_r = load_png_to_image("./assets/tile027.png", game);
	game->tiles->wall_low_l = load_png_to_image("./assets/tile017_wood.png", game);
	game->tiles->wall_low_r = load_png_to_image("./assets/tile019_wood.png", game);
	game->tiles->wall_bottom_l = load_png_to_image("./assets/tile033.png", game);
	game->tiles->wall_bottom_r = load_png_to_image("./assets/tile035.png", game);
	game->tiles->floor = load_png_to_image("./assets/wooden.png", game);
	game->tiles->object = load_png_to_image("./assets/tile002.png", game);
	game->exit->closed = load_png_to_image("./assets/wooden_door_closed.png", game);
	game->exit->open = load_png_to_image("./assets/wooden_door_open.png", game);
}

void	draw_top_bg(char **map, t_so_long *game)
{
	size_t		i;
	uint32_t	x;

	i = 1;
	x = 72;
	while (map[0][i + 1] && map[0][i + 1] != '\n')
	{
		put_img_to_img(game->background, game->tiles->wall_top_m, 0, x);
		x += 64;
		i++;
	}
	put_img_to_img(game->background, game->tiles->wall_top_l, 0, 36);
	put_img_to_img(game->background, game->tiles->wall_top_r, 0, x - 28);
}

void	draw_first_row(char **map, t_so_long *game)
{
	size_t		i;
	uint32_t	x;

	i = 1;
	x = 72;
	while (map[0][i + 1] && map[0][i + 1] != '\n')
	{
		put_img_to_img(game->background, game->tiles->wall_m, 28, x);
		x += 64;
		i++;
	}
	put_img_to_img(game->background, game->tiles->wall_l, 28, 36);
	put_img_to_img(game->background, game->tiles->wall_l, 28, x);
}

void	draw_between_rows(char	**map, t_so_long *game)
{
	size_t		i;
	size_t		j;
	uint32_t	y;
	uint32_t	x;

	j = 1;
	y = 92;
	while (map[j + 1])
	{
		i = 1;
		x = 72;
		while (map[j][i + 1] && map[j][i + 1] != '\n')
		{
			put_img_to_img(game->background, game->tiles->floor, y, x);
			if (map[j][i] == '1')
				put_img_to_img(game->background, game->tiles->object, y, x);
			else if (map[j][i] == 'P')
			{
				game->player->j_pos = j;
				game->player->i_pos = i;
				game->player->y_pos = j * 64;
				game->player->x_pos = i * 64 - 64;
			}
			else if (map[j][i] == 'E')
			{
				game->exit->j_pos = j;
				game->exit->i_pos = i;
				game->exit->y_pos = y;
				game->exit->x_pos = x;
				put_img_to_img(game->background, game->exit->closed, y, x);
			}
			x += 64;
			i++;
		}
		put_img_to_img(game->background, game->tiles->wall_l, y, 36);
		put_img_to_img(game->background, game->tiles->wall_l, y, x);
		y += 64;
		j++;
	}
}

void	draw_last_row(char **map, t_so_long *game)
{
	size_t		i;
	uint32_t	y;
	uint32_t	x;

	i = 1;
	x = 72;
	y = (game->map->rows - 1) * 64 + 22;
	while (map[0][i + 1] && map[0][i + 1] != '\n')
	{
		put_img_to_img(game->background, game->tiles->wall_top_m, y, x);
		x += 64;
		i++;
	}
	put_img_to_img(game->background, game->tiles->wall_low_l, y - 36, 36);
	put_img_to_img(game->background, game->tiles->wall_low_r, y - 36, x - 28);
}

void	draw_bottom_bg(char **map, t_so_long *game)
{
	size_t		i;
	uint32_t	y;
	uint32_t	x;

	i = 1;
	x = 72;
	y = (game->map->rows - 1) * 64 + 50;
	while (map[0][i + 1] && map[0][i + 1] != '\n')
	{
		put_img_to_img(game->background, game->tiles->wall_m, y, x);
		x += 64;
		i++;
	}
	put_img_to_img(game->background, game->tiles->wall_bottom_l, y, 36);
	put_img_to_img(game->background, game->tiles->wall_bottom_r, y, x - 28);
}

void	draw_background(t_so_long *game)
{
	char	**map;

	map = game->map->map_array;
	draw_top_bg(map, game);
	draw_first_row(map, game);
	draw_between_rows(map, game);
	draw_last_row(map, game);
	draw_bottom_bg(map, game);
}

void	draw_chest(t_so_long *game)
{
	char		**map;
	size_t		j;
	size_t		i;
	uint32_t	y;
	uint32_t	x;

	j = 1;
	y = 92;
	map = game->map->map_array;
	while (map[j + 1])
	{
		i = 1;
		x = 72;
		while (map[j][i + 1] && map[j][i + 1] != '\n')
		{
			if (map[j][i] == 'C')
				put_img_to_img(game->background, game->chest->a->frame->img, y, x);
			x += 64;
			i++;
		}
		y += 64;
		j++;
	}
}

int	main(int argc, char *argv[])
{
	t_so_long	*game;
	t_sprite_sheet	*sprite_sheet;

	if (argc != 2)
		error_exit("Invalid amount of arguments\n", NULL);
	game = init_game(argv[1]);
	check_map(game);
	load_background_assets(game);
	draw_background(game);
	sprite_sheet = load_sprite_sheet("./assets/player_02.png", 92, 192, game->mlx);
	game->player->a = init_animation(sprite_sheet, 6, 0, 120, game->mlx);
	sprite_sheet = load_sprite_sheet("./assets/chest_01.png", 64, 64, game->mlx);
	game->chest->a = init_animation(sprite_sheet, 4, 0, 1, game->mlx);
	draw_chest(game);
	sprite_sheet = load_sprite_sheet("./assets/Effect.png", 192, 192, game->mlx);
	game->effect = init_animation(sprite_sheet, 10, 0, 120, game->mlx);
	sprite_sheet = load_sprite_sheet("./assets/chest_02.png", 64, 64, game->mlx);
	game->gold_chest = init_animation(sprite_sheet, 4, 0, 120, game->mlx);
	mlx_loop_hook(game->mlx, update, game);
	mlx_key_hook(game->mlx, key_update, game);
//	mlx_close_hook(game->mlx, exit_game, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
