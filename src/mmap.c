#include "../inc/game.h"


void fill_grid(t_game *game, int cur_row, int cur_col, int type)
{
	int col;
	int row; 

	if (cur_row < 0 || cur_col < 0)
		return;
	row = cur_row;
	while (row < cur_row + game->cell_size)
	{
		col = cur_col;
		while (col < cur_col + game->cell_size)
		{
			{	
				if (type == WALL)
					put_pixel_mmap(game, col, row, 0x2896299);
				else if (type == SPACE)
					put_pixel_mmap(game, col, row, 0x45454560);
			
			}
			col++;
		}
		col = cur_col;
		row++;
	}	
}

void draw_grid(t_game *game, int rows, int cols)
{
	int x, y;

	if (rows <= 0 || cols <= 0)
		return;

	// Drawing horizontal lines
	y = 0;
	while (y <= rows * game->cell_size)
	{
		int x_start = 0;
		int x_end = cols * game->cell_size;
		x = x_start;
		while (x < x_end)
		{
			put_pixel_mmap(game, x, y, 0x777777FF);
			x++;
		}
		y += game->cell_size;
	}

	// Drawing vertical lines
	x = 0;
	while(x < (cols +1) * game->cell_size)
	{
		int y_start = 0;
		int y_end = rows * game->cell_size;
		y = y_start;
		while (y < y_end)
		{
			put_pixel_mmap(game, x, y, 0x777777FF);
			y++;
		}
		x += game->cell_size;
	}
	
	y = 0;
	while (y <= rows -1)
	{
		x = 0;
		while (x <= cols -1)
		{
			if (game->data->map[y * cols + x] == WALL)
			{
				//printf ("x is %d and y is %d\n",x, y);
				fill_grid (game, y * game->cell_size, x * game->cell_size, WALL);
			}
			if (game->data->map[y * cols + x] == SPACE)
			{
				//printf ("x is %d and y is %d\n",x, y);
				fill_grid (game, y * game->cell_size, x * game->cell_size, SPACE);
			}
			x++;
			
		}
		x = 0;
		y++;
	}
}
