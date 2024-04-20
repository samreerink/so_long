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

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "so_long", false);
	if (!mlx)
		error_exit();

	
	mlx_image_t 	*img_game;
	mlx_texture_t 	*tex_player;
	
	
	img_game = mlx_new_image(mlx, WIDTH, HEIGHT);
	tex_player = mlx_load_png("./assets/fox.png");
	mlx_image_to_window(mlx, img_game, 0, 0);


	//int n_animations = tex_player->height / 128;
	//int n_frames = tex_player->width / 128;
		int current_animation = 0;
		int current_frame = 1;

		uint32_t	y = current_animation * 32;
		uint32_t	x = current_frame * 32;
		uint32_t 	y_end = y + 32;
		uint32_t	x_end = x + 32;
		while (y < y_end)
		{
			x = current_frame * 32;
			while (x < x_end)
			{
				int index = (y * tex_player->width + x) * 4;

				unsigned char r = tex_player->pixels[index]; 
				unsigned char g = tex_player->pixels[index + 1];
				unsigned char b = tex_player->pixels[index + 2];
				unsigned char a = tex_player->pixels[index + 3];

				mlx_put_pixel(img_game, x, y, get_rgba(r, g, b, a));
				x++;
			}
			y++;
		}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
