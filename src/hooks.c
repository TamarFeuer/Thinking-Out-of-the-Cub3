#include "../inc/game.h"

bool is_vertical_collision(t_game *game, t_pos new, t_player player)
{
	int x_offset = 0;

	
	if (player.angle_quad == 1 || player.angle_quad == 4) 
		x_offset = PLAYER_SIZE; //2 * PLAYER_SIZE + 1;  // Check right side
	else
		x_offset = 0;  // Check left side
	int i = 0;
	while (i <= PLAYER_SIZE)
	{
		t_pos check_x = {new.x + x_offset, new.y + i};
		if (game->data->map[get_block_index2(game, &check_x, 1)] == '1') 
		{
			printf("vertical collision!\n");
			return (true);
		}
		i++;
	}
	return (false);
}

bool is_horiz_collision(t_game *game, t_pos new, t_player player)
{
	int y_offset = 0;

	
	if (player.angle_quad == 3 || player.angle_quad == 4)
		y_offset = PLAYER_SIZE; //2 * PLAYER_SIZE + 1;  // Check bottom side
	else 
		y_offset = 0;  // Check top side
	int i = 0;
	printf ("player: %f, %f\n", game->player.p_pos.x, game->player.p_pos.y);
   	while (i <= PLAYER_SIZE)
	{
		t_pos check_y = {new.x + i, new.y + y_offset};
		printf ("horiz: check y: %f, %f\n", new.x + i, new.y + y_offset);
		if (game->data->map[get_block_index2(game, &check_y, 0)] == '1')
		{
			printf("horizontal collision!\n");
			return (true);
		}
		i++;
	}
	printf ("\n");
	return (false);
}


static void check_keys_for_movement(t_game *game, mlx_key_data_t keydata)
{
	t_pos new;
	new.x = game->player.p_pos.x;
	new.y = game->player.p_pos.y;
	double new_angle = game->player.angle;
	double angle_size = 2 * M_PI / 100;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x += round(cos(game->player.angle) * DISTANCE_PER_TURN);
		new.y -= round(sin(game->player.angle) * DISTANCE_PER_TURN);
	}
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x -= round(cos(game->player.angle) * DISTANCE_PER_TURN);
		new.y += round(sin(game->player.angle) * DISTANCE_PER_TURN);
	}
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x -= round(sin(game->player.angle) * DISTANCE_PER_TURN);
		new.y -= round(cos(game->player.angle) * DISTANCE_PER_TURN);
	}
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x += round(sin(game->player.angle) * DISTANCE_PER_TURN);
		new.y += round(cos(game->player.angle) * DISTANCE_PER_TURN);
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
		// int x_offset = 0;
		// int y_offset = 0;

		// if (is_collision(game, new, &(game->player)))
		// {	
		// 	printf ("Collision! x_offset %d y_offest %d\n", x_offset, y_offset);
		// 	printf ("sin(game->player.angle) %f, cos(game->player.angle) %f\n", round(sin(game->player.angle) * DISTANCE_PER_TURN), round(cos(game->player.angle) * DISTANCE_PER_TURN));
		// }
		// else
		// {
		if (!is_horiz_collision(game, new, game->player))
		{
			game->player.p_pos.y = round(new.y);
			//game->camera.pos.y = round(game->player.p_pos.y + CONST /2);
			game->camera.pos.y = round(game->player.p_pos.y + (PLAYER_SIZE + CONST) /2);
	
		}
		// else
		// {
		// 	printf ("Collision! x_offset %d y_offest %d\n", x_offset, y_offset);
		// 	printf ("sin(game->player.angle) %f, cos(game->player.angle) %f\n", round(sin(game->player.angle) * DISTANCE_PER_TURN), round(cos(game->player.angle) * DISTANCE_PER_TURN));
		// }
		if (!is_vertical_collision(game, new, game->player))
		{
			game->player.p_pos.x = round(new.x);
			//game->camera.pos.x = round(game->player.p_pos.x + CONST /2);
			game->camera.pos.x = round(game->player.p_pos.x + (PLAYER_SIZE + CONST) /2);
		}
		// else
		// {
		// 	printf ("Collision! x_offset %d y_offest %d\n", x_offset, y_offset);
		// 	printf ("sin(game->player.angle) %f, cos(game->player.angle) %f\n", round(sin(game->player.angle) * DISTANCE_PER_TURN), round(cos(game->player.angle) * DISTANCE_PER_TURN));
		// }
	}
	if (game->is_mouse_active == false &&(keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
		new_angle -= angle_size; // Rotate clockwise (right)
	if ( game->is_mouse_active == false && (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
		new_angle += angle_size; // Rotate counterclockwise (left)
	//printf ("in check for movement\n");
	normalize_angle_to_2pi(&new_angle);
	if (new_angle != game->player.angle)
	{
		determine_quad(new_angle, &game->player.angle_quad);
		game->player.angle = new_angle;
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
	check_keys_for_movement(game, keydata);
}
