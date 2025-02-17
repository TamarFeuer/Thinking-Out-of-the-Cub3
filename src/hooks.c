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
			//if (game->mapdata[get_block_index(&check_pos)] == '1')
			if (game->mapdata[get_block_index2(game, &check_pos, 999)] == '1')  //consider ceiling in the right places
				return true;
			(*x_offset)++;
		}
		(*y_offset)++;
	}
	return false;
}

void check_keys_for_movement(t_game *game)
{
	t_pos new;
	new.x = game->player.p_pos.x;
	new.y = game->player.p_pos.y;
	double new_angle = game->player.angle;
	double angle_size = 2 * M_PI / 100;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		new.x += cos(game->player.angle) * DISTANCE_PER_TURN;
		new.y -= sin(game->player.angle) * DISTANCE_PER_TURN;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		new.x -= cos(game->player.angle) * DISTANCE_PER_TURN;
		new.y += sin(game->player.angle) * DISTANCE_PER_TURN;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		new.x -= sin(game->player.angle) * DISTANCE_PER_TURN;
		new.y -= cos(game->player.angle) * DISTANCE_PER_TURN;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		new.x += sin(game->player.angle) * DISTANCE_PER_TURN;
		new.y += cos(game->player.angle) * DISTANCE_PER_TURN;
	}

	// Boundary check for player movement
	if (new.x != game->player.p_pos.x || new.y != game->player.p_pos.y)
	{
		if (new.x < X_START)
			new.x = X_START;
		if (new.y < Y_START)
			new.y = Y_START;
		if (new.x > X_START + game->data->minimap_data.width - CONST)
			new.x = X_START + game->data->minimap_data.width - CONST;
		if (new.y > Y_START + game->data->minimap_data.height - CONST)
			new.y = Y_START + game->data->minimap_data.height - CONST;
		int x_offset = 0;
		int y_offset = 0;

		if (is_collision(game, new, &x_offset, &y_offset))
		{	
			printf ("Collision! x_offset %d y_offest %d\n", x_offset, y_offset);
			printf ("sin(game->player.angle) %f, cos(game->player.angle) %f\n", sin(game->player.angle), cos(game->player.angle));
		}
		else
		{
			game->player.p_pos.x = round(new.x);
			game->player.p_pos.y = round(new.y);
			game->camera.pos.x = game->player.p_pos.x + CONST /2;
			game->camera.pos.y = game->player.p_pos.y + CONST /2;
			mlx_delete_image(game->mlx, game->stats);
			if (game->is_mmap)
				print_stats(game);

		}
	}

	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		new_angle -= angle_size; // Rotate clockwise (right)
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		new_angle += angle_size; // Rotate counterclockwise (left)
	if (new_angle >= 2 * M_PI)
			new_angle -= 2 * M_PI;
	if (new_angle < 0)
			new_angle += 2 * M_PI;
	if (new_angle != game->player.angle)
	{
		determine_quad(new_angle, &game->player.angle_quad);
		game->player.angle = new_angle;
		mlx_delete_image(game->mlx, game->stats);
		if (game->is_mmap)
			print_stats(game);

	}
}

// void	key_hook(mlx_key_data_t keydata, void *param)
// {
// 	t_game	*game;
// 	game = param;
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
// 	{
// 		printf("Player pressed ESC. Closing the game...\n");
// 		mlx_close_window(game->mlx);
// 		clean_nicely(game, NULL);
// 	}
// 	check_keys_for_movement(game, keydata);
// }
