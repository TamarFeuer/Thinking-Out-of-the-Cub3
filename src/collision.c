/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfeuer <tfeuer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:15:40 by tfeuer            #+#    #+#             */
/*   Updated: 2025/04/20 15:02:43 by tfeuer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

bool	is_colliding(t_game *game, t_vec2 new, t_intersect_type intersect_type)
{
	t_vec2	new_tl;
	t_vec2	new_tr;
	t_vec2	new_bl;
	t_vec2	new_br;

	new_tl = new;
	new_tr.x = new.x + PLAYER_SIZE;
	new_tr.y = new.y;
	new_bl.x = new.x;
	new_bl.y = new.y + PLAYER_SIZE;
	new_br.x = new.x + PLAYER_SIZE;
	new_br.y = new.y + PLAYER_SIZE;
	if (is_wall_hit(game, new_tl, intersect_type)
		|| is_wall_hit(game, new_tr, intersect_type)
		|| is_wall_hit(game, new_bl, intersect_type)
		|| is_wall_hit(game, new_br, intersect_type))
		return (true);
	else
		return (false);
}

/**
 * @brief Updates the player's and camera's position based on a new valid
 *        position.
 * @details Sets the `game->player.pos` to `new_valid_pos`. Also updates the
 *          `game->camera_pos` based on the new player position and offsets.
 *
 * @param game Pointer to the main game structure.
 * @param new_valid_pos The new, collision-free position for the player.
 */
static void	update_player_and_camera_pos(t_game *game, t_vec2 new_valid_pos)
{
	game->player.pos = new_valid_pos;
	game->camera_pos.x = game->player.pos.x + (PLAYER_SIZE - 1) / 2;
	game->camera_pos.y = game->player.pos.y + (PLAYER_SIZE - 1) / 2;
}

/**
 * @brief Attempts "wall sliding" by checking axis-aligned moves if a diagonal
 *        move is blocked.
 * @details If a direct move to `new_pos` resulted in a collision, this function
 *          checks if moving only horizontally (to `new_pos.x`, `old_pos.y`) or
 *          only vertically (to `old_pos.x`, `new_pos.y`) is possible without
 *          colliding. If either axis-aligned move is valid, it updates the
 *          player's position accordingly using `update_player_and_camera_pos`
 *          and returns true.
 *
 * @param game Pointer to the main game structure.
 * @param old_pos The player's position before the attempted move.
 * @param new_pos The diagonally desired, but colliding, new position.
 *
 * @return bool Returns `true` if a valid slide movement (horizontal or
 *         vertical) was found and applied, `false` otherwise (meaning the
 *         player stays at `old_pos`).
 */
static bool	try_slide_movement(t_game *game, t_vec2 old_pos, t_vec2 new_pos)
{
	t_vec2	horizontal_try;
	t_vec2	vertical_try;

	horizontal_try.x = new_pos.x;
	horizontal_try.y = old_pos.y;
	vertical_try.x = old_pos.x;
	vertical_try.y = new_pos.y;
	if (!is_colliding(game, horizontal_try, INTERSECT_NONE))
	{
		update_player_and_camera_pos(game, horizontal_try);
		return (true);
	}
	if (!is_colliding(game, vertical_try, INTERSECT_NONE))
	{
		update_player_and_camera_pos(game, vertical_try);
		return (true);
	}
	return (false);
}

/**
 * @brief Checks for collision at a desired new position and updates the player
 *        position, attempting wall sliding if necessary.
 * @details Checks if moving the player from `old_pos` directly to `new_pos`
 *          results in a collision using `is_colliding`.
 *          - If there is no collision, the player's position is updated to
 *            `new_pos` (and the camera position is updated accordingly).
 *          - If there IS a collision with the direct move, it calls
 *            `try_slide_movement` to see if moving only horizontally or only
 *            vertically from `old_pos` towards `new_pos` is possible. If
 *            sliding succeeds, the position is updated by the helper function.
 *          - If both the direct move and sliding attempts fail, the player's
 *            position remains unchanged at `old_pos`.
 *
 * @param game Pointer to the main game structure. Will be modified if a valid
 *             move is found.
 * @param old_pos The player's current position before attempting the move.
 * @param new_pos The desired target position for the player.
 */
void	check_collision(t_game *game, t_vec2 old_pos, t_vec2 new_pos)
{
	if (!is_colliding(game, new_pos, INTERSECT_NONE))
		update_player_and_camera_pos(game, new_pos);
	else
		try_slide_movement(game, old_pos, new_pos);
}
