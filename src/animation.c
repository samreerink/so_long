/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   animation.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 21:09:47 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/07 21:09:56 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_sprite_sheet	*load_sprite_sheet(const char *file_path, int slice_h, int slice_w, mlx_t *mlx)
{
	t_sprite_sheet	*s;
	mlx_texture_t	*texture;

	s = malloc(sizeof(t_sprite_sheet));
	if (!s)
		error_exit();
	texture = mlx_load_png(file_path);
	if (!texture)
		error_exit();
	s->img = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
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
	uint32_t	old_cur_x;

	y = 0;
	old_cur_x = s->cur_x;
	while (y < s->slice_height)
	{
		x = 0;
		s->cur_x = old_cur_x;
		while (x < s->slice_width)
		{
			printf("y = %d cur_y = %d, x = %d cur_x = %d\n", y, s->cur_y, x, s->cur_x);
			index_src = (s->cur_y * s->img->width + s->cur_x) * 4;
			index_dst = (y * s->slice_width + x) * 4;
			img->pixels[index_dst] = s->img->pixels[index_src];
			img->pixels[index_dst + 1] = s->img->pixels[index_src + 1];
			img->pixels[index_dst + 2] = s->img->pixels[index_src + 2];
			img->pixels[index_dst + 3] = s->img->pixels[index_src + 3];
			s->cur_x++;
			x++;
		}
		s->cur_y++;
		y++;
	}
	printf("----------------------------------------------\n");
}

void	add_frame(t_animation *a, t_sprite_sheet *s, mlx_t *mlx)
{
	t_frame	*new_frame;
	t_frame	*temp;

	new_frame = malloc(sizeof(t_frame));
	if (!new_frame)
		error_exit();
	new_frame->img = mlx_new_image(mlx, s->slice_width, s->slice_height);
	if (!new_frame->img)
		error_exit();
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

t_animation	*init_animation(t_sprite_sheet *s, int n_frames, int row, mlx_t *mlx)
{
	t_animation	*a;

	a = malloc(sizeof(t_animation));
	if (!a)
		error_exit();
	a->frame = NULL;
	a->current_frame = 0;
	a->n_frames = n_frames;
	while (n_frames > 0)
	{
		s->cur_y = row * s->slice_height;
		add_frame(a, s, mlx);
		n_frames--;
	}
	return (a);
}