#include "../inc/game.h"

// bool is_diagonal_collision(t_game *game, t_pos new)
// {
//     t_pos new_tl = new;
// 	t_pos new_tr = {new.x + PLAYER_SIZE * CONST, new.y};
// 	t_pos new_bl = {new.x, new.y + PLAYER_SIZE * CONST};
// 	t_pos new_br = {new.x + PLAYER_SIZE * CONST, new.y + PLAYER_SIZE * CONST};
	
// 	if (game->player.angle_quad == 1 || game->player.angle_quad == 3)
// 	{
		
// 		if ((game->data->map[get_block_index2(game, &new_tl, 1).index] == '1') && (game->data->map[get_block_index2(game, &new_br, 1).index] == '1'))
// 		{
// 			//printf ("quad 1 or 3 diagonal collision\n");
// 			return true;
// 		}
// 		else
// 			return false;
// 	}
// 	else if (game->player.angle_quad == 2 || game->player.angle_quad == 4)
// 	{
		
// 		if ((game->data->map[get_block_index2(game, &new_bl, 1).index] == '1') && (game->data->map[get_block_index2(game, &new_tr, 1).index] == '1'))
// 		{
// 			//printf ("quad 2 or 4 diagonal collision\n");
// 			return true;
// 		}
// 		else
// 			return false;
// 	}
// 	return false;
// }


// bool is_horiz_collision(t_game *game, t_pos new)
// {
// 	t_pos	new_tl = new;
// 	t_pos	new_tr = {new.x + PLAYER_SIZE * CONST, new.y};
// 	t_pos	new_bl = {new.x, new.y + PLAYER_SIZE * CONST};
// 	t_pos	new_br = {new.x + PLAYER_SIZE * CONST, new.y + PLAYER_SIZE * CONST};
	
// 	if (game->ray->direction == FORWARD)
// 	{
// 		if (((game->player.angle_quad == 1 || game->player.angle_quad == 2) && (is_wall_hit(game, new_tl, 1) && is_wall_hit(game, new_tr, 1)))
// 			|| ((game->player.angle_quad == 3 || game->player.angle_quad == 4) && (is_wall_hit(game, new_bl, 1) && is_wall_hit(game, new_br, 1))))
// 			{
// 				printf("horizontal collision!\n");
// 				return (true);
// 			}
// 	}
// 	else if (game->ray->direction == BACKWARD)
// 	{
// 		if (((game->player.angle_quad == 3 || game->player.angle_quad == 4) && (is_wall_hit(game, new_tl, 1) && is_wall_hit(game, new_tr, 1)))
// 			|| ((game->player.angle_quad == 1 || game->player.angle_quad == 2) && (is_wall_hit(game, new_bl, 1) && is_wall_hit(game, new_br, 1))))
// 			{
// 				printf("horizontal collision!\n");
// 				return (true);
// 			}
// 	}
// 	return (false);
// }

// bool is_vertical_collision(t_game *game, t_pos new)
// {
// 	t_pos	new_tl = new;
// 	t_pos	new_tr = {new.x + PLAYER_SIZE * CONST, new.y};
// 	t_pos	new_bl = {new.x, new.y + PLAYER_SIZE * CONST};
// 	t_pos	new_br = {new.x + PLAYER_SIZE * CONST, new.y + PLAYER_SIZE * CONST};

// 	if (game->ray->direction == FORWARD)
// 	{
// 		if ((((game->player.angle_quad == 2) || (game->player.angle_quad == 3)) && (game->data->map[get_block_index2(game, &new_tl, 0).index] == '1') && (game->data->map[get_block_index2(game, &new_bl, 0).index] == '1'))
// 			|| (((game->player.angle_quad == 1) || (game->player.angle_quad == 4)) && (game->data->map[get_block_index2(game, &new_tr, 0).index] == '1') && (game->data->map[get_block_index2(game, &new_br, 0).index] == '1')))
		
// 			{
// 				printf("vertical collision!\n");
// 				return (true);
// 			}
// 	}
// 	else if (game->ray->direction == BACKWARD)
// 	{
// 		if ((((game->player.angle_quad == 1) || (game->player.angle_quad == 4)) && (game->data->map[get_block_index2(game, &new_tl, 0).index] == '1') && (game->data->map[get_block_index2(game, &new_bl, 0).index] == '1'))
// 			|| (((game->player.angle_quad == 2) || (game->player.angle_quad == 3)) && (game->data->map[get_block_index2(game, &new_tr, 0).index] == '1') && (game->data->map[get_block_index2(game, &new_br, 0).index] == '1')))
// 			{
// 				printf("vertical collision!\n");
// 				return (true);
// 			}
	
