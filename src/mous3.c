#include "../inc/game.h"


void cursor_hook(double xpos, double ypos, void* param)
{
	t_game *game;
	
	game = (t_game *)param;
	
	(void)ypos;
	static float last_x = -1;
	// static float last_y = -1;
	double new_angle;
	double angle_size = 2 * M_PI / 100;
	double delta_x = fabs(xpos - last_x);
	
	double speed_factor = delta_x * MOUSE_SENSITIVITY;
	printf ("speed_factor is %f\n", speed_factor);
	if (delta_x < 1.0)  // Dead zone threshold, adjust as necessary
    	return;

	new_angle = game->player.angle;
	
	if (last_x != -1  && last_x != xpos)
	{
		//mlx_get_mouse_pos(game->mlx, x, y);
		// mlx_set_mouse_pos(game->mlx, x, y);
		if ((xpos - last_x) > 0)
			new_angle -= angle_size * speed_factor;   //radians per frame
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
		mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);  //to do: handle resize window
	}
	last_x = xpos;
}

void mouse_action (mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_game *game;
	
	(void)mods;
	game = (t_game *)param;
	
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		printf ("left button pressed\n");
		game->is_mouse_active ^= 1;
		if (!game->is_mouse_active)
		{
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
			printf ("mouse inactive, we should see a cursor\n");
		}
		else
		{
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
			printf ("mouse active, we shouldn't see a cursor\n");
		}
	}
	
}