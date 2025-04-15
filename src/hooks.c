#include "../inc/game.h"

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

	angle_increment = PI / 100.0;
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
