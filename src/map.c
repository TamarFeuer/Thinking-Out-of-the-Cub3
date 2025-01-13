#include "../inc/game.h"

void init_map(t_game *game)
{
    game->mapdata = malloc(ROWS * COLS * sizeof(char));
    if (!game->mapdata)
    {
        exit(EXIT_FAILURE);
    }
 
    int initial_map[ROWS][COLS] = 
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    
    int i = 0;
    while (i < ROWS)
    {
        int j = 0;
        while (j < COLS)
        {
            game->mapdata[i * COLS + j] = initial_map[i][j];
            j++;
        }
        i++;
    }
}

void fill_grid(t_game *game, int rows, int cols)
{
	int col, row;
	mlx_texture_t	*texture;
	
	texture = mlx_load_png("textures/helipad48.png");
	if (!texture)
		printf ("error loading texture\n");
	game->fill = mlx_texture_to_image(game->mlx, texture);
	if (!game->fill)
		printf ("error converting texture to image\n");
	mlx_delete_texture(texture);
	printf ("rows = %d, cols = %d\n", rows, cols);
	if (rows <= 0 || cols <= 0)
		return;
	row = 0;
	while (row < rows)
	{
		col = 0;
		while (col < cols)
		{
			if (game->mapdata[row * cols + col] == WALL)
			{	
				mlx_image_to_window(game->mlx, game->fill, 
					X_START + col * PIXELS_PER_BLOCK * CONST,
					Y_START + row * PIXELS_PER_BLOCK * CONST);
			}
			col++;
		}
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
	while (y <= (rows - 1)* PIXELS_PER_BLOCK * CONST)
	{
		int x_start = X_START;
		int x_end = X_START + cols * PIXELS_PER_BLOCK * CONST;
		x = x_start;
		while (x <= x_end)
		{
			mlx_put_pixel(game->screen, x, Y_START + y, 0x777777FF);
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
			mlx_put_pixel(game->screen, X_START + x, y, 0x777777FF);
			y++;
		}
		x += PIXELS_PER_BLOCK * CONST;
	}
	fill_grid(game, rows, cols);
}
