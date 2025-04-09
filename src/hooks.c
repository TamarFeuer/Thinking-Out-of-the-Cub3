#include "../inc/game.h"

bool is_colliding(t_game *game, t_pos new, int flag)
{
    t_pos new_tl = new;
	t_pos new_tr = {new.x + PLAYER_SIZE * CONST , new.y};
	t_pos new_bl = {new.x, new.y + PLAYER_SIZE * CONST };
	t_pos new_br = {new.x + PLAYER_SIZE * CONST -1, new.y + PLAYER_SIZE * CONST };
	
		if ((is_wall_hit(game, new_tl, flag))
		|| (is_wall_hit(game, new_tr, flag))
		||(is_wall_hit(game, new_bl,flag))
		||(is_wall_hit(game, new_br, flag)))
	{
	
		return true;
	}
	else
		return false;
}



// check if there is any collision
// if there is separate to vertical and horrizontal
void check_collision(t_game *game, t_pos old_pos, t_pos new_pos)
{
	if (is_colliding(game, new_pos, 99))
	{
		printf ("COLLIDING\n");
		//flag: vertical 1, horizontal 0
		// Try moving only in the horizontal direction
		t_pos temp_pos1, temp_pos2;
		temp_pos1.x = new_pos.x;
		temp_pos1.y = old_pos.y;
		temp_pos2.x = old_pos.x;
		temp_pos2.y = new_pos.y;
	
		if (is_wall_hit(game, temp_pos1, 99) && is_wall_hit(game, temp_pos2, 99))
		{
			printf("diagonal\n");
			return;
		}
		printf ("trying to move horrizontally\n");
		printf ("player is at x=%f y=%f\n", game->player.pos.x, game->player.pos.y);
		
		printf ("temp_pos.x is %f, temp_pos.y is %f\n", temp_pos1.x, temp_pos1.y);
		if (!is_colliding(game, temp_pos1, 99))
		//if(game->data->map[corner_block_index(game, temp_pos)] != '1')
		{
			game->camera_pos.x = temp_pos1.x; // Allow horizontal movement
			game->camera_pos.x = game->player.pos.x + PLAYER_SIZE * CONST / 2 - 1;
			printf ("Allowing to go to new x\n\n");
			return;
		}
		else
			printf ("no horizontal movement allowed\n\n");

		
		printf ("trying to move vertically\n");
		printf ("temp_pos.x is %f, temp_pos.y is %f\n", temp_pos2.x, temp_pos2.y);
		if (!is_colliding(game, temp_pos2, 99))
		{
			game->player.pos.y = temp_pos2.y; // Allow vertical movement
			game->camera_pos.y = game->player.pos.y + PLAYER_SIZE * CONST /2 - 1;
			printf("Allowing to go to new y\n\n");
			return;
		}
		else
			printf ("no vertical movement allowed\n\n");
		// No valid movement, stay in old position
		//game->player.p_pos = old_pos;
	}
	else
	{
		// No collision, update position
		game->player.pos = new_pos;
		game->camera_pos.x = game->player.pos.x + PLAYER_SIZE * CONST / 2 - 1;
		game->camera_pos.y = game->player.pos.y + PLAYER_SIZE * CONST /2- 1;
	}
}



static void check_keys_for_movement(t_game *game, mlx_key_data_t keydata)
{
	t_pos new;
	new.x = game->player.pos.x;
	new.y = game->player.pos.y;
	double new_angle = game->player.angle;
	double angle_size = M_PI / 100;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x += (cos(game->player.angle) * DISTANCE_PER_TURN);
		new.y -= (sin(game->player.angle) * DISTANCE_PER_TURN);
		//printf ("addition is %f\n", sin(game->player.angle) * DISTANCE_PER_TURN);
		//printf ("quad is %d\n", game->player.angle_quad);
		game->ray->direction = FORWARD;
	}
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x -= (cos(game->player.angle) * DISTANCE_PER_TURN);
		new.y += (sin(game->player.angle) * DISTANCE_PER_TURN);
		game->ray->direction = BACKWARD;
	}
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x -= (sin(game->player.angle) * DISTANCE_PER_TURN);
		new.y -= (cos(game->player.angle) * DISTANCE_PER_TURN);
		game->ray->direction = FORWARD;
	}
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x += (sin(game->player.angle) * DISTANCE_PER_TURN);
		new.y += (cos(game->player.angle) * DISTANCE_PER_TURN);
		game->ray->direction = BACKWARD;
		
	}

	// Boundary check for player movement
	if (new.x != game->player.pos.x || new.y != game->player.pos.y)
	{
		if (new.x < X_START)
			new.x = X_START;
		if (new.y < Y_START)
			new.y = Y_START;
		if (new.x > X_START + game->data->minimap_data.width - CONST)
			new.x = X_START + game->data->minimap_data.width - CONST;
		if (new.y > Y_START + game->data->minimap_data.height - CONST)
			new.y = Y_START + game->data->minimap_data.height - CONST;
		check_collision(game, game->player.pos, new);
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
