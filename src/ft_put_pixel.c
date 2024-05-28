/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_put_pixel.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/28 16:56:59 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/28 17:02:02 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	px_to_px(mlx_image_t *d, mlx_image_t *s, uint32_t i_dst, uint32_t i_src)
{
	d->pixels[i_dst] = s->pixels[i_src];
	d->pixels[i_dst + 1] = s->pixels[i_src + 1];
	d->pixels[i_dst + 2] = s->pixels[i_src + 2];
	d->pixels[i_dst + 3] = s->pixels[i_src + 3];
}
