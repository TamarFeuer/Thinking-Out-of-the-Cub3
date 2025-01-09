#include "../inc/game.h"

bool is_collision(t_game *game, t_pos new, int *x_offset, int *y_offset)
{
	int range = CONST - 1;

	while (*y_offset <= range)
	{
		*x_offset = 0;
		while (*x_offset <= range)
		{
			// Check the position (x + x_offset, y + y_offset)
			t_pos check_pos = {new.x + *x_offset, new.y + *y_offset};
			if (game->mapdata[get_block_index(&check_pos)] == 1)
				return true;
			(*x_offset)++;
		}
		(*y_offset)++;
	}
	return false;
}

static void check_keys_for_movement(t_game *game, mlx_key_data_t keydata)
{
	t_pos new;
	new.x = game->player.x;
	new.y = game->player.y;
	double new_angle = game->player.angle;
	double angle_size = 2 * M_PI / 100;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x += cos(game->player.angle) * DISTANCE_PER_TURN;
		new.y -= sin(game->player.angle) * DISTANCE_PER_TURN;
	}
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x -= cos(game->player.angle) * DISTANCE_PER_TURN;
		new.y += sin(game->player.angle) * DISTANCE_PER_TURN;
	}
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x -= sin(game->player.angle) * DISTANCE_PER_TURN;
		new.y -= cos(game->player.angle) * DISTANCE_PER_TURN;
	}
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x += sin(game->player.angle) * DISTANCE_PER_TURN;
		new.y += cos(game->player.angle) * DISTANCE_PER_TURN;
	}

	// Boundary check for player movement
	if (new.x != game->player.x || new.y != game->player.y)
	{
		if (new.x < X_START)
			new.x = X_START;
		if (new.y < Y_START)
			new.y = Y_START;
		if (new.x > X_START + MAP_WIDTH - CONST)
			new.x = X_START + MAP_WIDTH - CONST;
		if (new.y > Y_START + MAP_HEIGHT - CONST)
			new.y = Y_START + MAP_HEIGHT - CONST;
		int x_offset = 0;
		int y_offset = 0;

		if (is_collision(game, new, &x_offset, &y_offset))
		{	
			printf ("Collision! x_offset %d y_offest %d\n", x_offset, y_offset);
			printf ("sin(game->player.angle) %f, cos(game->player.angle) %f\n", sin(game->player.angle), cos(game->player.angle));
		}
		else
		{
			game->player.x = new.x;
			game->player.y = new.y;
			draw_player(game);
			cast_rays(game);
			print_stats(game);
		}
	}

	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		new_angle -= angle_size; // Rotate clockwise (right)
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		new_angle += angle_size; // Rotate counterclockwise (left)
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