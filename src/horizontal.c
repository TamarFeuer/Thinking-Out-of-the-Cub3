#include "../inc/game.h"

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
