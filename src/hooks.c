#include "../inc/game.h"

static void check_keys_for_movement(t_game *game, mlx_key_data_t keydata)
{
	float new_x = game->player.x;
	float new_y = game->player.y;
	double new_angle = game->player.angle;
	double angle_size = 2 * M_PI / 100;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new_x += cos(game->player.angle) * DISTANCE_PER_TURN;
		new_y += sin(game->player.angle) * DISTANCE_PER_TURN;
	}
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new_x -= cos(game->player.angle) * DISTANCE_PER_TURN;
		new_y -= sin(game->player.angle) * DISTANCE_PER_TURN;
	}
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new_x += sin(game->player.angle) * DISTANCE_PER_TURN;
		new_y -= cos(game->player.angle) * DISTANCE_PER_TURN;
	}
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new_x -= sin(game->player.angle) * DISTANCE_PER_TURN;
		new_y += cos(game->player.angle) * DISTANCE_PER_TURN;
	}

	// Boundary check for player movement
	if (new_x != game->player.x || new_y != game->player.y)
	{
		if (new_x < X_START)
			new_x = X_START;
		if (new_y < Y_START)
			new_y = Y_START;
		if (new_x > X_START + MAP_WIDTH - CONST)
			new_x = X_START + MAP_WIDTH - CONST;
		if (new_y > Y_START + MAP_HEIGHT - CONST)
			new_y = Y_START + MAP_HEIGHT - CONST;
		game->player.x = new_x;
		game->player.y = new_y;
		draw_player(game);
		cast_rays(game);
		print_stats(game);
	}

	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		new_angle += angle_size; // Rotate clockwise (right)
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		new_angle -= angle_size; // Rotate counterclockwise (left)
	if (new_angle >= 2 * M_PI)
			new_angle -= 2 * M_PI;
	if (new_angle < 0)
			new_angle += 2 * M_PI;
	if (new_angle != game->player.angle)
	{
		game->player.angle = new_angle;
		cast_rays(game);
		print_stats(game);
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
		clean_nicely(game);
		exit (EXIT_SUCCESS);
	}
	check_keys_for_movement(game, keydata);
}