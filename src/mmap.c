#include "../inc/game.h"

void	fill_grid(t_game *game, int cur_row, int cur_col, int type)
{
	int	col;
	int	row;

	if (cur_row < 0 || cur_col < 0)
		return ;
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
					put_pixel_mmap(game, col, row, 0xAA604560);
			}
			col++;
		}
		col = cur_col;
		row++;
	}
}

/**
 * @brief Iterates through the map data and fills each cell on the minimap.
 */
static void	fill_mmap_cells(t_game *game, int rows, int cols)
{
	int	x;
	int	y;
	int	map_index;
	int	cell_type;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			map_index = y * cols + x;
			if (map_index >= 0 && map_index < rows * cols)
			{
				cell_type = game->data->map[map_index];
				if (cell_type == WALL || cell_type == SPACE)
				{
					fill_grid(game, y * game->cell_size, \
							x * game->cell_size, cell_type);
				}
			}
			x++;
		}
		y++;
	}
}

/**
 * @brief Draws the horizontal lines for the minimap grid.
 */
static void	draw_horizontal_lines(t_game *game, int rows, int cols)
{
	int	x;
	int	y;
	int	max_x;
	int	max_y;

	max_x = cols * game->cell_size;
	max_y = rows * game->cell_size;
	y = 0;
	while (y <= max_y)
	{
		x = 0;
		while (x < max_x)
		{
			put_pixel_mmap(game, x, y, COLOR_MMAP_GRID);
			x++;
		}
		y += game->cell_size;
	}
}

/**
 * @brief Draws the vertical lines for the minimap grid.
 */
static void	draw_vertical_lines(t_game *game, int rows, int cols)
{
	int	x;
	int	y;
	int	max_x;
	int	max_y;

	max_x = cols * game->cell_size;
	max_y = rows * game->cell_size;
	x = 0;
	while (x <= max_x)
	{
		y = 0;
		while (y < max_y)
		{
			put_pixel_mmap(game, x, y, COLOR_MMAP_GRID);
			y++;
		}
		x += game->cell_size;
	}
}

/**
 * @brief Draws the complete minimap grid, including lines and filled cells.
 * @param game Pointer to the main game structure.
 * @param rows Number of rows in the map data.
 * @param cols Number of columns in the map data.
 */
void	draw_grid(t_game *game, int rows, int cols)
{
	if (rows <= 0 || cols <= 0 || !game || !game->data || !game->data->map \
		|| game->cell_size <= 0)
		return ;
	draw_horizontal_lines(game, rows, cols);
	draw_vertical_lines(game, rows, cols);
	fill_mmap_cells(game, rows, cols);
}
