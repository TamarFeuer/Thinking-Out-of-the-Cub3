#include "../inc/game.h"

//first positive slope, and then negative slope
void	draw_bresenham_ray(t_game *game, t_pos start, t_pos end)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;
	int	delta_x;
	int	delta_y;
	int	abs_delta_x;
	int	abs_delta_y;
	int	decision_variable;
	int	distance;
	int	step_x;
	int	step_y;

	x = (int)round(start.x);
	y = (int)round(start.y);
	end_x = (int)round(end.x);
	end_y = (int)round(end.y);
	delta_x = end_x - x;
	delta_y = end_y - y;
	abs_delta_x = (int)abs(delta_x);
	abs_delta_y = (int)abs(delta_y);
	step_x = 1;
	step_y = 1;
	if (delta_x < 0)
		step_x = -1;
	if (delta_y < 0)
		step_y = -1;
	// Case 1: Positive slope (abs_delta_x >= abs_delta_y)
	if (abs_delta_x >= abs_delta_y)
	{
		decision_variable = 2 * abs_delta_y - abs_delta_x;
		while (true)
		{
			distance = sqrt((x - start.x) * (x - start.x) + (y - start.y) * (y - start.y));
			if ((x == end_x && y == end_y) || x < 0 || x >= game->data->minimap_data.x_end || y < 0 || y >= game->data->minimap_data.y_end)
				return ;
			if (distance <= MAX_RAY_DISTANCE)
				safe_put_pixel(game, x, y, distance_to_color(distance, 0));
			if (decision_variable >= 0)
			{
				decision_variable -= 2 * abs_delta_x;
				y += step_y;
			}
			decision_variable += 2 * abs_delta_y;
			x += step_x;
		}
	}
	// Case 2: Negative slope (abs_delta_y > abs_delta_x)
	else
	{
		decision_variable = 2 * abs_delta_x - abs_delta_y;
		while (true)
		{
			distance = sqrt((x - start.x) * (x - start.x) + (y - start.y) * (y - start.y));
			if ((x == end_x && y == end_y) || x < 0 || x >= game->data->minimap_data.x_end || y < 0 || y >= game->data->minimap_data.y_end)
				return ;
			if (distance <= MAX_RAY_DISTANCE)
				safe_put_pixel(game, x, y, distance_to_color(distance, 0));
			if (decision_variable >= 0)
			{
				decision_variable -= 2 * abs_delta_y;
				x += step_x;
			}
			decision_variable += 2 * abs_delta_x;
			y += step_y;
		}
	}
	return ;
}
