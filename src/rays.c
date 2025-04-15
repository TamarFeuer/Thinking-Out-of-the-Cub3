#include "../inc/game.h"

/**
 * @brief Converts float coordinates to a 1D map index, adjusting for ray 
 *        direction.
 * @details Calculates the 2D map indices from floating-point grid coordinates.
 *          It then adjusts the index based on the intersection type (`flag`)
 *          and the ray's direction (`angle_quad`) to correctly identify the
 *          map cell being intersected, especially when hitting exact grid lines.
 *
 *          Adjustment logic:
 *          - Horizontal Line (`INTERSECT_W_HORIZONTAL`) check:
 *            If ray moves UP (`angle_quad` 1 or 2), decrement Y index to check
 *            the cell *below* the line.
 *          - Vertical Line (`INTERSECT_W_VERTICAL`) check:
 *            If ray moves LEFT (`angle_quad` 2 or 3), decrement X index
 *            to check the cell *to the left* of the line.
 *
 *          This logic handles grid line intersections precisely,
 *          removing the need for epsilon adjustments in coordinate
 *          calculations elsewhere.
 *          Finally, converts the adjusted 2D index (x, y) into a
 *          1D array index using the map width.
 *
 * @param game Pointer to the main game structure, accessing `cell_size`,
 *             `ray->angle_quad`, and `data->map_data.cols`.
 * @param grid_pos Pointer to `t_vec2` with the float x, y coordinates of the
 *                 intersection point.
 * @param intersection_type Enum (`t_intersection_type`) indicating if this check
 *                          is for a vertical or horizontal line intersection.
 *
 * @return int The 1D index into `game->data->map` for the relevant map cell.
 */
int	get_block_index(t_game *game, t_vec2 *grid_pos, \
	t_intersect_type intersect_type)
{
	t_block_index	block_index;

	block_index.x = (int)(grid_pos->x / game->cell_size);
	block_index.y = (int)(grid_pos->y / game->cell_size);
	if (intersect_type == INTERSECT_W_HORIZONTAL && \
		(game->ray->angle_quad == 1 || game->ray->angle_quad == 2))
		block_index.y--;
	else if (intersect_type == INTERSECT_W_VERTICAL && \
		(game->ray->angle_quad == 2 || game->ray->angle_quad == 3))
		block_index.x--;
	block_index.index = block_index.y * game->data->map_data.cols + \
		block_index.x;
	return (block_index.index);
}

double	get_distance(t_vec2 start, t_vec2 end)
{
	double	dx;
	double	dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	return (sqrt(dx * dx + dy * dy));
}

void	cast_rays(t_game *game)
{
	t_ray *const		ray = game->ray;

	ray->ray_num = 0;
	while (ray->ray_num < game->number_of_rays)
	{
		ray->relative_angle = atan((SCREEN_WIDTH / 2.0 - ray->ray_num) / \
			game->pplane);
		if (game->is_debug == true)
			ray->relative_angle = 0;
		ray->current_angle = game->player.angle + ray->relative_angle;
		normalize_angle_to_2pi(&ray->current_angle);
		determine_quad(ray->current_angle, &ray->angle_quad);
		ray->tan_current = tan(ray->current_angle);
		reach_nearest_wall_by_intersections(game);
		game->ray_end[ray->ray_num].x = ray->end.x;
		game->ray_end[ray->ray_num].y = ray->end.y;
		draw_scene(game, game->ray);
		ray->ray_num++;
	}
}
