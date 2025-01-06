#include "../inc/game.h"

char mapdata[8 * 10] = 
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 1, 1, 0, 1,
	1, 0, 0, 0, 1, 1, 0, 1,
	1, 0, 0, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 1, 1, 1, 1,
	1, 0, 0, 0, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};

void draw_grid(t_game *game, int rows, int cols)
{
	int x, y;

	if (rows <= 0 || cols <= 0)
		return;

	// Drawing horizontal lines
	for (y = 0; y <= rows * 8 * CONST; y += 8 * CONST)
	{
		int x_start = X_START;
		int x_end = X_START + cols * 8 * CONST;
		for (x = x_start; x <= x_end; x++)
			mlx_put_pixel(game->map, x, Y_START + y, 0xFF0000FF);
	}

	// Drawing vertical lines
	for (x = 0; x <= cols * 8 * CONST; x += 8 * CONST)
	{
		int y_start = Y_START;
		int y_end = Y_START + rows * 8 * CONST;
		for (y = y_start; y <= y_end; y++)
			mlx_put_pixel(game->map, X_START + x, y, 0xFF0000FF);
	}
}
