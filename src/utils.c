#include "../inc/game.h"

void	determine_quad(double angle, int *quad)
{
	double	sin_a;
	double	cos_a;

	sin_a = sin(angle);
	cos_a = cos(angle);
	if (cos_a > 0 && sin_a > 0)
		*quad = 1;
	else if (cos_a < 0 && sin_a > 0)
		*quad = 2;
	else if (cos_a < 0 && sin_a < 0)
		*quad = 3;
	else if (cos_a > 0 && sin_a < 0)
		*quad = 4;
	else if (cos_a == 1 && sin_a == 0)
		*quad = 1;
	else if (cos_a == 0 && sin_a == 1)
		*quad = 2;
	else if (cos_a == -1 && sin_a == 0)
		*quad = 3;
	else if (cos_a == 0 && sin_a == -1)
		*quad = 4;
}

/**
 * @brief Safely puts a pixel onto the main scene image, checking boundaries.
 * @details Checks if the provided pixel coordinates (x, y) are within the
 *          valid screen dimensions (0 to SCREEN_WIDTH-1, 0 to SCREEN_HEIGHT-1).
 *          If the coordinates are within bounds, it calls `mlx_put_pixel` to
 *          draw the specified color onto the main scene image (`game->scene`).
 *          If out of bounds, the function returns silently.
 *
 * @param game Pointer to the main game structure (to access game->scene).
 * @param x The horizontal pixel coordinate (column).
 * @param y The vertical pixel coordinate (row).
 * @param color The color to draw in integer format (e.g., BGRA for MLX42).
 */
void	put_pixel_scene(t_game *game, int x, int y, u_int32_t color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	mlx_put_pixel(game->scene, x, y, color);
}

/**
 * @brief Safely puts a pixel onto the minimap image, checking boundaries.
 * @details Checks if the provided pixel coordinates (x, y) are within the
 *          valid minimap image dimensions (0 to minimap_data.width-1, 0 to
 *          minimap_data.height-1). If within bounds, it calls `mlx_put_pixel`
 *          to draw the specified color onto the minimap image
 *          (`game->minimap_image`). If out of bounds, returns silently.
 *
 * @param game Pointer to the main game structure (to access minimap data/image).
 * @param x The horizontal pixel coordinate relative to the minimap image.
 * @param y The vertical pixel coordinate relative to the minimap image.
 * @param color The color to draw in integer format.
 */
void	put_pixel_mmap(t_game *game, int x, int y, u_int32_t color)
{
	if (x < 0 || x >= (int)game->data->map_data.cols * game->cell_size || \
		y < 0 || y >= (int)game->data->map_data.rows * game->cell_size)
		return ;
	mlx_put_pixel(game->mini, x, y, color);
}

void	normalize_angle_to_2pi(double *angle)
{
	*angle = fmod(*angle, 2.0 * M_PI);
	if (*angle < 0.0)
		*angle += (2.0 * M_PI);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void plot_adjacent_pixels(t_game *game, t_vec2 center, int color)
{
	t_point neighbors[8];
	int dx[8];
	int dy[8];
	int i;

	dx[0] = -1;	dy[0] = -1;
	dx[1] =  0;	dy[1] = -1;
	dx[2] =  1;	dy[2] = -1;
	dx[3] = -1;	dy[3] =  0;
	dx[4] =  1;	dy[4] =  0;
	dx[5] = -1;	dy[5] =  1;
	dx[6] =  0;	dy[6] =  1;
	dx[7] =  1;	dy[7] =  1;

	i = 0;
	while (i < 8)
	{
		neighbors[i].x = (int)center.x + dx[i];
		neighbors[i].y = (int)center.y + dy[i];
		put_pixel_mmap(game, neighbors[i].x, neighbors[i].y, color);
		i++;
	}
}