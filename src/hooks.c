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
 *          `game->camera_pos` based on the new player position and predefined
 *          offsets (`CAMERA_OFFSET_X`, `CAMERA_OFFSET_Y`).
 *
 * @param game Pointer to the main game structure.
 * @param new_valid_pos The new, collision-free position for the player.
 */
static void	update_player_and_camera_pos(t_game *game, t_vec2 new_valid_pos)
{
	game->player.pos = new_valid_pos;
	game->camera_pos.x = game->player.pos.x + CAMERA_OFFSET_X;
	game->camera_pos.y = game->player.pos.y + CAMERA_OFFSET_Y;
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

/**
 * @brief Calculates the desired change in player position based on WASD keys.
 * @details Checks if WASD keys are active (pressed or held). If so, calculates
 *          the potential change in x and y coordinates based on the player's
 *          current angle and movement speed (`DISTANCE_PER_TURN`). Updates the
 *          `new_pos` vector passed by reference.
 *
 * @param game Pointer to the main game structure (for player angle).
 * @param keydata Structure containing key and action data.
 * @param key_is_active Boolean indicating if the key action is PRESS or REPEAT.
 * @param new_pos Pointer to the `t_vec2` structure where the calculated new
 *                position (relative to the current) will be stored.
 * @note This function directly modifies the `new_pos` passed to it.
 */
static void	handle_movement_keys(t_game *game, mlx_key_data_t keydata,
	bool key_is_active, t_vec2 *new_pos)
{
	double	move_dx;
	double	move_dy;

	move_dx = cos(game->player.angle) * DISTANCE_PER_TURN;
	move_dy = sin(game->player.angle) * DISTANCE_PER_TURN;
	if (key_is_active && keydata.key == MLX_KEY_W)
	{
		new_pos->x += move_dx;
		new_pos->y -= move_dy;
	}
	else if (key_is_active && keydata.key == MLX_KEY_S)
	{
		new_pos->x -= move_dx;
		new_pos->y += move_dy;
	}
	else if (key_is_active && keydata.key == MLX_KEY_A)
	{
		new_pos->x -= move_dy;
		new_pos->y -= move_dx;
	}
	else if (key_is_active && keydata.key == MLX_KEY_D)
	{
		new_pos->x += move_dy;
		new_pos->y += move_dx;
	}
}

/**
* @brief Calculates the desired change in player angle based on arrow keys.
* @details Checks if Left/Right arrow keys are active (pressed or held) and if
*          mouse rotation is inactive. If conditions met, updates the potential
*          new angle passed by reference.
*
* @param game Pointer to the main game structure (for mouse active status).
* @param keydata Structure containing key and action data.
* @param key_is_active Boolean indicating if the key action is PRESS or REPEAT.
* @param new_angle Pointer to the double where the calculated new angle will
*                  be stored.
* @note This function directly modifies the `new_angle` passed to it.
*/
static void	handle_rotation_keys(t_game *game, mlx_key_data_t keydata,
	bool key_is_active, double *new_angle)
{
	double	angle_increment;

	angle_increment = M_PI / 100.0;
	if (!game->is_mouse_active && key_is_active)
	{
		if (keydata.key == MLX_KEY_RIGHT)
			*new_angle -= angle_increment;
		else if (keydata.key == MLX_KEY_LEFT)
			*new_angle += angle_increment;
	}
}

/**
 * @brief Clamps the player's intended world position to stay within map limits.
 * @details Adjusts the x and y components of the player's potential position
 *          vector (`pos`) to ensure the player's bounding box does not go
 *          outside the valid map area. The minimum boundary is (0, 0). The
 *          maximum boundary is calculated based on map dimensions in cells
 *          (`map_data.cols`, `map_data.rows`), cell size (`game->cell_size`),
 *          and player size (`PLAYER_SIZE`). This prevents the player from
 *          moving outside the playable world grid.
 *
 * @param game Pointer to the main game structure (for map dims, cell size).
 * @param pos Pointer to the `t_vec2` position vector (player's top-left corner)
 *            to be clamped. Represents world coordinates.
 *
 * @note Modifies the `pos` vector directly. Uses world coordinates and
 *       boundaries, NOT minimap pixel dimensions. Assumes PLAYER_SIZE
 *       represents the player's width and height.
 */
static void	clamp_player_position_to_world(t_game *game, t_vec2 *pos)
{
	double	max_x;
	double	max_y;

	max_x = (double)game->data->map_data.cols * game->cell_size - PLAYER_SIZE;
	max_y = (double)game->data->map_data.rows * game->cell_size - PLAYER_SIZE;
	if (pos->x < 0.0)
		pos->x = 0.0;
	else if (pos->x > max_x)
		pos->x = max_x;
	if (pos->y < 0.0)
		pos->y = 0.0;
	else if (pos->y > max_y)
		pos->y = max_y;
}

/**
* @brief Processes key presses/holds for player movement and rotation.
* @details Checks for WASD movement and Left/Right arrow key rotation based on
*          the provided `keydata`. Calculates potential new position and angle.
*          If the potential position changed, clamps it to map boundaries and
*          performs collision detection using `check_collision`, potentially
*          updating the player's position. If the potential angle changed,
*          normalizes it and updates the player's angle and quadrant.
*
* @param game Pointer to the main game structure, whose player state may be
*             modified.
* @param keydata The key event data provided by MLX42's key hook.
*/
void	check_keys_for_movement(t_game *game, mlx_key_data_t keydata)
{
	t_vec2	new_pos;
	double	new_angle;
	bool	key_is_active;
	t_vec2	old_pos;

	new_pos = game->player.pos;
	new_angle = game->player.angle;
	old_pos = game->player.pos;
	key_is_active = (keydata.action == MLX_PRESS || \
		keydata.action == MLX_REPEAT);
	handle_movement_keys(game, keydata, key_is_active, &new_pos);
	handle_rotation_keys(game, keydata, key_is_active, &new_angle);
	if (new_pos.x != old_pos.x || new_pos.y != old_pos.y)
	{
		clamp_player_position_to_world(game, &new_pos);
		check_collision(game, old_pos, new_pos);
	}
	if (new_angle != game->player.angle)
	{
		normalize_angle_to_2pi(&new_angle);
		game->player.angle = new_angle;
		determine_quad(game->player.angle, &game->player.angle_quad);
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		printf("Player pressed ESC. Closing the game...\n");
		mlx_close_window(game->mlx);
		clean_nicely(game, NULL);
	}
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		printf("Player pressed M. toggling mmap...\n");
		game->is_mmap ^= 1;
		if (game->is_mmap == false)
		{
			game->mini->enabled = false;
			game->stats->enabled = false;
		}
		else
		{
			draw_mmap(game);
			game->mini->enabled = true;
		}
	}
	check_keys_for_movement(game, keydata);
}
