/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   animation.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 21:09:47 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/31 22:55:08 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_sprite	*load_sprite_sheet(const char *file, int h, int w, mlx_t *mlx)
{
	t_sprite	*s;
	mlx_texture_t	*texture;

	s = malloc(sizeof(t_sprite));
	if (!s)
		error_exit(NULL, "malloc");
	texture = mlx_load_png(file);
	if (!texture)
		error_exit(NULL, NULL);
	s->mlx = mlx;
	s->img = mlx_texture_to_image(s->mlx, texture);
	mlx_delete_texture(texture);
	s->cur_y = 0;
	s->cur_x = 0;
	s->slice_height = h;
	s->slice_width = w;
	return (s);
}

void	sprite_to_frame(mlx_image_t *img, t_sprite *s)
{
	uint32_t	index_src;
	uint32_t	index_dst;
	uint32_t	y;
	uint32_t	x;
	uint32_t	old_cur_x;

	y = 0;
	old_cur_x = s->cur_x;
	while (y < s->slice_height)
	{
		x = 0;
		s->cur_x = old_cur_x;
		while (x < s->slice_width)
		{
			index_src = (s->cur_y * s->img->width + s->cur_x) * 4;
			index_dst = (y * s->slice_width + x) * 4;
			px_to_px(img, s->img, index_dst, index_src);
			s->cur_x++;
			x++;
		}
		s->cur_y++;
		y++;
	}
}

void	add_frame(t_animation *a, t_sprite *s)
{
	t_frame	*new_frame;
	t_frame	*temp;

	new_frame = malloc(sizeof(t_frame));
	if (!new_frame)
		error_exit(NULL, "malloc");
	new_frame->img = mlx_new_image(s->mlx, s->slice_width, s->slice_height);
	if (!new_frame->img)
		error_exit(NULL, "malloc");
	sprite_to_frame(new_frame->img, s);
	new_frame->next = NULL;
	if (!a->frame)
		a->frame = new_frame;
	else
	{
		temp = a->frame;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_frame;
	}
}

void	update_animation(t_animation *a, double dt)
{
	a->accum += dt * 1000;
	if (a->accum > a->frame_speed)
	{
		a->accum -= a->frame_speed;
		a->current_frame++;
		a->current_frame %= a->n_frames;
	}
}

t_animation	*init_animation(t_sprite *s, int n_frames, int row, int f_speed)
{
	t_animation	*a;

	a = malloc(sizeof(t_animation));
	if (!a)
		error_exit(NULL, "malloc");
	a->frame = NULL;
	a->frame_speed = f_speed;
	a->accum = 0;
	a->current_frame = 0;
	a->n_frames = n_frames;
	while (n_frames > 0)
	{
		s->cur_y = row * s->slice_height;
		add_frame(a, s);
		n_frames--;
	}
	return (a);
}
