/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/04/21 20:39:35 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/20 22:42:27 by sreerink      ########   odam.nl         */
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

mlx_image_t	*load_png_to_image(char *path_png, t_so_long *game)
{
	mlx_texture_t	*texture;
	mlx_image_t	*img;

	texture = mlx_load_png(path_png);
	if (!texture)
		error_exit(NULL, NULL);
	img = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	return (img);
}

void	load_background_assets(t_so_long *game)
{
	game->tiles->wall_l = load_png_to_image("./assets/tile009.png", game);
	game->tiles->wall_m = load_png_to_image("./assets/tile034.png", game);
	game->tiles->wall_top_l = load_png_to_image("./assets/tile025.png", game);
	game->tiles->wall_top_m = load_png_to_image("./assets/tile026.png", game);
	game->tiles->wall_top_r = load_png_to_image("./assets/tile027.png", game);
	game->tiles->floor = load_png_to_image("./assets/wooden.png", game);
}

void	draw_top_bg(char **map, t_so_long *game)
{
	size_t		i;
	uint32_t	x;

	i = 1;
	x = 64;
	put_img_to_img(game->background, game->tiles->wall_top_l, 0, 0);
	while (map[0][i + 1] && map[0][i + 1] != '\n')
	{
		put_img_to_img(game->background, game->tiles->wall_top_m, 0, x);
		x += 64;
		i++;
	}
	put_img_to_img(game->background, game->tiles->wall_top_r, 0, x);
}

void	draw_first_row(char **map, t_so_long *game)
{
	size_t		i;
	uint32_t	x;

	i = 0;
	x = 0;
	while (map[0][i] && map[0][i] != '\n')
	{
		put_img_to_img(game->background, game->tiles->wall_m, 28, x);
		x += 64;
		i++;
	}
	put_img_to_img(game->background, game->tiles->wall_l, 28, 0);
	put_img_to_img(game->background, game->tiles->wall_l, 28, x - 36);
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
		i = 0;
		x = 0;
		while (map[j][i] && map[j][i] != '\n')
		{
			put_img_to_img(game->background, game->tiles->floor, y, x);
			x += 64;
			i++;
		}
		put_img_to_img(game->background, game->tiles->wall_l, y, 0);
		put_img_to_img(game->background, game->tiles->wall_l, y, x - 36);
		y += 64;
		j++;
	}
}

void	draw_background(t_so_long *game)
{
	char		**map;

	map = game->map->map_array;
	draw_top_bg(map, game);
	draw_first_row(map, game);
	draw_between_rows(map, game);
}

int	main(int argc, char *argv[])
{
	t_so_long	*game;
	t_sprite_sheet	*sprite_sheet;

	if (argc != 2)
		error_exit("Invalid amount of arguments\n", NULL);
	game = init_game(argv[1]);
	load_background_assets(game);
	draw_background(game);
	sprite_sheet = load_sprite_sheet("./assets/player_02.png", 92, 192, game->mlx);
	game->player->a = init_animation(sprite_sheet, 6, 0, 120, game->mlx);
	game->player->y_pos = 64;
	game->player->x_pos = 704;
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
