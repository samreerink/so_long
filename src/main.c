/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/04/21 20:39:35 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/03 22:10:24 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#define WIDTH 1080
#define HEIGTH 720

void	error_exit(void)
{
	const char	*msg;

	if (mlx_errno)
	{
		msg = mlx_strerror(mlx_errno);
		write(STDERR_FILENO, msg, ft_strlen(msg));
	}
	exit(EXIT_FAILURE);
}

t_sprite_sheet	*load_sprite_sheet(const char *file_path, int slice_h, int slice_w)
{
	t_sprite_sheet	*s;

	s = malloc(sizeof(t_sprite_sheet));
	if (!s)
		error_exit();
	s->t = mlx_load_png(file_path);
	if (!s->t)
		error_exit();
	s->cur_y = 0;
	s->cur_x = 0;
	s->slice_height = slice_h;
	s->slice_width = slice_w;
	return (s);
}

void	sprite_to_frame(mlx_image_t *img, t_sprite_sheet *s)
{
	uint32_t	index_src;
	uint32_t	index_dst;
	uint32_t	y;
	uint32_t	x;
	uint32_t	end_y;
	uint32_t	end_x;

	y = 0;
	end_y = s->cur_y + s->slice_height;
	end_x = s->cur_x + s->slice_width;
	while (s->cur_y < end_y)
	{
		x = 0;
		s->cur_x = 0;
		while (s->cur_x < end_x)
		{
			index_src = (s->cur_y * s->t->width + s->cur_x) * 4;
			index_dst = (y * s->slice_width + x) * 4;
			img->pixels[index_dst] = s->t->pixels[index_src];
			img->pixels[index_dst + 1] = s->t->pixels[index_src + 1];
			img->pixels[index_dst + 2] = s->t->pixels[index_src + 2];
			img->pixels[index_dst + 3] = s->t->pixels[index_src + 3];
			s->cur_x++;
			x++;
		}
		s->cur_y++;
		y++;
	}
}

void	init_frames(t_animation *a, t_sprite_sheet *s, int n, mlx_t *mlx)
{
	t_frame	*new_frame;
	t_frame	*temp;

	a->frame = NULL;
	while (n > 0)
	{
		new_frame = malloc(sizeof(t_frame));
		// check
		new_frame->img = mlx_new_image(mlx, s->slice_width, s->slice_height);
		// check
		sprite_to_frame(new_frame->img, s);
	}
}

t_animation	*init_animation(t_sprite_sheet *s, int n_frames, mlx_t *mlx)
{
	t_animation	*a;

	a = malloc(sizeof(t_animation));
	if (!a)
		error_exit();
	a->current_frame = 0;
	a->n_frames = n_frames;
	init_frames(a, s, n_frames, mlx);
	return (a);
}

int	main(void)
{
	mlx_t		*mlx;
//	mlx_image_t	*background;
	mlx_image_t	*foreground;
	t_animation	*fox_1;
	t_sprite_sheet	*sprite_sheet;

	mlx = mlx_init(WIDTH, HEIGTH, "so_long", false);
	if (!mlx)
		error_exit();
	foreground = mlx_new_image(mlx, WIDTH, HEIGTH);
	if (!foreground)
		error_exit();
/*	if (mlx_image_to_window(mlx, foreground, 0, 0) < 0)
		error_exit(); */
	sprite_sheet = load_sprite_sheet("./assets/fox.png", 32, 32);
	fox_1 = init_animation(sprite_sheet, 5, mlx);
	mlx_delete_texture(sprite_sheet->t);
	if (mlx_image_to_window(mlx, fox_1->frame->img, 0, 0) < 0)
		error_exit();
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
