/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   image_utils.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/08 20:48:39 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/19 01:02:17 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
//			printf("Write src %d, %d to dst %d, %d\n", i, j, y, x);
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
