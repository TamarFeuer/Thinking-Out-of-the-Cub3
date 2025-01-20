#include "../inc/game.h"

void bresenham_ray(t_game *game, t_pos start, t_pos end)
{
	int x = (int)round(start.x);
	int y = (int)round(start.y);
	int end_x = (int)round(end.x);
	int end_y = (int)round(end.y);
	int delta_x = (int)round(fabs(end.x - start.x));
	int delta_y = (int)round(fabs(end.y - start.y));
	int decision_variable;
    int distance;


	// Direction factors to ensure correct increments
	int step_x = 1;
	int step_y = 1;

	// Determine direction of x and y
	if (end_x < start.x)  // Moving left
		step_x = -1;
	if (end_y < start.y)  // Moving up
		step_y = -1;

	// Case 2: Positive slope (slope >= 0)
	if (delta_x >= delta_y)
	{
        //printf ("positive slope, \n");
		decision_variable = 2 * delta_y - delta_x;
		while (1)
		{

			if ((x == end_x && y == end_y) || x < X_START || x >= X_END || y < Y_START || y >= Y_END)
            {
                distance =  sqrt((x - start.x) * (x - start.x) + (y - start.y) * (y - start.y));
                //printf ("positive slope, distance is %d\n", distance);
                return;
            }
            distance =  sqrt((x - start.x) * (x - start.x) + (y - start.y) * (y - start.y));
            //printf ("negative slope, distance is %d\n", distance);
			mlx_put_pixel(game->scene, x, y, distance_to_color(distance));
			
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
    
	else if (delta_y > delta_x)  //also includes nearly vertical (dx =71, dy =72 for example)
	{
        //printf ("3. dx is %d, dy is %d\n", delta_x, delta_y);
        //printf ("negative slope\n");
		decision_variable = 2 * delta_x - delta_y;
		while (1)
		{

			if ((x == end_x && y == end_y) || x < X_START || x >= X_END || y < Y_START || y >= Y_END)
            {
                // || (game->ray->found_vertical_first == 1 &&  x > X_END)
                // || (game->ray->found_vertical_first == 0 &&  y > Y_END))
                distance =  sqrt((x - start.x) * (x - start.x) + (y - start.y) * (y - start.y));
                //printf ("Negative slope, distance is %d\n", distance);
                return;
            }
				
			//int distance = get_distance(start, end);
            distance =  sqrt((x - start.x) * (x - start.x) + (y - start.y) * (y - start.y));
            //printf ("positive slope, distance is %d\n", distance);
			mlx_put_pixel(game->scene, x, y, distance_to_color(distance));
			
			if (decision_variable >= 0)
			{
				decision_variable -= 2 * delta_y;
				x += step_x;
			}
			decision_variable += 2 * delta_x;
			y += step_y;
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
		// 	convert_to_mlx42_endian(distance_to_color(distance)));
		mlx_put_pixel(game->scene, (int)round(x) - X_START,  (int)round(y) - Y_START, 
			convert_to_mlx42_endian(color));
    
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
