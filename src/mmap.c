#include "../inc/game.h"

void	fill_grid(t_game *game, int cur_row, int cur_col, int type )
{
	int	row;
	int	col;

	if (cur_row < 0 || cur_col < 0)
		return;
	row = cur_row;
	while (row < cur_row + game->cell_size)
	{
		col = cur_col;
		while (col < cur_col + game->cell_size)
		{
			{
				if (type == 1)
					mlx_put_pixel(game->mini, col, row, 0x2896299);
				else if (type == 2)
					safe_put_pixel(game, col, row, 0x45454560);
			}
			col++;
		}
		col = cur_col;
		row++;
	}
}

void	draw_grid(t_game *game, int rows, int cols)
{
	int	x;
	int	y;
	int	x_start;
	int	x_end;
	int	y_start;
	int	y_end;

	if (rows <= 0 || cols <= 0)
		return ;
	y = 0;
	while (y <= rows * game->cell_size)
	{
		x_start = 0;
		x_end = cols * game->cell_size;
		x = x_start;
		while (x < x_end)
		{
			safe_put_pixel(game, x, y, 0x777777FF);
			x++;
		}
		y += game->cell_size;
	}
	x = 0;
	while (x < (cols + 1) * game->cell_size)
	{
		y_start = 0;
		y_end = rows * game->cell_size;
		y = y_start;
		while (y < y_end)
		{
			safe_put_pixel(game, x, y, 0x777777FF);
			y++;
		}
		x += game->cell_size;
	}
	y = 0;
	while (y <= rows - 1)
	{
		x = 0;
		while (x <= cols - 1)
		{
			if (game->data->map[y * cols + x] == WALL)
				fill_grid (game, y * game->cell_size, x * game->cell_size, 1);
			if (game->data->map[y * cols + x] == SPACE)
				fill_grid (game, y * game->cell_size, x * game->cell_size, 2);
			x++;
		}
		x = 0;
		y++;
	}
}
