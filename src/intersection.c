/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfeuer <tfeuer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:46:50 by tfeuer            #+#    #+#             */
/*   Updated: 2025/04/20 15:46:51 by tfeuer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static bool	should_continue_stepping(t_game *game, t_vec2 intersect, \
	t_intersect_type intersect_type)
{
	if (is_out_of_bounds(game, intersect))
		return (false);
	if (is_wall_hit(game, intersect, intersect_type))
		return (false);
	return (true);
}

static void	init_horizontal_intercept_and_step(t_game *game, \
	double cotan_current)
{
	t_vec2	*intersect;
	t_vec2	*step;
	double	delta_y;

	intersect = &game->ray->intersect;
	step = &game->ray->ray_step;
	if (game->ray->angle_quad == 1 || game->ray->angle_quad == 2)
	{
		intersect->y = floor(game->camera_pos.y / game->cell_size)
			* game->cell_size;
		step->y = -game->cell_size;
	}
	else
	{
		intersect->y = ceil(game->camera_pos.y / game->cell_size)
			* game->cell_size;
		step->y = game->cell_size;
	}
	delta_y = intersect->y - game->camera_pos.y;
	intersect->x = game->camera_pos.x - delta_y * cotan_current;
	step->x = step->y * -cotan_current;
}

/**
 * @brief Calculates the distance to the nearest wall intersected by a ray
 *        when checking along horizontal grid lines.
 * @details Performs raycasting by checking for intersections with horizontal
 *          grid lines. It first handles edge cases: purely horizontal rays
 *          (`tan_current` is 0) return `OUT_OF_BOUNDS`. It then calculates
 *          the cotangent (`cotan_current`) of the ray's angle, handling
 *          vertical rays (`tan_current` is +/- HUGE_VAL). This cotangent is
 *          then passed to `init_horizontal_intercept_and_step` to initialize
 *          the starting intersection point and step increments. The function
 *          then iteratively steps along the ray's path using
 *          `should_continue_stepping` to check for boundaries or wall hits.
 *          If a wall is hit, it stores coordinates in `game->ray->h_hit` and
 *          returns the distance. Returns `OUT_OF_BOUNDS` if the ray goes out
 *          of bounds first.
 *
 * @param game Pointer to the main game structure (`t_game`). Used to access
 *             ray properties, camera position, and map data. `game->ray->h_hit`
 *             will be updated upon a successful hit.
 *
 * @return double Returns the distance from the camera position to the horizontal
 *         wall hit point (`game->ray->h_hit`), or `OUT_OF_BOUNDS` if the ray
 *         leaves map boundaries, or if the ray is perfectly horizontal.
 *
 * @note Modifies `game->ray->h_hit` if a wall is hit. Relies on
 *       `init_horizontal_intercept_and_step` to modify `game->ray->intersect`
 *       and `game->ray->ray_step`.
 */
double	horiz_intersect(t_game *game)
{
	double	cotan_current;

	if (game->ray->tan_current == 0)
		return (OUT_OF_BOUNDS);
	if (game->ray->tan_current == HUGE_VAL
		|| game->ray->tan_current == -HUGE_VAL)
		cotan_current = 0;
	else
		cotan_current = 1.0 / game->ray->tan_current;
	init_horizontal_intercept_and_step(game, cotan_current);
	if (game->is_debug)
		plot_adjacent_pixels(game, game->ray->intersect, 0xFFFF00FF);
	while (should_continue_stepping(game, game->ray->intersect, \
									INTERSECT_W_HORIZONTAL))
	{
		if (game->is_debug)
			plot_adjacent_pixels(game, game->ray->intersect, 0xFFFF00FF);
		game->ray->intersect.x += game->ray->ray_step.x;
		game->ray->intersect.y += game->ray->ray_step.y;
	}
	if (is_out_of_bounds(game, game->ray->intersect))
		return (OUT_OF_BOUNDS);
	game->ray->h_hit.x = game->ray->intersect.x;
	game->ray->h_hit.y = game->ray->intersect.y;
	return (get_distance(game->camera_pos, game->ray->h_hit));
}

