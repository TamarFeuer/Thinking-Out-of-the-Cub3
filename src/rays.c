#include "../inc/game.h"

/**
 * @brief Converts floating-point coordinates to a 1D map array index, adjusting
 *        for ray direction and intersection type.
 * @details This function takes a precise grid position (`grid_pos`) representing
 *          a potential ray intersection point. It first calculates the basic 2D
 *          integer map indices (`block_index.x`, `block_index.y`) by dividing
 *          the coordinates by `cell_size` and truncating to integer.
 *
 *          Crucially, it then adjusts either the x or y index based on the
 *          intersection type (`flag`) and the ray's direction (`angle_quad`):
 *          - If checking a HORIZONTAL line (`flag == INTERSECT_W_HORIZONTAL`)
 *            and the ray is moving UP (`angle_quad` 1 or 2), `block_index.y`
 *            is decremented. This ensures the check targets the map cell *below*
 *            the intersection line, which is the relevant cell when approaching
 *            from below.
 *          - If checking a VERTICAL line (`flag == INTERSECT_W_VERTICAL`)
 *            and the ray is moving LEFT (`angle_quad` 2 or 3), `block_index.x`
 *            is decremented. This targets the map cell *to the right* of the
 *            intersection line, relevant when approaching from the right.
 *
 *          This explicit index adjustment correctly handles cases where the
 *          intersection falls exactly on a grid line, ensuring the appropriate
 *          cell is checked based on the direction of ray travel. Consequently,
 *          subtracting a small epsilon value from coordinates in the calling
 *          functions (`init_..._intercept_and_step`) is rendered unnecessary
 *          by this logic.
 *
 *          Finally, it converts the adjusted 2D index into a 1D array index
 *          using the map width (`game->data->map_data.cols`).
 *
 * @param game Pointer to the main game structure, used to access `cell_size`,
 *             `ray->angle_quad`, and `data->map_data.cols`.
 * @param grid_pos Pointer to the `t_vec2` structure containing the floating-point
 *                 x and y coordinates of the intersection point to check.
 * @param intersection_type An enum/int (`t_intersection_type`) indicating whether this check
 *             originates from a vertical or horizontal intersection calculation.
 *
 * @return int The calculated 1D index into the `game->data->map` array
 *             corresponding to the relevant map cell to check for a wall.
 */
int get_block_index(t_game *game, t_vec2 *grid_pos, t_intersect_type intersect_type)
{
	t_block_index block_index;

	block_index.x = (int)(grid_pos->x / game->cell_size);
	block_index.y = (int)(grid_pos->y / game->cell_size);
	if (intersect_type == INTERSECT_W_HORIZONTAL && (game->ray->angle_quad == 1 || game->ray->angle_quad == 2))
		block_index.y--;
	else if (intersect_type == INTERSECT_W_VERTICAL && (game->ray->angle_quad == 2 || game->ray->angle_quad == 3))
		block_index.x--;
	block_index.index = block_index.y * game->data->map_data.cols + block_index.x;
	return (block_index.index);
}

double get_distance(t_vec2 start, t_vec2 end)
{
	double dx = end.x - start.x;
	double dy = end.y - start.y;
	return sqrt(dx * dx + dy * dy);
}

void cast_rays(t_game *game)
{
	t_ray *const		ray = game->ray;

	ray->ray_num = 0;
	while (ray->ray_num < SCREEN_WIDTH)
	{	
		ray->relative_angle = atan((SCREEN_WIDTH / 2.0 - ray->ray_num) / game->pplane);
		ray->current_angle = game->player.angle + ray->relative_angle;
		normalize_angle_to_2pi(&ray->current_angle);
		determine_quad(ray->current_angle, &ray->angle_quad);
		ray->tan_current = tan(ray->current_angle);
		reach_nearest_wall_by_intersections(game);
		game->ray_end[ray->ray_num].x = ray->end.x;
		game->ray_end[ray->ray_num].y = ray->end.y;

		//draw_ray(game, game->camera.pos, game->ray->end);
		//printf ("in cast_rays: angle is %f\n", game->ray->current_angle);
		draw_scene(game, game->ray);

		ray->ray_num++;
	}
}
