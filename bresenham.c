#include "../inc/game.h"

void bresenham_line(t_game *game, int start[2], int end[2])
{
    int x = start[0];
    int y = start[1];
    int delta_x = end[0] - start[0];
    int delta_y = end[1] - start[1];
    int decision_variable;

	if (start[0] < 0 || start[0] >= MAP_WIDTH || start[1] < 0 || start[1] >= MAP_HEIGHT ||
        end[0] < 0 || end[0] >= MAP_WIDTH || end[1] < 0 || end[1] >= MAP_HEIGHT)
        return;  // Stop if out of bounds


    // Case 1: Vertical line (undefined slope)
    if (delta_x == 0)
    {
        // If the line is vertical, just iterate over the y-axis
        if (y < end[1])
        {
            while (y <= end[1])
            {
                mlx_put_pixel(game->map, x, y, 0xFF0000FF);
                y++;
            }
        }
        else
        {
            while (y >= end[1])
            {
                mlx_put_pixel(game->map, x, y, 0xFF0000FF);
                y--;
            }
        }
        return;
    }

    // Case 2: Positive slope (slope > 0)
    if (delta_y >= 0 && delta_x > 0)
    {
        decision_variable = 2 * delta_y - delta_x;
        while (x <= end[0])
        {
            mlx_put_pixel(game->map, x, y, 0xFF0000FF);
            x++;
            if (decision_variable < 0)
                decision_variable += 2 * delta_y;
            else
            {
                decision_variable += 2 * delta_y - 2 * delta_x;
                y++;
            }
        }
    }

    // Case 3: Negative slope (slope < 0)
    else if (delta_y < 0 && delta_x > 0)
    {
        delta_y = -delta_y;  // Make the slope positive for calculation purposes
        decision_variable = 2 * delta_y - delta_x;
        while (x <= end[0])
        {
            mlx_put_pixel(game->map, x, y, 0xFF0000FF);
            x++;
            if (decision_variable < 0)
                decision_variable += 2 * delta_y;
            else
            {
                decision_variable += 2 * delta_y - 2 * delta_x;
                y--;
            }
        }
    }

    // Case 4: Very steep line where delta_x is much smaller than delta_y (handle special case)
    if (abs(delta_y) > abs(delta_x))
    {
        decision_variable = 2 * delta_x - delta_y;
        while (y <= end[1])
        {
            mlx_put_pixel(game->map, x, y, 0xFF0000FF);
            y++;
            if (decision_variable < 0)
                decision_variable += 2 * delta_x;
            else
            {
                decision_variable += 2 * delta_x - 2 * delta_y;
                x++;
            }
        }
    }
}