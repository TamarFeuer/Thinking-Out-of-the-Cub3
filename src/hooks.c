#include "../inc/game.h"

bool is_diagonal_collision(t_game *game, t_pos new)
{
    t_pos new_tl = new;
	t_pos new_tr = {new.x + PLAYER_SIZE * CONST, new.y};
	t_pos new_bl = {new.x, new.y + PLAYER_SIZE * CONST};
	t_pos new_br = {new.x + PLAYER_SIZE * CONST, new.y + PLAYER_SIZE * CONST};
	t_pos check1;
	t_pos check2;

	// Check four diagonal corners
	if (game->player.angle_quad == 1)
	{
		// Top right of player
		check1.x = round(new_tr.x / CONST);
		check1.y = round((new_tr.y - 1) / CONST);
		check2.x = round((new_tr.x - 1) / CONST);
		check2.y = round(new_tr.y / CONST);
	}
	else if (game->player.angle_quad == 2)
	{
		// Top left of player
		check1.x = round(new_tl.x / CONST);
		check1.y = round((new_tl.y - 1) / CONST);
		check2.x = round((new_tl.x + 1) / CONST);
		check2.y = round(new_tl.y / CONST);
	}
	else if (game->player.angle_quad == 3)
	{
		// Bottom left of player
		check1.x = round(new_bl.x / CONST);
		check1.y = round((new_bl.y + 1) / CONST);
		check2.x = round((new_bl.x - 1) / CONST);
		check2.y = round(new_bl.y / CONST);
	}
	else if (game->player.angle_quad == 4)
	{
		// Bottom right of player
		check1.x = round(new_br.x / CONST);
		check1.y = round((new_br.y + 1) / CONST);
		check2.x = round((new_br.x + 1) / CONST);
		check2.y = round(new_br.y / CONST);
	}

	printf("check1 is x=%f, y=%f\n", check1.x, check1.y);
	printf("check2 is x=%f, y=%f\n", check2.x, check2.y);

	int index_horiz1 = get_block_index2(game, &check1, 0);
	int index_vert1 = get_block_index2(game, &check1, 1);
	int index_horiz2 = get_block_index2(game, &check2, 0);
	int index_vert2 = get_block_index2(game, &check2, 1);

	if ((game->data->map[index_horiz1] == '1' && game->data->map[index_vert1] == '1')
		&& (game->data->map[index_horiz2] == '1' && game->data->map[index_vert2] == '1'))
	{
		printf("Diagonal collision!\n");
		return true;
	}
	return false;
}


bool is_horiz_collision(t_game *game, t_pos new)
{
	t_pos	new_tl = new;
	t_pos	new_tr = {new.x + PLAYER_SIZE * CONST, new.y};
	t_pos	new_bl = {new.x, new.y + PLAYER_SIZE * CONST};
	t_pos	new_br = {new.x + PLAYER_SIZE * CONST, new.y + PLAYER_SIZE * CONST};
	
	if ((game->data->map[get_block_index2(game, &new_tl, 1)] == '1') || (game->data->map[get_block_index2(game, &new_tr, 1)] == '1')
		|| (game->data->map[get_block_index2(game, &new_bl, 1)] == '1') || (game->data->map[get_block_index2(game, &new_br, 1)] == '1'))
		{
			if ((game->data->map[get_block_index2(game, &new_tl, 1)] == '1' && game->data->map[get_block_index2(game, &new_tr, 1)] == '1')
			|| (game->data->map[get_block_index2(game, &new_bl, 1)] == '1' && game->data->map[get_block_index2(game, &new_br, 1)] == '1'))
			{
				printf("horizontal collision!\n");
				return (true);
			}
		}
	return (false);
}

bool is_vertical_collision(t_game *game, t_pos new)
{
	t_pos	new_tl = new;
	t_pos	new_tr = {new.x + PLAYER_SIZE * CONST, new.y};
	t_pos	new_bl = {new.x, new.y + PLAYER_SIZE * CONST};
	t_pos	new_br = {new.x + PLAYER_SIZE * CONST, new.y + PLAYER_SIZE * CONST};

	if ((game->data->map[get_block_index2(game, &new_tl, 0)] == '1') || (game->data->map[get_block_index2(game, &new_tr, 0)] == '1')
		|| (game->data->map[get_block_index2(game, &new_bl, 0)] == '1') || (game->data->map[get_block_index2(game, &new_br, 0)] == '1'))
		{
			if ((game->data->map[get_block_index2(game, &new_tl, 0)] == '1' && game->data->map[get_block_index2(game, &new_bl, 0)] == '1')
			|| (game->data->map[get_block_index2(game, &new_tr, 0)] == '1' && game->data->map[get_block_index2(game, &new_br, 0)] == '1'))
			{
				printf("vertical collision!\n");
				return (true);
			}
		}
	return (false);
}


void check_collision(t_game *game, t_pos *new_pos) 
{
    // Check for collisions in all directions
    bool horiz_collision = is_horiz_collision(game, *new_pos);  // Check horizontal collision
    bool vert_collision = is_vertical_collision(game, *new_pos);  // Check vertical collision
    bool diag_collision = is_diagonal_collision(game, *new_pos);  // Check diagonal collision

    // Handle movement based on the type of collision
    if (!diag_collision) 
	{

        // If there's no horizontal collision, the player can move vertically (up or down)
        if (!horiz_collision) 
		{
            game->player.p_pos.y = round(new_pos->y);  // Move player vertically
        }

        // If there's no vertical collision, the player can move horizontally (left or right)
        if (!vert_collision) 
		{
            game->player.p_pos.x = round(new_pos->x);  // Move player horizontally
        }
    }

    // Update the camera position based on the player's new position
    game->camera.pos.x = round(game->player.p_pos.x + (PLAYER_SIZE + CONST) / 2);
    game->camera.pos.y = round(game->player.p_pos.y + (PLAYER_SIZE + CONST) / 2);
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
		check_collision(game, &new);
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
