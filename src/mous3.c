#include "../inc/game.h"

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_game			*game;
	static float	last_x = -1;
	double			new_angle;
	double			angle_size;
	double			speed_factor;
	double			delta_x;

	game = (t_game *)param;
	(void)ypos;
	angle_size = 2 * M_PI / 100;
	delta_x = fabs(xpos - last_x);
	speed_factor = delta_x * MOUSE_SENSITIVITY;
	if (delta_x < 1.0)
		return ;
	new_angle = game->player.angle;
	if (last_x != -1 && last_x != xpos && game->is_mouse_active == true)
	{
		if ((xpos - last_x) > 0)
			new_angle -= angle_size * speed_factor;
		else
			new_angle += angle_size * speed_factor;
		normalize_angle_to_2pi(&new_angle);
		if (new_angle != game->player.angle)
		{
			determine_quad(new_angle, &game->player.angle_quad);
			game->player.angle = new_angle;
			mlx_delete_image(game->mlx, game->stats);
			if (game->is_mmap)
				print_stats(game);
		}
	}
	last_x = xpos;
}

void	mouse_action(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
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
