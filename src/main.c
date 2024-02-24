#include "../include/so_long.h"
#define WIDTH 1080
#define HEIGHT 720

void	error_exit(void)
{
	const char	*msg;

	msg = mlx_strerror(mlx_errno);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

int	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "so_long", true);
	if (!mlx)
		error_exit();
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
