#include "MLX42.h"
#include "../inc/game.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void bresenham_line(t_game *game, int x2, int y2)
{
	int x1 = game->player_pos_x;
	int y1 = game->player_pos_y;
	int x = x1;
	int y = y1;
	int dx = x2 - x1;
	int dy = y2 - y1;
	int p = 2 * dy - dx;
	while (x <= x2)
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
	
	game->player_pos_x = 30;
	game->player_pos_y = 40;
	int x2 = 1000;
	int y2 = 500;
	bresenham_line(game, x2, y2);
	
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);

}
