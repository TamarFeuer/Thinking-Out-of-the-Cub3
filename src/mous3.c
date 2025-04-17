/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mous3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfeuer <tfeuer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:14:38 by tfeuer            #+#    #+#             */
/*   Updated: 2025/04/17 18:14:39 by tfeuer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static void	update_stats_display(t_game *game)
{
	if (game->stats)
		mlx_delete_image(game->mlx, game->stats);
	game->stats = NULL;
	if (game->is_mmap)
		print_stats(game);
}

/**
 * @brief Handles mouse movement callback for player view rotation.
 * @details This function is registered as an MLX cursor position callback.
 *          It calculates the horizontal change (`delta_x`) in the cursor's
 *          position since the last time the function was invoked. To achieve
 *          this, it uses a `static` variable (`last_x`) to retain the
 *          previous x-coordinate across calls.
 *
 *          Rotation only occurs if mouse interaction is active
 *          (`game->is_mouse_active`) and the absolute horizontal movement
 *          (`fabs(delta_x)`) exceeds a small threshold (1.0) to prevent
 *          jitter from minor movements.
 *
 *          If conditions are met, a new view angle is calculated based on
 *          `delta_x` and a sensitivity factor (`MOUSE_ANGLE_FACTOR`). The
 *          angle is then normalized to the range [0, 2*PI).
 *
 *          If the calculated angle differs from the player's current angle,
 *          the player's angle and corresponding angle quadrant are updated.
 *          The on-screen statistics display is also refreshed via the
 *          `update_stats_display` helper function.
 *
 *          Finally, `last_x` is updated with the current `xpos` to prepare
 *          for the next function call. The vertical position `ypos` is ignored.
 *
 * @param xpos Current horizontal cursor position (provided by MLX).
 * @param ypos Current vertical cursor position (provided by MLX, unused).
 * @param param Void pointer expected to be castable to `t_game *`.
 */
void	cursor_hook(double xpos, double ypos, void *param)
{
	t_game			*game;
	static double	last_x = -1.0;
	double			delta_x;
	double			new_angle;

	game = (t_game *)param;
	(void)ypos;
	if (last_x == -1.0)
		last_x = xpos;
	delta_x = xpos - last_x;
	if (game->is_mouse_active == false || fabs(delta_x) < 1.0)
	{
		last_x = xpos;
		return ;
	}
	new_angle = game->player.angle - (delta_x * MOUSE_SENSITIVITY);
	normalize_angle_to_2pi(&new_angle);
	if (new_angle != game->player.angle)
	{
		determine_quad(new_angle, &game->player.angle_quad);
		game->player.angle = new_angle;
		update_stats_display(game);
	}
	last_x = xpos;
}

void	mouse_action(mouse_key_t button, action_t action, \
	modifier_key_t mods, void *param)
{
	t_game	*game;

	(void)mods;
	game = (t_game *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		game->is_mouse_active ^= 1;
		if (!game->is_mouse_active)
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
		else
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	}
}
