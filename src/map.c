#include "../inc/game.h"



// void fill_grid(t_game *game, int rows, int cols)
// {
// 	int col, row;
// 	mlx_texture_t	*texture;
	
// 	texture = mlx_load_png("textures/helipad32.png");
// 	if (!texture)
// 		printf ("error loading texture\n");
// 	game->fill = mlx_texture_to_image(game->mlx, texture);
// 	if (!game->fill)
// 		printf ("error converting texture to image\n");
// 	mlx_delete_texture(texture);
// 	//printf ("rows = %d, cols = %d\n", rows, cols);
// 	if (rows <= 0 || cols <= 0)
// 		return;
// 	row = 0;
// 	while (row < rows)
// 	{
// 		col = 0;
// 		while (col < cols)
// 		{
// 			if (game->mapdata[row * cols + col] == WALL)
// 			{	
// 				mlx_image_to_window(game->mlx, game->fill, 
// 					X_START + col * PIXELS_PER_BLOCK * CONST,
// 					Y_START + row * PIXELS_PER_BLOCK * CONST);
// 			}
// 			col++;
// 		}
// 		row++;
// 	}	
// }

void fill_grid(t_game *game, int cur_row, int cur_col)
{
	int col, row;
	// printf ("cur_row is %d, cur_col is %d\n", cur_row, cur_col);
	if (cur_row < 0 || cur_col < 0)
		return;
	
	row = cur_row;
	while (row < cur_row + PIXELS_PER_BLOCK * CONST)
	{
		col = cur_col;
		while (col < cur_col + PIXELS_PER_BLOCK * CONST)
		{
			{	
				// printf ("col is %d, row is %d\n", col, row);
				mlx_put_pixel(game->scene, col, row, 0x777777FF);
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
	while (y <= (rows - 1) * PIXELS_PER_BLOCK * CONST)
	{
		int x_start = X_START;
		int x_end = X_START + cols * PIXELS_PER_BLOCK * CONST;
		x = x_start;
		while (x <= x_end)
		{
			mlx_put_pixel(game->scene, x, Y_START + y, 0x777777FF);  //safe_put_pixel
			x++;
		}
		y += PIXELS_PER_BLOCK * CONST;
	}

	// Drawing vertical lines
	x = 0;
	while(x <= (cols - 1) * PIXELS_PER_BLOCK * CONST)
	{
		int y_start = Y_START;
		int y_end = Y_START + rows * PIXELS_PER_BLOCK * CONST;
		y = y_start;
		while (y <= y_end)
		{
			mlx_put_pixel(game->scene, X_START + x, y, 0x777777FF);  //safe put pixel
			y++;
		}
		x += PIXELS_PER_BLOCK * CONST;
	}
	
	y = 0;
	while (y <= rows -1)
	{
		//int x_start = X_START;
		//int x_end = X_START + cols * PIXELS_PER_BLOCK * CONST;
		x = 0;
		while (x <= cols -1)
		{
			if (game->mapdata[y * cols + x] == WALL)
			{
				//printf ("x is %d and y is %d\n",x, y);
				fill_grid (game, y * PIXELS_PER_BLOCK * CONST, x * PIXELS_PER_BLOCK * CONST);
			}
			x++;
			
		}
		x = 0;
		y++;
	}
}
