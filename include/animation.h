/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   animation.h                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 19:56:21 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/07 21:15:57 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../Libft/libft.h"

typedef struct s_sprite_sheet {
	mlx_image_t	*img;
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


// Functions

t_sprite_sheet	*load_sprite_sheet(const char *file_path, int slice_h, int slice_w, mlx_t *mlx);

void		sprite_to_frame(mlx_image_t *img, t_sprite_sheet *s);

void		add_frame(t_animation *a, t_sprite_sheet *s, mlx_t *mlx);

t_animation	*init_animation(t_sprite_sheet *s, int n_frames, int row, mlx_t *mlx);

#endif
