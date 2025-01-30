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
	while (distance < MAX_RAY_LENGTH)
	{
		game->ray->end.x += cos(angle) * step_size;
		game->ray->end.y -= sin(angle) * step_size;
		game->ray-> distance += step_size;
		//printf ("REACH NEAREST: game->ray->end.x %f game->ray->end.y %f\n", game->ray->end.x, game->ray->end.y);
		//mlx_put_pixel(game->rays, (int)game->ray->end.x, (int)game->ray->end.y, distance_to_color(distance));

		//check map limits
		{
			if (game->mapdata[get_block_index(&game->ray->end)] == '1')
			{
				
				//printf ("Intersection found\n");
				//printf ("With my stats: game->ray->end.x is %f, game->ray->end.y is %f\n", game->ray->end.x - X_START, game->ray->end.y - Y_START);
				game->ray->wall_met= 1;
				game->ray->distance = get_distance(game->camera.pos, game->ray->end);
				if ((int)(round(game->ray->end.x) - X_START) % (PIXELS_PER_BLOCK * CONST) == 0)
				{
					//printf ("It met vertical first\n");
					game->ray->found_vertical_first = true;
				}
				if ((int)(round(game->ray->end.y) - Y_START) % (PIXELS_PER_BLOCK * CONST) == 0)
				{
					//printf ("It met horizontal first\n");
					game->ray->found_vertical_first = false;
				}
				return;
			}
		}
		if (distance > MAX_RAY_LENGTH)
		{
			// Out of bounds, stop casting
			game->ray->wall_met= false;
			break;
		}
	}
}

bool is_out_of_bounds(t_pos position)
{
	if (position.y < 0 || position.x < 0 || position.y >= ROWS * 4 * 8 || position.x >= COLS * 4 * 8)
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
	if (game->mapdata[get_block_index2(game, &inter, flag)] == '1')
	{	
		//printf ("game->ray->end.x %f, game->ray->end.y %f\n", game->ray->end.x, game->ray->end.y);
		//printf ("hit wall\n");
		return (true);
	}
	return (false);
}


void reach_nearest_wall_by_intersections(t_game *game, float angle)
{
	float horiz_distance, vertical_distance;
	horiz_distance = horiz_intersect(game, angle);
	vertical_distance = vertical_intersect(game, angle);
	//printf ("vertical itersection: distance %f, end.x %f, end.y %f\n", vertical_distance, game->ray->v_hit.x, game->ray->v_hit.y);
	//printf ("horizontal itersection: distance %f ,end.x %f, end.y %f\n", horiz_distance, game->ray->h_hit.x, game->ray->h_hit.y);
	// if (horiz_distance > vertical_intersect(game, angle))
	if (horiz_distance > vertical_distance)
	{	
		//printf ("I met vertical first\n");
		game->ray->found_vertical_first = true;
		game->ray->end.x = game->ray->v_hit.x;
		game->ray->end.y = game->ray->v_hit.y;
		game->ray->distance = get_distance(game->camera.pos, game->ray->end);
	}
	else
	{
		//printf ("I met horizontal first\n");
		game->ray->found_vertical_first = false;
		game->ray->end.x = game->ray->h_hit.x;
		game->ray->end.y = game->ray->h_hit.y;
		game->ray->distance = get_distance(game->camera.pos, game->ray->end);
	}
}