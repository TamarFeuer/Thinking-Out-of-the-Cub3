/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfeuer <tfeuer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:47:05 by tfeuer            #+#    #+#             */
/*   Updated: 2025/04/20 21:47:54 by tfeuer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

bool	is_out_of_bounds(t_game *game, t_vec2 position)
{
	if (position.y < 0 || position.x < 0 || position.y >= \
		game->data->map_data.rows * game->cell_size || position.x >= \
		game->data->map_data.cols * game->cell_size)
		return (true);
	return (false);
}

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
int	 get_block_index(t_game *game, t_vec2 *grid_pos, \
	t_intersect_type intersect_type)
{
	t_block_index	block_index;

	block_index.x = (int)(grid_pos->x / game->cell_size);
	//printf ("	block_index.x is %d, grid_pos.x is %.10f\n", block_index.x, grid_pos->x);
	block_index.y = (int)(grid_pos->y / game->cell_size);
	if (intersect_type == INTERSECT_W_HORIZONTAL && \
		(game->ray->angle_quad == 1 || game->ray->angle_quad == 2) && block_index.y != 0)
		block_index.y--;
	else if (intersect_type == INTERSECT_W_VERTICAL && \
		(game->ray->angle_quad == 2 || game->ray->angle_quad == 3) && block_index.x != 0)
		block_index.x--;
	// if (intersect_type == INTERSECT_W_HORIZONTAL && \
	// 	(game->ray->angle_quad == 1 || game->ray->angle_quad == 2) )
	// 	block_index.y--;
	// else if (intersect_type == INTERSECT_W_VERTICAL && \
	// 	(game->ray->angle_quad == 2 || game->ray->angle_quad == 3) )
	// 	block_index.x--;
	block_index.index = block_index.y * game->data->map_data.cols + \
		block_index.x;
	if (block_index.index < 0)
	{
		printf ("it is %d, ray number is %d\n", block_index.index, game->ray->ray_num);
		printf("end of this ray horizontallyis x=%f y=%f \n", game->ray->h_hit.x, game->ray->h_hit.y);
		printf("end of this ray vertically is x=%f y=%f \n", game->ray->v_hit.x, game->ray->v_hit.y);
		printf ("intersect type is %d, block_index x is %d, block_index y is %d and index is %d\n", intersect_type, block_index.x, block_index.y, block_index.index);
	}
		return (block_index.index);
}

int	is_wall_hit(t_game *game, t_vec2 inter, t_intersect_type intersect_type)
{
	return (game->data->map[get_block_index(game, &inter, intersect_type)] == \
		WALL);
}
