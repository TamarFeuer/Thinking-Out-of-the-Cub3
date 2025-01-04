#include "MLX42.h"
#include "../inc/game.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void bresenham_line(t_game *game, t_pos vertex1, t_pos vertex2)
{
	int x = vertex1.x;
	int y = vertex1.y;
	int dx = vertex2.x - vertex1.x;
	int dy = vertex2.y - vertex1.y;
	int p = 2 * dy - dx;
	while (x <= vertex2.x)
	{
		mlx_put_pixel(game->img, x, y, 0xFF0000FF);
		x++;
		if (p < 0)
			p += 2 * dy;
		else
		{
			p = p + 2 * dy - 2 * dx;
			y++;
		}
	}
}

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_game *game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	game->mlx = mlx_init(1024, 512, "Ray tracing", true);
	if (!game->mlx)
		return (EXIT_FAILURE);
	game->img = mlx_new_image(game->mlx, 1024, 512);
	if (!game->img || (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0))
		return (EXIT_FAILURE);
	
	t_pos vertex1;
	t_pos vertex2;
	vertex1.x = 30;
	vertex1.y = 40;
	vertex2.x = 1000;
	vertex2.y = 500;
	bresenham_line(game, vertex1, vertex2);
	
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);

}