// 	}
// 	return (false);
// }


// void check_collision(t_game *game, t_pos *new_pos) 
// {
//     // Check for collisions in all directions
//     bool horiz_collision = is_horiz_collision(game, *new_pos);  // Check horizontal collision
//     bool vert_collision = is_vertical_collision(game, *new_pos);  // Check vertical collision
//     bool diag_collision = is_diagonal_collision(game, *new_pos);  // Check diagonal collision


// 	if (diag_collision)
// 		return;
// 	printf ("direction is %d\n", game->ray->direction);
// 	//printf ("y value of new pos is %f\n", (*new_pos).y);

//         // If there's no horizontal collision, the player can move vertically (up or down)
//         if (!horiz_collision) 
// 		{
//             game->player.p_pos.y = (new_pos->y);  // Move player vertically
// 			//printf ("new player pos is y = %f\n", new_pos->y);
// 			game->camera.pos.y = (game->player.p_pos.y + (PLAYER_SIZE + CONST) / 2);
//         }

//         // If there's no vertical collision, the player can move horizontally (left or right)
//         if (!vert_collision) 
// 		{
//            game->player.p_pos.x = (new_pos->x);  // Move player horizontally
// 			game->camera.pos.x = (game->player.p_pos.x + (PLAYER_SIZE + CONST) / 2);
// 			//printf ("new player.pos is x=%f y=%f\n", game->player.p_pos.x, game->player.p_pos.y);
//     }
// }

//-----------------------------------------------------
// void check_collision(t_game *game, t_pos new_pos)
// {
//     t_block_index block_x, block_y;

//     // Define positions for each corner based on the movement direction
//     t_pos check_x, check_y;

//     // When moving horizontally (left or right)
//     if (new_pos.x != game->player.p_pos.x) 
// 	{
//         // Check the left or right corners based on movement direction
//         if (new_pos.x > game->player.p_pos.x) 
// 		{ 
// 			//printf ("moving right\n");
//             check_x = (t_pos){new_pos.x + CONST * PLAYER_SIZE, game->player.p_pos.y + CONST * PLAYER_SIZE};  // Right bottom corner
//         } 
// 		else 
// 		{ 
// 			//printf ("moving left\n");
//             check_x = (t_pos){new_pos.x , game->player.p_pos.y};  // Left bottom corner
//         }
//         block_x = get_block_index2(game, &check_x, 0); // flag = 0 for horizontal
//     }

//     // When moving vertically (up or down)
//     if (new_pos.y != game->player.p_pos.y) 
// 	{
//         // Check the top or bottom corners based on movement direction
//         if (new_pos.y > game->player.p_pos.y) 
// 		{ 
// 			//printf ("moving down\n");
//             check_y = (t_pos){game->player.p_pos.x, new_pos.y + PLAYER_SIZE * CONST};  // Bottom left corner  --- add botton right
//         } 
// 		else 
// 		{ 
// 			//printf ("moving up\n");
//             check_y = (t_pos){game->player.p_pos.x, new_pos.y };  // Top left corner   
//         }
//         block_y = get_block_index2(game, &check_y, 1); // flag = 1 for vertical
//     }

//     // Check for collisions
//     if (game->data->map[block_y.index] == '1' && game->data->map[block_x.index] == '1') 
// 	{
//         printf("Diagonal collision detected!\n");
// 		printf ("new is x=%f y=%f\n", new_pos.x, new_pos.y);
//         return;
//     }

//     // Check horizontal movement (X direction)
//     if (game->data->map[block_x.index] == '1' && game->data->map[block_y.index] != '1') 
// 	{
//         printf("Collision in X direction, block movement in x\n");

//     }
//     else 
// 	{
//         game->player.p_pos.x = new_pos.x;  // Move player horizontally
//         game->camera.pos.x = (game->player.p_pos.x + (PLAYER_SIZE + CONST) / 2);
//     }

//     // Check vertical movement (Y direction)
//     if (game->data->map[block_y.index] == '1' && game->data->map[block_x.index] != '1') 
// 	{
//         printf("Collision in Y direction, block movement in y\n");
       
