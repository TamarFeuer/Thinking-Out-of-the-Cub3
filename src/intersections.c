#include "../inc/game.h"

void reach_nearest_wall_by_plotting(t_game *game, float angle) //start and end include X_START and Y_START
{
	(void)game;
	game->ray->end.x = game->camera.pos.x;
	game->ray->end.y = game->camera.pos.y;
	double step_size = .1;  // Small step to move along the ray
	double distance = 0.0;
   
	//printf ("angle is %f\n", angle);
	//printf ("starting in x=%f y=%f\n", start.x, start.y);
	while (distance < MAX_RAY_DISTANCE)
	{
		game->ray->end.x += cos(angle) * step_size;
		game->ray->end.y -= sin(angle) * step_size;
		game->ray-> distance += step_size;
		//printf ("REACH NEAREST: game->ray->end.x %f game->ray->end.y %f\n", game->ray->end.x, game->ray->end.y);
		//mlx_put_pixel(game->rays, (int)game->ray->end.x, (int)game->ray->end.y, distance_to_color(distance));

		//check map limits
		{
			//if (game->mapdata[get_block_index(&game->ray->end)] == '1')
			if (game->data->map[get_block_index2(game, &game->ray->end, 99).index] == '1')
			{
				
				//printf ("Intersection found\n");
				//printf ("With my stats: game->ray->end.x is %f, game->ray->end.y is %f\n", game->ray->end.x - X_START, game->ray->end.y - Y_START);
				game->ray->wall_met= 1;
				game->ray->distance = get_distance(game->camera.pos, game->ray->end);
				if ((int)(round(game->ray->end.x) - X_START) % (game->cell_size) == 0)
				{
					//printf ("It met vertical first\n");
					game->ray->is_vertical_first = true;
				}
				if ((int)(round(game->ray->end.y) - Y_START) % (game->cell_size) == 0)
				{
					//printf ("It met horizontal first\n");
					game->ray->is_vertical_first = false;
				}
				return;
			}
		}
		if (distance > MAX_RAY_DISTANCE)
		{
			// Out of bounds, stop casting
			game->ray->wall_met= false;
			break;
		}
	}
}

bool is_out_of_bounds(t_game *game, t_pos position)
{
	if (position.y < 0 || position.x < 0 || position.y >= game->data->map_data.rows * game->cell_size || position.x >= game->data->map_data.cols * game->cell_size)
	{
		//printf ("out of bounds\n");
		return (true);
	}
	return (false);
}

// int	is_wall_hit(t_game *game, t_pos inter)
// {
// 	if (game->mapdata[get_block_index(&inter)] == 1)
// 	{	
// 		//printf ("game->ray->end.x %f, game->ray->end.y %f\n", game->ray->end.x, game->ray->end.y);
// 		//printf ("hit wall\n");
// 		return (true);
// 	}
// 	return (false);
// }

int	is_wall_hit(t_game *game, t_pos inter, int flag)
{
	if (game->data->map[get_block_index2(game, &inter, flag).index] == '1')
	{	
		//printf ("game->ray->end.x %f, game->ray->end.y %f\n", game->ray->end.x, game->ray->end.y);
		
		return (true);
	}
	return (false);
}

int	is_wall_hit2(t_game *game, t_pos inter, int flag)
{
	if (game->data->map[get_block_index2(game, &inter, flag).index] == '1')
	{	
		//printf ("game->ray->end.x %f, game->ray->end.y %f\n", game->ray->end.x, game->ray->end.y);
		printf ("hit wall\n");
		return (true);
	}
	return (false);
}


void reach_nearest_wall_by_intersections(t_game *game)
{
	float horiz_distance, vertical_distance;
	
	//printf ("in reach nearest: angle is %f\n", game->ray->current_angle);
	horiz_distance = horiz_intersect(game);
	vertical_distance = vertical_intersect(game);
	if (game->ray->ray_num == SCREEN_WIDTH /2)
	{
		printf ("vertical itersection: distance %f, end.x %f, end.y %f\n", vertical_distance, game->ray->v_hit.x, game->ray->v_hit.y);
		printf ("horizontal itersection: distance %f ,end.x %f, end.y %f\n", horiz_distance, game->ray->h_hit.x, game->ray->h_hit.y);
	}

	if (horiz_distance > vertical_distance)
	{	
		if (game->ray->ray_num == SCREEN_WIDTH /2)
			printf ("\nI met vertical first\n");
		game->ray->is_vertical_first = true;
		game->ray->end.x = game->ray->v_hit.x;
		game->ray->end.y = game->ray->v_hit.y;
		game->ray->distance = get_distance(game->camera.pos, game->ray->end);
	}
	else
	{
		if (game->ray->ray_num == SCREEN_WIDTH /2)
			printf ("\nI met horizontal first\n");
		game->ray->is_vertical_first = false;
		game->ray->end.x = game->ray->h_hit.x;
		game->ray->end.y = game->ray->h_hit.y;
		game->ray->distance = get_distance(game->camera.pos, game->ray->end);
	}
	
}
