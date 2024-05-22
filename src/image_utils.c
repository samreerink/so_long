/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   image_utils.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/08 20:48:39 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/22 05:15:38 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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

void	put_img_to_img(mlx_image_t *dst, mlx_image_t *src, uint32_t y, uint32_t x)
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
			dst->pixels[index_dst] = src->pixels[index_src];
			dst->pixels[index_dst + 1] = src->pixels[index_src + 1];
			dst->pixels[index_dst + 2] = src->pixels[index_src + 2];
			dst->pixels[index_dst + 3] = src->pixels[index_src + 3];
			j++;
			x++;
		}
		i++;
		y++;
	}
}