//     }
//     else 
// 	{
//         game->player.p_pos.y = new_pos.y;  // Move player vertically
//         game->camera.pos.y = (game->player.p_pos.y + (PLAYER_SIZE + CONST) / 2);
//     }
// }

int corner_block_index(t_game *game, t_pos corner)
{
	float y_index = get_block_index2(game, &corner, 1).y;
	float x_index = get_block_index2(game, &corner, 0).x;
	int block_index = (y_index) * game->data->map_data.cols + x_index;
	return (block_index);
}

bool is_colliding(t_game *game, t_pos new, int flag)
{
    t_pos new_tl = new;
	t_pos new_tr = {new.x + PLAYER_SIZE * CONST , new.y};
	t_pos new_bl = {new.x, new.y + PLAYER_SIZE * CONST };
	t_pos new_br = {new.x + PLAYER_SIZE * CONST -1, new.y + PLAYER_SIZE * CONST };
	
	// if ((game->data->map[corner_block_index(game, new_tl)] == '1')
	// 	|| (game->data->map[corner_block_index(game, new_tr)] == '1')
	// 	||(game->data->map[corner_block_index(game, new_bl)] == '1')
	// 	||(game->data->map[corner_block_index(game, new_br)] == '1'))
		// if ((is_wall_hit(game, new_tl, 0))
		// || (is_wall_hit(game, new_tr, 0))
		// ||(is_wall_hit(game, new_bl, 0))
		// ||(is_wall_hit(game, new_br, 0))
		// ||(is_wall_hit(game, new_tl, 1))
		// || (is_wall_hit(game, new_tr, 1))
		// ||(is_wall_hit(game, new_bl, 1))
		// ||(is_wall_hit(game, new_br, 1)))
		if ((is_wall_hit2(game, new_tl, flag))
		|| (is_wall_hit2(game, new_tr, flag))
		||(is_wall_hit2(game, new_bl,flag))
		||(is_wall_hit2(game, new_br, flag)))

	{
		if (game->data->map[corner_block_index(game, new_tl)] == '1')
			printf ("collision tl@ %f, %f\n", new_tl.x, new_tl.y);
		if(game->data->map[corner_block_index(game, new_tr)] == '1')
			printf ("collision tr@ %f, %f\n", new_tr.x, new_tr.y);
		if(game->data->map[corner_block_index(game, new_bl)] == '1')
			printf ("collision bl@ %f, %f\n", new_bl.x, new_bl.y);
		if(game->data->map[corner_block_index(game, new_br)] == '1')
			printf ("collision br @ %f, %f\n", new_br.x, new_br.y);
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
	
		if (is_wall_hit2(game, temp_pos1, 1) && is_wall_hit2(game, temp_pos2, 0))
		{
			printf("diagonal\n");
			return;
		}
		printf ("trying to move horrizontally\n");
		printf ("player is at x=%f y=%f\n", game->player.p_pos.x, game->player.p_pos.y);
		
		printf ("temp_pos.x is %f, temp_pos.y is %f\n", temp_pos1.x, temp_pos1.y);
		if (!is_colliding(game, temp_pos1, 1))
		//if(game->data->map[corner_block_index(game, temp_pos)] != '1')
		{
			game->player.p_pos.x = temp_pos1.x; // Allow horizontal movement
			game->camera.pos.x = game->player.p_pos.x + PLAYER_SIZE * CONST / 2 - 1;
			printf ("Allowing to go to new x\n\n");
			return;
		}
		else
			printf ("no horizontal movement allowed\n\n");

		
		printf ("trying to move vertically\n");
		printf ("temp_pos.x is %f, temp_pos.y is %f\n", temp_pos2.x, temp_pos2.y);
		if (!is_colliding(game, temp_pos2, 0))
		{
			game->player.p_pos.y = temp_pos2.y; // Allow vertical movement
			game->camera.pos.y = game->player.p_pos.y + PLAYER_SIZE * CONST /2 - 1;
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
		game->player.p_pos = new_pos;
		game->camera.pos.x = game->player.p_pos.x + PLAYER_SIZE * CONST / 2 - 1;
		game->camera.pos.y = game->player.p_pos.y + PLAYER_SIZE * CONST /2- 1;
	}
}



static void check_keys_for_movement(t_game *game, mlx_key_data_t keydata)
{
	t_pos new;
	new.x = game->player.p_pos.x;
	new.y = game->player.p_pos.y;
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
		check_collision(game, game->player.p_pos, new);
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
