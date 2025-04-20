/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfeuer <tfeuer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:14:53 by tfeuer            #+#    #+#             */
/*   Updated: 2025/04/20 15:46:15 by tfeuer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

/**
 * @brief Initializes parameters for Bresenham's line algorithm.
 * @details Calculates and stores essential values needed for drawing a line
 *          between two points using Bresenham's method. It rounds the float
 *          start/end coordinates to integers for grid traversal. It calculates
 *          the total change in x (`delta_x`) and y (`delta_y`), their absolute
 *          values (`abs_dx`, `abs_dy`), and the direction of movement along
 *          each axis (`step_x`, `step_y`, either 1 or -1). Stores the original
 *          float `start` coordinate for accurate distance calculations later.
 *
 * @param bres_params Pointer to the `t_bresenham_params` struct to be filled.
 * @param start The starting point of the line (float coordinates).
 * @param end The ending point of the line (float coordinates).
 */
static void	init_bresenham_params(t_bresenham_params *bres_params, \
	t_vec2 start, t_vec2 end)
{
	int	delta_x;
	int	delta_y;

	bres_params->x_start = (int)round(start.x);
	bres_params->y_start = (int)round(start.y);
	bres_params->x_end = (int)round(end.x);
	bres_params->y_end = (int)round(end.y);
	bres_params->start = start;
	delta_x = bres_params->x_end - bres_params->x_start;
	delta_y = bres_params->y_end - bres_params->y_start;
	bres_params->abs_dx = abs(delta_x);
	bres_params->abs_dy = abs(delta_y);
	bres_params->step_x = 1;
	bres_params->step_y = 1;
	if (delta_x < 0)
		bres_params->step_x = -1;
	if (delta_y < 0)
		bres_params->step_y = -1;
}

/**
 * @brief Plots a pixel on the minimap after validation checks.
 * @details Checks if the given integer coordinates (x, y) fall within the
 *          valid boundaries of the minimap image defined in `game->data`.
 *          If within bounds, it calculates the Euclidean distance from the
 *          original floating-point `start` position to the current pixel (x, y).
 *          If this distance is less than or equal to `MAX_RAY_DISTANCE`, it
 *          converts the distance to a color using `distance_to_color` and
 *          plots the pixel on the minimap using `put_pixel_mmap`.
 *
 * @param game Pointer to the main game structure (for map bounds, pixel func).
 * @param start The original floating-point start position of the ray.
 * @param x The current integer x-coordinate of the pixel to potentially plot.
 * @param y The current integer y-coordinate of the pixel to potentially plot.
 */
static void	plot_dissipating_pixel(t_game *game, t_vec2 start, int x, int y)
{
	int	distance;

	if (x < 0 || x >= game->data->map_data.cols * game->cell_size
		|| y < 0 || y >= game->data->map_data.rows * game->cell_size)
		return ;
	distance = (int)sqrt((x - start.x) * (x - start.x)
			+ (y - start.y) * (y - start.y));
	if (distance <= MAX_RAY_DISTANCE)
		put_pixel_mmap(game, x, y, distance_to_color(distance, CASTED_RAYS));
}

/**
 * @brief Executes the Bresenham loop for lines with gentle slopes.
 * @details Handles line drawing where the absolute change in x is greater than
 *          or equal to the absolute change in y (slope magnitude <= 1).
 *          It initializes the Bresenham decision variable based on this slope
 *          type. Inside the loop, it plots the current pixel using
 *          `plot_valid_pixel`, checks if the end point is reached, and updates
 *          the decision variable. It always steps along the primary axis (x)
 *          and conditionally steps along the secondary axis (y) based on the
 *          decision variable's sign.
 *
 * @param game Pointer to the main game structure (passed to plotting func).
 * @param bres_params Pointer to the initialized Bresenham parameters struct.
 */
static void	bresenham_loop_gentle(t_game *game, t_bresenham_params *bres_params)
{
	int	decision;
	int	x;
	int	y;

	x = bres_params->x_start;
	y = bres_params->y_start;
	decision = 2 * bres_params->abs_dy - bres_params->abs_dx;
	while (true)
	{
		plot_dissipating_pixel(game, bres_params->start, x, y);
		if (x == bres_params->x_end && y == bres_params->y_end)
			break ;
		if (decision >= 0)
		{
			decision -= 2 * bres_params->abs_dx;
			y += bres_params->step_y;
		}
		decision += 2 * bres_params->abs_dy;
		x += bres_params->step_x;
	}
}

/**
 * @brief Executes the Bresenham loop for lines with steep slopes.
 * @details Handles line drawing where the absolute change in y is greater than
 *          the absolute change in x (slope magnitude > 1).
 *          It initializes the Bresenham decision variable based on this slope
 *          type. Inside the loop, it plots the current pixel using
 *          `plot_valid_pixel`, checks if the end point is reached, and updates
 *          the decision variable. It always steps along the primary axis (y)
 *          and conditionally steps along the secondary axis (x) based on the
 *          decision variable's sign.
 *
 * @param game Pointer to the main game structure (passed to plotting func).
 * @param bres_params Pointer to the initialized Bresenham parameters struct.
 */
static void	bresenham_loop_steep(t_game *game, t_bresenham_params *bres_params)
{
	int	decision;
	int	x;
	int	y;

	x = bres_params->x_start;
	y = bres_params->y_start;
	decision = 2 * bres_params->abs_dx - bres_params->abs_dy;
	while (true)
	{
		plot_dissipating_pixel(game, bres_params->start, x, y);
		if (x == bres_params->x_end && y == bres_params->y_end)
			break ;
		if (decision >= 0)
		{
			decision -= 2 * bres_params->abs_dy;
			x += bres_params->step_x;
		}
		decision += 2 * bres_params->abs_dx;
		y += bres_params->step_y;
	}
}

/**
 * @brief Draws a ray on the minimap using Bresenham's line algorithm.
 * @details This is the main interface function. It initializes the necessary
 *          parameters for Bresenham's algorithm by calling the helper function
 *          `init_bresenham_params`. It then compares the absolute changes in x
 *          and y (`abs_dx` vs `abs_dy`) to determine if the line has a "gentle"
 *          or "steep" slope. Based on this comparison, it calls the appropriate
 *          loop function (`bresenham_loop_gentle` or `bresenham_loop_steep`)
 *          to perform the actual pixel plotting along the line.
 *
 * @param game Pointer to the main game structure.
 * @param start Starting point of the ray (float coordinates).
 * @param end   Ending point of the ray (float coordinates).
 */
void	draw_bresenham_ray(t_game *game, t_vec2 start, t_vec2 end)
{
	t_bresenham_params	bres_params;

	init_bresenham_params(&bres_params, start, end);
	if (bres_params.abs_dx >= bres_params.abs_dy)
		bresenham_loop_gentle(game, &bres_params);
	else
		bresenham_loop_steep(game, &bres_params);
}
