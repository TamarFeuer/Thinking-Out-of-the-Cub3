#include "../inc/game.h"

// bool is_collision(t_game *game, t_pos new, int *x_offset, int *y_offset)
// {
// 	int range = PLAYER_SIZE - 1;

// 	while (*y_offset <= range)
// 	{
// 		*x_offset = 0;
// 		while (*x_offset <= range)
// 		{
// 			// Check the position (x + x_offset, y + y_offset)
// 			t_pos check_pos = {new.x + *x_offset, new.y + *y_offset};
// 			//if (game->mapdata[get_block_index(&check_pos)] == '1')
// 			if (game->mapdata[get_block_index(game, &check_pos, 999)] == '1')  //consider ceiling in the right places
// 				return true;
// 			(*x_offset)++;
// 		}
// 		(*y_offset)++;
// 	}
// 	return false;
// }

bool is_collision(t_game *game, t_pos new, t_player *player)
{
    int range = PLAYER_SIZE * CONST - 1;
    int x_offset = 0;
    int y_offset = 0;

    // Set offsets based on quadrant
    if (player->angle_quad == 1) 
	{  // Right-Top
        x_offset = range;  // Check right
        y_offset = 0;      // Check top
    } 
    else if (player->angle_quad == 2) 
	{  // Left-Top
        x_offset = 0;      // Check left
        y_offset = 0;      // Check top
    } 
    else if (player->angle_quad == 3) 
	{  // Left-Bottom
        x_offset = 0;      // Check left
        y_offset = range;  // Check bottom
    } 
    else if (player->angle_quad == 4) {
		  // Right-Bottom
        x_offset = range;  // Check right
        y_offset = range;  // Check bottom
    }

    // Check horizontal collision (left or right edge)
	int i = 0;
    while(i <= range) 
	{
        t_pos check_x = {new.x + x_offset, new.y + i};
        if (game->data->map[get_block_index(game, &check_x, 0)] == '1')
            return true;
		i++;
    }

    // Check vertical collision (top or bottom edge)
	i = 0;
    while (i <= range) 
	{
        t_pos check_y = {new.x + i, new.y + y_offset};
        if (game->data->map[get_block_index(game, &check_y, 1)] == '1')
            return true;
		i++;
    }

    return false;
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
		int x_offset = 0;
		int y_offset = 0;

		if (is_collision(game, new, &(game->player)))
		{	
			printf ("Collision! x_offset %d y_offest %d\n", x_offset, y_offset);
			printf ("sin(game->player.angle) %f, cos(game->player.angle) %f\n", sin(game->player.angle), cos(game->player.angle));
		}
		else
		{
			game->player.p_pos.x = round(new.x);
			game->player.p_pos.y = round(new.y);
			game->camera.pos.x = round(game->player.p_pos.x + CONST /2);
			game->camera.pos.y = round(game->player.p_pos.y + CONST /2);
			mlx_delete_image(game->mlx, game->stats);
			if (game->is_mmap)
				print_stats(game);

		}
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
		mlx_delete_image(game->mlx, game->stats);
		if (game->is_mmap)
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
		clean_nicely(game, NULL);
	}
	check_keys_for_movement(game, keydata);
}
