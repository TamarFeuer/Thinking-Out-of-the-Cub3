#include "../inc/game.h"


void fill_grid(t_game *game, int cur_row, int cur_col, int type )
{
	int col, row;
	// printf ("cur_row is %d, cur_col is %d\n", cur_row, cur_col);
	if (cur_row < 0 || cur_col < 0)
		return;
	
	row = cur_row;
	while (row < cur_row + game->cell_size)
	{
		col = cur_col;
		while (col < cur_col + game->cell_size)
		{
			{	
				// printf ("col is %d, row is %d\n", col, row);
				if (type == 1)
					mlx_put_pixel(game->scene, col, row, 0x00F77650);
				else if (type == 2)
					mlx_put_pixel(game->scene, col, row, 0x45454560);
			
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
		int x_start = X_START;
		int x_end = X_START + cols * game->cell_size;
		x = x_start;
		while (x < x_end)
		{
			mlx_put_pixel(game->scene, x, Y_START + y, 0x777777FF);  //safe_put_pixel
			x++;
		}
		y += game->cell_size;
	}

	// Drawing vertical lines
	x = 0;
	while(x < (cols +1) * game->cell_size)
	{
		int y_start = Y_START;
		int y_end = Y_START + rows * game->cell_size;
		y = y_start;
		while (y < y_end)
		{
			mlx_put_pixel(game->scene, X_START + x, y, 0x777777FF);  //safe put pixel
			y++;
		}
		x += game->cell_size;
	}
	
	y = 0;
	while (y <= rows -1)
	{
		//int x_start = X_START;
		//int x_end = X_START + cols * PIXELS_PER_BLOCK * CONST;
		x = 0;
		while (x <= cols -1)
		{
			if (game->data->map[y * cols + x] == WALL)
			{
				//printf ("x is %d and y is %d\n",x, y);
				fill_grid (game, y * game->cell_size, x * game->cell_size, 1);
			}
			if (game->data->map[y * cols + x] == SPACE)
			{
				//printf ("x is %d and y is %d\n",x, y);
				fill_grid (game, y * game->cell_size, x * game->cell_size, 2);
			}
			x++;
			
		}
		x = 0;
		y++;
	}
}
