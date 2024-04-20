/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/04/20 14:02:20 by sreerink      #+#    #+#                 */
/*   Updated: 2024/04/20 22:14:52 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

#define WIDTH 640
#define HEIGHT 360

void	error_exit(t_game *so_long)
{
	const char	*msg;

	if (mlx_errno)
	{
		msg = mlx_strerror(mlx_errno);
		write(STDERR_FILENO, msg, ft_strlen(msg));
	}
	if (so_long)
	{
		mlx_terminate(so_long->mlx);
		free(so_long);
	}
	exit(EXIT_FAILURE);
}

t_game	*init_game(void)
{
	t_game		*so_long;
	mlx_texture_t	*texture_bg;

	so_long = ft_calloc(1, sizeof(t_game));
	if (!so_long)
		error_exit(NULL);
	so_long->mlx = mlx_init(WIDTH, HEIGHT, "so_long", false);
	if (!so_long->mlx)
		error_exit(so_long);
	texture_bg = mlx_load_png("./assets/color_bg.png");
	if (!texture_bg)
		error_exit(so_long);
	//so_long->background = mlx_texture_to_image(so_long->mlx, texture_bg);
	so_long->background = mlx_new_image(so_long->mlx, WIDTH, HEIGHT);
	mlx_delete_texture(texture_bg);
	if (!so_long->background)
		error_exit(so_long);
	if (mlx_image_to_window(so_long->mlx, so_long->background, 0, 0) < 0)
		error_exit(so_long);
	so_long->foreground = mlx_new_image(so_long->mlx, WIDTH, HEIGHT);
	if (!so_long->foreground)
		error_exit(so_long);
	if (mlx_image_to_window(so_long->mlx, so_long->foreground, 0, 0) < 0)
		error_exit(so_long);
	return (so_long);
}

int	get_pixel_color(mlx_image_t *s, int x, int y)
{
	int		index;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;

	index = (x + y * s->width) * 4;
	r = s->pixels[index];
	g = s->pixels[index + 1];
	b = s->pixels[index + 2];
	a = s->pixels[index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

void	add_frame(t_game *so_long, t_animation *a, mlx_image_t *s)
{
	mlx_image_t	*frame;
	int		x;
	int		y;
	int		w;
	int		h;
	int		i;
	int		p_color;

	i = 0;
	x = 0;
	y = 0;
	w = 32;
	h = 32;
	frame = mlx_new_image(so_long->mlx, w, h);
	if (!frame)
		error_exit(so_long);
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			p_color = get_pixel_color(s, x, y);
			so_long->foreground->pixels[i] = (unsigned char)0X00FFFFFF;
			i++;
			x++;
		}
		y++;
	}
	ft_lstadd_back(&a->frames, ft_lstnew(frame));
}

void	put_img_to_img(mlx_image_t *dst, mlx_image_t *src, uint32_t x, uint32_t y)
{
	int	i;
	int	p_color;

	while (y < src->height)
	{
		while (x < src->width)
		{
			i = (x + y * dst->width) * 4;
			p_color = get_pixel_color(src, x, y);
			dst->pixels[i] = p_color;
			i++;
			x++;
		}
		y++;
	}
}

t_animation	*animation_test(t_game **so_long)
{
	t_animation	*a;
	mlx_texture_t	*sprite_sheet;
	mlx_image_t	*s;

	a = ft_calloc(1, sizeof(t_animation));
	if (!a)
		error_exit(*so_long);
	sprite_sheet = mlx_load_png("./assets/fox.png");
	if (!sprite_sheet)
		error_exit(*so_long);
	s = mlx_texture_to_image((*so_long)->mlx, sprite_sheet);
	mlx_delete_texture(sprite_sheet);
	if (!s)
		error_exit(*so_long);
	add_frame(*so_long, a, s);
	return (a);
}

int	main(void)
{
	t_game		*so_long;
	t_animation	*fox;

	so_long = init_game();
	fox = animation_test(&so_long);
	put_img_to_img(so_long->foreground, (mlx_image_t *)fox->frames, 0, 0);
	mlx_loop(so_long->mlx);
	mlx_terminate(so_long->mlx);
	free(so_long);
	return (EXIT_SUCCESS);
}
