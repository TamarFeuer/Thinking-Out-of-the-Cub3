#include "../inc/game.h"


// t_mmap	get_blocksize(t_game *game)
// {
// 	int block_size;
// 	int height;
// 	int width;
// 	t_mmap map;

// 	map = game->mmap;
// 	block_size = map.height;
// 	if (map.width > map.height)
// 		block_size = map.width;
// 	while (block_size * map.height < MINIMAP_MAX_HEIGHT && block_size * map.width < MINIMAP_MAX_WIDTH)
// 		block_size++;
// 	while (block_size * map.height > MINIMAP_MAX_HEIGHT || block_size * map.width > MINIMAP_MAX_WIDTH)
// 		block_size--;
// 	height = block_size * map.height;
// 	width = block_size * map.width;
// 	return ((t_mmap) {block_size, height, width});
// }


void fill_grid(t_game *game, int cur_row, int cur_col, int type )
{
	int col, row;
	// printf ("cur_row is %d, cur_col is %d\n", cur_row, cur_col);
	if (cur_row < 0 || cur_col < 0)
		return;
	row = cur_row;
	while (row < cur_row + game->mmap.block_size * CONST)
	{
		col = cur_col;
		while (col < cur_col + game->mmap.block_size * CONST)
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

	int temp_width, temp_height;
	if (rows <= 0 || cols <= 0)
		return;

	temp_width = (SCREEN_WIDTH/2) / game->data->map_data.cols; 
	temp_height = (SCREEN_WIDTH/2) / game->data->map_data.rows; 
	if (temp_width > temp_height)
		game->mmap.block_size = temp_height;
	else
		game->mmap.block_size = temp_height;
	printf ("mmap blocksize is %d\n", game->mmap.block_size);
	// Drawing horizontal lines
	y = 0;
	while (y <= rows * game->mmap.block_size * CONST )
	{
		int x_start = X_START;
		int x_end = X_START + cols * game->mmap.block_size * CONST;
		x = x_start;
		while (x < x_end)
		{
			mlx_put_pixel(game->scene, x, Y_START + y, 0x777777FF);  //safe_put_pixel
			
			x++;
		}
		y += game->mmap.block_size * CONST;
	}

	// Drawing vertical lines
	x = 0;
	while(x < (cols + 1) * game->mmap.block_size * CONST )
	{
		int y_start = Y_START;
		int y_end = Y_START + rows * game->mmap.block_size * CONST;
		y = y_start;
		while (y < y_end)
		{
			mlx_put_pixel(game->scene, X_START + x, y, 0x777777FF);  //safe put pixel
			y++;
		}
		x += game->mmap.block_size * CONST;
	}
	
	y = 0;
	
	while (y <= rows - 1)
	{
		//int x_start = X_START;
		//int x_end = X_START + cols * PIXELS_PER_BLOCK * CONST;
		x = 0;
		while (x <= cols - 1)
		{
			if (game->mapdata[y * cols + x] == WALL)
			{
				//printf ("x is %d and y is %d\n",x, y);
				fill_grid (game, y * game->mmap.block_size * CONST, x * game->mmap.block_size * CONST, 1);
			}
			if (game->mapdata[y * cols + x] == SPACE)
			{
				//printf ("x is %d and y is %d\n",x, y);
				fill_grid (game, y * game->mmap.block_size * CONST, x * game->mmap.block_size * CONST, 2);
			}
			x++;
			
		}
		x = 0;
		y++;
	}
}
