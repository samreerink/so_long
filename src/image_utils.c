/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   image_utils.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/08 20:48:39 by sreerink      #+#    #+#                 */
/*   Updated: 2024/06/01 20:42:29 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

mlx_image_t	*load_png_to_image(char *path_png, t_so_long *game)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(path_png);
	if (!texture)
		error_exit(NULL, NULL, game);
	img = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	return (img);
}

void	clear_image(mlx_image_t *img)
{
	uint32_t	h;
	uint32_t	w;

	h = img->height;
	w = img->width;
	ft_memset(img->pixels, 0xFF000000, w * h * sizeof(uint32_t));
}

void	put_img(mlx_image_t *dst, mlx_image_t *src, uint32_t y, uint32_t x)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	old_x;
	uint32_t	index_src;
	uint32_t	index_dst;

	i = 0;
	old_x = x;
	while (i < src->height)
	{
		j = 0;
		x = old_x;
		while (j < src->width)
		{
			index_dst = (y * dst->width + x) * 4;
			index_src = (i * src->width + j) * 4;
			px_to_px(dst, src, index_dst, index_src);
			j++;
			x++;
		}
		i++;
		y++;
	}
}