/**
 * @brief Calculates the initial vertical grid intersection and step increments.
 * @details This function sets up the starting conditions for vertical grid
 *          line stepping in the raycasting process. It calculates the
 *          coordinate of the first vertical grid line the ray hits and the
 *          necessary step sizes to reach subsequent vertical lines.
 *
 *          Local Variables:
 *          - `intersect`: A pointer (`t_vec2*`) used as a shorthand alias for
 *            `game->ray->intersect`. It stores the calculated (x, y)
 *            coordinates of the *first* intersection point with a vertical
 *            grid line.
 *          - `step`: A pointer (`t_vec2*`) used as a shorthand alias for
 *            `game->ray->ray_step`. It stores the calculated (dx, dy) step
 *            increments. `step->x` is the fixed horizontal distance to the
 *            next vertical grid line (+/- cell_size), and `step->y` is the
 *            corresponding vertical distance along the ray.
 *          - `delta_x`: A temporary variable (`double`) storing the horizontal
 *            distance between the camera's x-position (`game->camera_pos.x`)
 *            and the x-coordinate of the first vertical intersection
 *            (`intersect->x`). This is used to calculate the initial
 *            `intersect->y`.
 *
 *          The function determines the initial `intersect->x` based on whether
 *          the ray faces left or right (`game->ray->angle_quad`), using `floor`
 *          or `ceil`. It then calculates `intersect->y` using `delta_x` and the
 *          ray's tangent (`game->ray->tan_current`). Finally, it calculates
 *          the step components (`step->x`, `step->y`). All results are stored
 *          back into the `game->ray` struct via the `intersect` and `step`
 *          pointers.
 *
 * @param game Pointer to the main game structure (`t_game`), providing access
 *             to `camera_pos`, `cell_size`, and the `ray` whose `intersect`
 *             and `ray_step` fields will be updated.
 *
 * @note Modifies `game->ray->intersect` and `game->ray->ray_step`. Returns void.
 *//**
 * @brief Calculates the initial vertical grid intersection and step increments.
 * @details This function sets up the starting conditions for vertical grid
 *          line stepping in the raycasting process. It calculates the
 *          coordinate of the first vertical grid line the ray hits and the
 *          necessary step sizes to reach subsequent vertical lines.
 *
 *          Local Variables:
 *          - `intersect`: A pointer (`t_vec2*`) used as a shorthand alias for
 *            `game->ray->intersect`. It stores the calculated (x, y)
 *            coordinates of the *first* intersection point with a vertical
 *            grid line.
 *          - `step`: A pointer (`t_vec2*`) used as a shorthand alias for
 *            `game->ray->ray_step`. It stores the calculated (dx, dy) step
 *            increments. `step->x` is the fixed horizontal distance to the
 *            next vertical grid line (+/- cell_size), and `step->y` is the
 *            corresponding vertical distance along the ray.
 *          - `delta_x`: A temporary variable (`double`) storing the horizontal
 *            distance between the camera's x-position (`game->camera_pos.x`)
 *            and the x-coordinate of the first vertical intersection
 *            (`intersect->x`). This is used to calculate the initial
 *            `intersect->y`.
 *
 *          The function determines the initial `intersect->x` based on whether
 *          the ray faces left or right (`game->ray->angle_quad`), using `floor`
 *          or `ceil`. It then calculates `intersect->y` using `delta_x` and the
 *          ray's tangent (`game->ray->tan_current`). Finally, it calculates
 *          the step components (`step->x`, `step->y`). All results are stored
 *          back into the `game->ray` struct via the `intersect` and `step`
 *          pointers.
 *
 * @param game Pointer to the main game structure (`t_game`), providing access
 *             to `camera_pos`, `cell_size`, and the `ray` whose `intersect`
 *             and `ray_step` fields will be updated.
 *
 * @note Modifies `game->ray->intersect` and `game->ray->ray_step`. Returns void.
 */
static void	init_vertical_intercept_and_step(t_game *game)
{
	t_vec2	*intersect;
	t_vec2	*step;
	double	delta_x;

	intersect = &game->ray->intersect;
	step = &game->ray->ray_step;
	if (game->ray->angle_quad == 1 || game->ray->angle_quad == 4)
	{
		intersect->x = ceil(game->camera_pos.x / game->cell_size)
			* game->cell_size;
		step->x = game->cell_size;
	}
	else
	{
		intersect->x = floor(game->camera_pos.x / game->cell_size)
			* game->cell_size;
		step->x = -game->cell_size;
	}
	delta_x = intersect->x - game->camera_pos.x;
	intersect->y = game->camera_pos.y - delta_x * game->ray->tan_current;
	step->y = step->x * -game->ray->tan_current;
}

/**
 * @brief Calculates the distance to the nearest wall intersected by a ray
 *        when checking along vertical grid lines.
 * @details This function performs raycasting by specifically checking for
 *          intersections with vertical grid lines in the map. It first handles
 *          the edge case of purely vertical rays. Then, it initializes the
 *          starting intersection point and step increments using
 *          `init_vertical_intercept_and_step`. It iteratively steps along the
 *          ray's path from one vertical grid line to the next, using
 *          `should_continue_stepping` to check for map boundaries or wall hits
 *          at each step. Once the loop terminates (due to hitting a wall or
 *          going out of bounds), it determines if a wall was hit within bounds.
 *          If so, it stores the hit coordinates in `game->ray->v_hit` and
 *          returns the calculated distance from the camera to the hit point.
 *          If the ray goes out of bounds first, it returns `OUT_OF_BOUNDS`.
 *
 * @param game Pointer to the main game structure (`t_game`). It's used to
 *             access ray properties (`game->ray`), camera position
 *             (`game->camera_pos`), map data (via helper functions), and
 *             will have `game->ray->v_hit` updated upon a successful hit.
 *
 * @return double Returns the distance from the camera position to the vertical
 *         wall hit point (`game->ray->v_hit`), or a specific value
 *         (`OUT_OF_BOUNDS`, typically -1.0 or similar) if the ray leaves the
 *         map boundaries before hitting a vertical wall segment.
 *
 * @note This function modifies `game->ray->v_hit` if a wall is hit. It also
 *       relies on `init_vertical_intercept_and_step` to modify
 *       `game->ray->intersect` and `game->ray->ray_step`.
 */
double	vertical_intersect(t_game *game)
{
	if (game->ray->tan_current == HUGE_VAL
		|| game->ray->tan_current == -HUGE_VAL)
		return (OUT_OF_BOUNDS);
	init_vertical_intercept_and_step(game);
	if (game->is_debug)
		plot_adjacent_pixels(game, game->ray->intersect, 0xFF0000FF);
	while (should_continue_stepping(game, game->ray->intersect, \
									INTERSECT_W_VERTICAL))
	{
		if (game->is_debug)
			plot_adjacent_pixels(game, game->ray->intersect, 0xFF0000FF);
		game->ray->intersect.x += game->ray->ray_step.x;
		game->ray->intersect.y += game->ray->ray_step.y;
	}
	if (is_out_of_bounds(game, game->ray->intersect))
		return (OUT_OF_BOUNDS);
	game->ray->v_hit.x = game->ray->intersect.x;
	game->ray->v_hit.y = game->ray->intersect.y;
	return (get_distance(game->camera_pos, game->ray->v_hit));
}
