#include "../inc/game.h"

void draw_bresenham_ray(t_game *game, t_vec2 start, t_vec2 end)
{
    int x = (int)round(start.x);
    int y = (int)round(start.y);
    int end_x = (int)round(end.x);
    int end_y = (int)round(end.y);
    
    // Original differences for slope determination
    int delta_x = end_x - x;  // Original difference
    int delta_y = end_y - y;  // Original difference
    int abs_delta_x = (int)abs(delta_x);  // Absolute difference
    int abs_delta_y = (int)abs(delta_y);  // Absolute difference
    
    int decision_variable;
    int distance;

    //printf("in bresenham\n");
    //printf("start.x is %d start.y is %d\n", x, y);
    //printf("end_x is %d end_y is %d\n", end_x, end_y);
    //printf("current angle is %f\n", game->ray->current_angle);
    
    // Direction factors to ensure correct increments
    int step_x = 1; // Default step to the right
    int step_y = 1; // Default step downwards

    // Determine direction of x and y
    if (delta_x < 0)  // Moving left
        step_x = -1;
    if (delta_y < 0)  // Moving up
        step_y = -1;

    // Case 1: Positive slope (abs_delta_x >= abs_delta_y)
    if (abs_delta_x >= abs_delta_y)
    {
        //printf("positive slope, \n");
        decision_variable = 2 * abs_delta_y - abs_delta_x;
        
        while (1)
		{
			// Calculate the distance
			distance = sqrt((x - start.x) * (x - start.x) + (y - start.y) * (y - start.y));
			
			// Check if we should exit
			if ((x == end_x && y == end_y) || x < 0 || x >= game->data->minimap_data.x_end || y < 0 || y >= game->data->minimap_data.y_end)
			{
				return; // Exit without doing anything else
			}

			// Set the pixel color using the computed distance
            if (distance <= MAX_RAY_DISTANCE)
				put_pixel_mmap(game, x, y, distance_to_color(distance, CASTED_RAYS));
			
			// Update the decision variable and position
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
		//printf("negative slope\n");
		decision_variable = 2 * abs_delta_x - abs_delta_y;

		while (1)
		{
			// Calculate the distance once at the start of the loop
			distance = sqrt((x - start.x) * (x - start.x) + (y - start.y) * (y - start.y));

			// Check if we should exit
			if ((x == end_x && y == end_y) || x < 0 || x >= game->data->minimap_data.x_end || y < 0 || y >= game->data->minimap_data.y_end)
			{
				return; // Exit without doing anything else
			}

			// Set the pixel color using the computed distance
			if (distance <= MAX_RAY_DISTANCE)
				put_pixel_mmap(game, x, y, distance_to_color(distance, CASTED_RAYS));

			// Update the decision variable and position
			if (decision_variable >= 0)
			{
				decision_variable -= 2 * abs_delta_y;
				x += step_x; // Increment x
			}
			decision_variable += 2 * abs_delta_x;
			y += step_y; // Increment y
		}
	}

    return;
}
