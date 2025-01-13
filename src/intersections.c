#include "../inc/game.h"

void reach_nearest_wall_block(t_game *game, t_pos start, double angle) //start and end include X_START and Y_START
{
	(void)game;
	game->ray->end.x = start.x;
	game->ray->end.y = start.y;
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
			if (game->mapdata[get_block_index(&game->ray->end)] == 1)
			{
				
				//printf ("Intersection found\n");
				//printf ("With my stats: game->ray->end.x is %f, game->ray->end.y is %f\n", game->ray->end.x - X_START, game->ray->end.y - Y_START);
				game->ray->wall_met= 1;
				game->ray->distance = get_distance(start, game->ray->end);
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

//  bool is_vertical_intersect (t_game *game, t_pos *end, double angle)
//  {
// 	// (void)game;
// 	// (void)angle;
// 	// (*end).x = game->player.p_pos.x;
// 	// (*end).y = game->player.p_pos.y;
// 	// if (game->player.angle_quad == 1 || game->player.angle_quad == 4)
// 	// {	
// 	// 	if ((int)round((*end).x) != X_START)
// 	// 	{
// 	// 		double dx = PIXELS_PER_BLOCK * CONST - (((int)round((*end).x) - X_START) % (PIXELS_PER_BLOCK * CONST ));
// 	// 		printf ("dx is %f\n", dx);
// 	// 		(*end).x += dx;
// 	// 	}
// 	// }
// 	// else
	
// 	// {
		
		
// 	// }
// 	// return 1;
	
// 	float	x_inc;
// 	float	y_inc;
// 	float	inter_x;
// 	float	inter_y;
// 	int		x_add_pixel;

// 	x_add_pixel = 0;
// 	if (angle == M_PI / 2 || angle == 3 * M_PI / 2)
// 		angle += 0.0001;
// 	y_inc = PIXELS_PER_BLOCK * CONST * tan(angle);
// 	inc_and_pixel_vert(angle, &x_inc, &x_add_pixel, &y_inc);
// 	inter_x = floor(game->camera.x / PIXELS_PER_BLOCK * CONST) * PIXELS_PER_BLOCK * CONST + 
// 															x_add_pixel;
// 	inter_y = game->camera.float_y + 
// 						(inter_x - game->camera.float_x) * tan(angle);
// 	while (!wall_hit_or_out_bounds(game, inter_y, inter_x, 1))
// 	{
// 		inter_y += y_inc;
// 		inter_x += x_inc;
// 	}
// 	game->ray->end_vert.x = inter_x;
// 	game->ray->end_vert.y = inter_y;
// 	return (sqrt(pow(inter_x - game->camera.float_x, 2) + 
// 				pow(inter_y - game->camera.float_y, 2)));
//  }

// void reach_nearest_wall_block2(t_game *game, double angle)
// {
// 	(void)game;
// 	t_pos end;
// 	game->ray->end.x = game->camera.float_x;
// 	game->ray->end.y = game->camera.float_y;
// 	is_vertical_intersect(game, &end, angle);
// }