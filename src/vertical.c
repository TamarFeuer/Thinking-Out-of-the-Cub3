#include "../inc/game.h"

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
