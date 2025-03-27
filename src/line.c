#include "../inc/game.h"

void draw_bresenham_ray(t_game *game, t_pos start, t_pos end)
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
			if ((x == end_x && y == end_y) || x < X_START || x >= game->data->minimap_data.x_end || y < Y_START || y >= game->data->minimap_data.y_end)
			{
				return; // Exit without doing anything else
			}

			// Set the pixel color using the computed distance
            if (distance <= MAX_RAY_DISTANCE)
			    mlx_put_pixel(game->mini, x, y, distance_to_color(distance, 0));  //safe
			
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
			if ((x == end_x && y == end_y) || x < X_START || x >= game->data->minimap_data.x_end || y < Y_START || y >= game->data->minimap_data.y_end)
			{
				return; // Exit without doing anything else
			}

			// Set the pixel color using the computed distance
			if (distance <= MAX_RAY_DISTANCE)
                mlx_put_pixel(game->mini, x, y, distance_to_color(distance, 0));

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


void DDA_ray(t_game *game, t_pos start, t_pos end, int color)
{
    double dx = end.x - start.x;
    double dy = end.y - start.y;
    double steps;

    steps = fmax(fabs(dx), fabs(dy));

    //printf ("steps is %f\n", steps);
    double x_increment = dx / steps;
    double y_increment = dy / steps;

    double x = start.x;
    double y = start.y;
    int step_count = 0;
	
    while (step_count <= steps) 
    {
        (void)game;
        
        //double distance = get_distance(start, (t_pos){x, y});
        
        //printf("Distance at step %d: %f\n", step_count, distance);
        //mlx_put_pixel(game->scene, (int)round(x), (int)round(y), distance_to_color(distance));
        // mlx_put_pixel(game->scene, (int)round(x) - X_START,  (int)round(y) - Y_START, 
		// 	color_abgr_to_rgba(distance_to_color(distance)));
		mlx_put_pixel(game->scene, (int)round(x) - X_START,  (int)round(y) - Y_START, 
			color_abgr_to_rgba(color));
    
        x += x_increment;
        y += y_increment;
        step_count++;
    }
}

//more bresenham:

// static void draw_segment_low_slope(t_game *game, t_pos p1, t_pos p2, int col)
// {
//     int dx = p2.x - p1.x;
//     int dy = p2.y - p1.y;
//     int yi = 1;
//     int derive;

//     if (dy < 0)
//     {
//         yi = -1;
//         dy = -dy;
//     }
//     derive = (2 * dy) - dx;
//     while (p1.x <= p2.x)
//     {
//         mlx_put_pixel(img, p1.x, p1.y, col);
//         if (derive > 0)
//         {
//             p1.y += yi;
//             derive += 2 * (dy - dx);
//         }
//         else
//         {
//             derive += 2 * dy;
//         }
//         p1.x++;
//     }
// }

// static void draw_segment_high_slope(t_game *game, t_pos p1, t_pos p2, int col)
// {
//     int dx = p2.x - p1.x;
//     int dy = p2.y - p1.y;
//     int xi = 1;
//     int derive;

//     if (dx < 0)
//     {
//         xi = -1;
//         dx = -dx;
//     }
//     derive = (2 * dx) - dy;
//     while (p1.y <= p2.y)
//     {
//         mlx_put_pixel(img, p1.x, p1.y, col);
//         if (derive > 0)
//         {
//             p1.x += xi;
//             derive += 2 * (dx - dy);
//         }
//         else
//         {
//             derive += 2 * dx;
//         }
//         p1.y++;
//     }
// }
