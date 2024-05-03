/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   so_long.h                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/04/21 20:52:34 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/03 18:12:40 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../Libft/libft.h"
# include <stdio.h>
# include <stdbool.h>

typedef struct s_sprite_sheet {
	mlx_texture_t	*t;
	uint32_t	slice_height;
	uint32_t	slice_width;
	uint32_t	cur_y;
	uint32_t	cur_x;
} t_sprite_sheet;

typedef struct s_frame {
	mlx_image_t	*img;
	struct s_frame	*next;
} t_frame;

typedef struct s_animation {
	struct s_frame	*frame;
	int		current_frame;
	int		n_frames;
} t_animation;

#endif