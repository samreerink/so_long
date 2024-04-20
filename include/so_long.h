#ifndef SO_LONG_H
# define SO_LONG_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../Libft/libft.h"
# include <stdbool.h>

typedef struct s_game {
	mlx_t		*mlx;
	mlx_image_t	*foreground;
	mlx_image_t	*background;
} t_game;

typedef struct s_animation {
	t_list	*frames;
	int	frame_speed;
	double	accum;
	int	current_frame;
	int	frames_total;
} t_animation;

#endif
