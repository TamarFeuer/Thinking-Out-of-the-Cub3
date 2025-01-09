#include "../inc/game.h"

// void bresenham_rays(t_game *game, t_pos start, t_pos end)
// {
// 	int x = round(start.x);
// 	int y = round(start.y);
// 	int end_x = (int)round(end.x);
// 	int end_y = (int)round(end.y);
// 	int delta_x = (int)fabs(end.x - start.x);
// 	int delta_y = (int)fabs(end.y - start.y);
// 	int decision_variable;

// 	// Direction factors to ensure correct increments
// 	int step_x = 1;
// 	int step_y = 1;

// 	// Determine direction of x and y
// 	if (end_x < start.x)  // Moving left
// 		step_x = -1;
// 	if (end_y < start.y)  // Moving up
// 		step_y = -1;

// 	// Case 1: Vertical line (undefined slope)
// 	if (delta_x == 0)
// 	{
// 		if (y < end_y)
// 		{
// 			while (y <= end_y)
// 			{
// 				if (x < X_START || x >= X_END || y < Y_START || y >= Y_END)
// 					break;
// 				int distance = get_distance(start.x, x, start.y, y);
// 				mlx_put_pixel(game->rays, x, y, );
				
// 				y++;
// 			}
// 		}
// 		else
// 		{
// 			while (y >= end_y)
// 			{
// 				if (x < X_START || x >= X_END || y < Y_START || y >= Y_END)
// 					break;
// 				int distance = get_distance(start.x, x, start.y, y);
// 				mlx_put_pixel(game->rays, x, y, distance_to_color(distance));
// 				y--;
// 			}
// 		}
// 		return;
// 	}

// 	// Case 2: Positive slope (slope >= 0)
// 	if (delta_x >= delta_y)
// 	{
// 		printf ("here!\n");
// 		decision_variable = 2 * delta_y - delta_x;
// 		while (1)
// 		{
// 			printf ("x is %d and y is %d\n", x, y);
// 			if ((x == end_x && y == end_y) || x < X_START || x >= X_END || y < Y_START || y >= Y_END)
// 			{
// 				printf ("I'm breaking\n");
// 				return;
// 			}
// 			printf ("plotting x %d and y %d\n", x, y);
// 			int distance = get_distance(start.x, x, start.y, y);
// 			mlx_put_pixel(game->rays, x, y, distance_to_color(distance));
// 			//mlx_put_pixel(game->rays, x, y, 0x112323FF);
			
// 			if (decision_variable >= 0)
// 			{
// 				decision_variable -= 2 * delta_x;
// 				y += step_y;
// 			}
// 			decision_variable += 2 * delta_y;
// 			x += step_x;
// 		}
// 	}
// 	// Case 3: Negative slope (slope < 0)
// 	else
// 	{
// 		decision_variable = 2 * delta_x - delta_y;
// 		while (y != end_y)
// 		{
// 			if (x < X_START || x >= X_END || y < Y_START || y >= Y_END)
// 				break;
// 			int distance = get_distance(start.x, x, start.y, y);
// 			mlx_put_pixel(game->rays, x, y, distance_to_color(distance));
			
// 			if (decision_variable >= 0)
// 			{
// 				decision_variable -= 2 * delta_y;
// 				x += step_x;
// 			}
// 			decision_variable += 2 * delta_x;
// 			y += step_y;
// 		}
// 	}
// }

void DDA_ray(t_game *game, t_pos start, t_pos end)
{
    double dx = end.x - start.x;
    double dy = end.y - start.y;
    double steps;

    if (fabs(dx) == fabs(dy))
        {
            printf ("!, \n");
        }
    // Determine the number of steps needed
    // if (fabs(dx) > fabs(dy))
    //     steps = fabs(dx);
    // else 
    //     steps = fabs(dy);
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
        
        double distance = get_distance(start, (t_pos){x, y});
        
        //printf("Distance at step %d: %f\n", step_count, distance);
        mlx_put_pixel(game->rays, (int)x, (int)y, distance_to_color(distance));
        
        

        x += x_increment;
        y += y_increment;
        step_count++;
    }
}

