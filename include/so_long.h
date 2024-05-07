/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   so_long.h                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/04/21 20:52:34 by sreerink      #+#    #+#                 */
/*   Updated: 2024/05/07 22:21:25 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "./animation.h"
# include "../Libft/libft.h"
# include <stdio.h>
# include <stdbool.h>

#define WIDTH 1080
#define HEIGTH 720

typedef struct s_so_long {
	mlx_t		*mlx;
	mlx_image_t	*background;
	mlx_image_t	*foreground;
	t_animation	*a;
} t_so_long;


// Functions

void		error_exit(void);

t_so_long	*init_game(void);

#endif
