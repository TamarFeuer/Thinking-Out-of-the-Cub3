#include "../inc/game.h"

void bresenham_line(t_game *game, int start[2], int end[2])
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

    // Boundary check
    if (start[0] < 0 || start[0] >= MAP_WIDTH || start[1] < 0 || start[1] >= MAP_HEIGHT ||
        end[0] < 0 || end[0] >= MAP_WIDTH || end[1] < 0 || end[1] >= MAP_HEIGHT)
        return;  // Stop if out of bounds

    // Case 1: Vertical line (undefined slope)
    if (delta_x == 0)
    {
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

    // Case 2: Positive slope (slope >= 0)
    if (delta_x >= delta_y)
    {
        decision_variable = 2 * delta_y - delta_x;
        while (x != end[0])
        {
            mlx_put_pixel(game->map, x, y, 0xFF0000FF);
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
            mlx_put_pixel(game->map, x, y, 0xFF0000FF);
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
