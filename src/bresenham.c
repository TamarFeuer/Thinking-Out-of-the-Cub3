#include "../inc/game.h"

void bresenham_rays(t_game *game, int start[2], int end[2])
{
	int x = start[0];
	int y = start[1];
	int delta_x = abs(end[0] - start[0]);
	int delta_y = abs(end[1] - start[1]);
	int decision_variable;

	// Direction factors to ensure correct increments
	int step_x = 1;
	int step_y = 1;

	// Determine direction of x and y
	if (end[0] < start[0])  // Moving left
		step_x = -1;
	if (end[1] < start[1])  // Moving up
		step_y = -1;

	// Case 1: Vertical line (undefined slope)
	if (delta_x == 0)
	{
		if (y < end[1])
		{
			while (y <= end[1])
			{
				if (x < X_START || x >= X_END || y < Y_START || y >= Y_END)
					break;
				mlx_put_pixel(game->rays, x, y, 0xFF0000FF);
				y++;
			}
		}
		else
		{
			while (y >= end[1])
			{
				if (x < X_START || x >= X_END || y < Y_START || y >= Y_END)
					break;
				mlx_put_pixel(game->rays, x, y, 0xFF0000FF);
				y--;
			}
		}
		return;
	}

	// Case 2: Positive slope (slope >= 0)
	if (delta_x >= delta_y)
	{
		decision_variable = 2 * delta_y - delta_x;
		while (x != end[0])
		{
			if (x < X_START || x >= X_END || y < Y_START || y >= Y_END)
				break;
			mlx_put_pixel(game->rays, x, y, 0xFF0000FF);
			if (decision_variable >= 0)
			{
				decision_variable -= 2 * delta_x;
				y += step_y;
			}
			decision_variable += 2 * delta_y;
			x += step_x;
		}
	}
	// Case 3: Negative slope (slope < 0)
	else
	{
		decision_variable = 2 * delta_x - delta_y;
		while (y != end[1])
		{
			if (x < X_START || x >= X_END || y < Y_START || y >=Y_END)
				break;
			mlx_put_pixel(game->rays, x, y, 0xFF0000FF);
			if (decision_variable >= 0)
			{
				decision_variable -= 2 * delta_y;
				x += step_x;
			}
			decision_variable += 2 * delta_x;
			y += step_y;
		}
	}
}

void cast_rays(t_game *game)
{
	float ray_angle;
	float start_angle = game->player.angle - (FOV / 2) * DEG_TO_RAD;
	float end_angle = game->player.angle + (FOV / 2) * DEG_TO_RAD;
	float step = FOV * DEG_TO_RAD / RAY_COUNT;

	// Delete only the rays layer to refresh it
	if (game->rays)
		mlx_delete_image(game->mlx, game->rays);
	game->rays = mlx_new_image(game->mlx, 1024, 512);
	if (!game->rays || mlx_image_to_window(game->mlx, game->rays, 0, 0) < 0)
		return;

	ray_angle = start_angle;
	while (ray_angle <= end_angle)
	{
		float dx = cos(ray_angle);
		float dy = sin(ray_angle);

		float start_x = game->player.x + 1 * CONST;
		float start_y = game->player.y + 1 * CONST;

		float end_x = start_x + dx * 300; // Ray length 300 pixels
		float end_y = start_y + dy * 300;

		int ver1[2] = {start_x, start_y}; 
		int ver2[2] = {end_x, end_y}; 

		bresenham_rays(game, ver1, ver2);
		ray_angle += step;
	}
}
