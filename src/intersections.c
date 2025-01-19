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


void	set_inc_vert(t_game *game, float *increase_x, int *delta_x_to_next_vertical, \
															float *increase_y)
{
	if (game->ray->angle_quad == 1 || game->ray->angle_quad == 4) // quad 1 and quad 4
	{
		*increase_x = 4 * 8;
		*delta_x_to_next_vertical = 4 * 8;
	}
	else if (game->ray->angle_quad == 2 || game->ray->angle_quad == 3) //quad 2 and quad 3
	{
		*increase_x = -4 * 8;
		*delta_x_to_next_vertical =  -1;
	}
	if (game->ray->angle_quad == 1 || game->ray->angle_quad == 4)
		*increase_y *= -1;
}

void	set_inc_horiz(t_game *game, float *increase_y, int *delta_y_to_next_horiz, \
															float *increase_x)
{
	(void)increase_x;
	if (game->ray->angle_quad == 3 || game->ray->angle_quad == 4)
	{
		*increase_y = 4 * 8;
		*delta_y_to_next_horiz = 4 * 8;
	}
	else if (game->ray->angle_quad == 1 || game->ray->angle_quad == 2)
	{
		*increase_y = -4 * 8;
		*delta_y_to_next_horiz = -1; //0
	}
	if (game->ray->angle_quad == 3 || game->ray->angle_quad == 4)
		*increase_x *= -1;
	
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

int	is_wall_hit(t_game *game, t_pos inter)
				//inter is not end													int flag)
{
	if (game->mapdata[get_block_index(&inter)] == 1)
	{	
		//printf ("game->ray->end.x %f, game->ray->end.y %f\n", game->ray->end.x, game->ray->end.y);
		//printf ("hit wall\n");
		return (true);
	}
	return (false);
}

float	horiz_intersect(t_game *game, float angle)
{
	float	increase_x;
	float	increase_y;
	int		delta_y_to_next_horiz;
	
	//printf ("\nHORIZONTAL:\n");
	delta_y_to_next_horiz = 0;
	increase_x = 4 * 8 / tan(angle);
	set_inc_horiz(game, &increase_y, &delta_y_to_next_horiz, &increase_x);
	//printf ("increase_x is %f\n", increase_x);
	//printf ("increase_y is %f, delta_y_to_next_horiz is %d, \n", increase_y, delta_y_to_next_horiz);
	
	
	game->ray->inter.y = floor((game->camera.pos.y- Y_START) / (4 * 8)) * (4 * 8) + delta_y_to_next_horiz;
	//printf ("game->ray->inter.y %f\n", game->ray->inter.y);
	//printf ("game->camera.x %d\n", game->camera.x);
	//printf ("game->camera.y %d, floor(game->camera.y / (4.0*8.0)) %f\n", game->camera.y, floor(game->camera.y / (4.0*8.0)));
	game->ray->inter.x = (game->camera.pos.x - X_START) - (game->ray->inter.y - game->camera.pos.y) / tan(angle);
	//printf ("game->ray->inter.x %f\n", game->ray->inter.x);
	
	while (!is_out_of_bounds(game->ray->inter) && !is_wall_hit(game, game->ray->inter))
	{
		if (game->is_debug )
		safe_put_pixel(game, (int)game->ray->inter.x, (int)game->ray->inter.y, 0xFF00FFFF);
		//mlx_put_pixel(game->rays, (int)round(game->ray->inter.x) - X_START, (int)round(game->ray->inter.y) - Y_START, 0xFFBBBBFF);
		//printf ("horiz intersect: did not hit wall yet\n");
		game->ray->inter.y += increase_y;
		game->ray->inter.x += increase_x;
	}
	if (is_out_of_bounds(game->ray->inter))
		return (OUT_OF_BOUNDS);
	if (game->is_debug )
		safe_put_pixel(game, (int)game->ray->inter.x, (int)game->ray->inter.y, 0xFF00FFFF);
	game->ray->h_hit_x = game->ray->inter.x;
	game->ray->h_hit_y = game->ray->inter.y;
	//printf ("horiz intersect: end.x is %f and end.y is %f\n", game->ray->h_hit_x, game->ray->h_hit_y = game->ray->h_hit_x);
	return (sqrt(pow(game->ray->inter.x - game->camera.pos.x, 2) + \
				pow(game->ray->inter.y - game->camera.pos.y, 2)));
}
// when x increase by 8 * 4, y increases by
float	vertical_intersect(t_game *game, float angle)
{
	float	increase_x;
	float	increase_y;
	int		delta_x_to_next_vertical;

	// printf ("\nVERTICAL:\n");
	delta_x_to_next_vertical = 0;
	if (angle == M_PI / 2 || angle == 3 * M_PI / 2)
		angle += 0.0001;
	//increase_x = 4 * 8;
	increase_y = 4 * 8 * tan(angle); //how much y changes when x changes by 1 (or -1) block_size
	
	set_inc_vert(game, &increase_x, &delta_x_to_next_vertical, &increase_y);
	//printf ("increase_y is %f\n", increase_y);
	//printf ("increase_x is %f, delta_x_to_next_vertical is %d, \n", increase_x, delta_x_to_next_vertical);
	
	game->ray->inter.x = floor(game->camera.pos.x / (4 * 8)) * 4 * 8 + delta_x_to_next_vertical;
	//printf ("game->ray->inter.x %f\n", game->ray->inter.x);
	//printf ("game->camera.x %d, floor(game->camera.x / (4.0*8.0)) %f\n", game->camera.x, floor(game->camera.x / (4.0*8.0)));
	game->ray->inter.y = game->camera.pos.y - (game->ray->inter.x - game->camera.pos.x) * tan(angle);
	
	//printf ("game->ray->inter.y %f\n", game->ray->inter.y);
	while (!is_out_of_bounds(game->ray->inter) && !is_wall_hit(game, game->ray->inter))
	{
		if (game->is_debug )
		safe_put_pixel(game, (int)game->ray->inter.x, (int)game->ray->inter.y, 0xFFFF00FF);
		//printf ("vertical intersect. did not hit wall yet\n");
		//mlx_put_pixel(game->rays, (int)round(game->ray->inter.x) - X_START,  (int)round(game->ray->inter.y) - Y_START, 0x008000FF);
		game->ray->inter.y += increase_y; //the sign was already dealt with
		game->ray->inter.x += increase_x;
		//printf ("inter_x is %f, inter_y is %f\n", game->ray->inter.x, game->ray->inter.y);
		
	}
	if (is_out_of_bounds(game->ray->inter))
		return (OUT_OF_BOUNDS);
	if (game->is_debug )
		safe_put_pixel(game, (int)game->ray->inter.x, (int)game->ray->inter.y, 0xFFFF00FF);
	game->ray->v_hit_x = game->ray->inter.x;
	game->ray->v_hit_y = game->ray->inter.y;
	//printf ("vertical intersect, end.x is %f and end.y is %f\n", game->ray->v_hit_x = inter_x, game->ray->v_hit_y = inter_y);
	return (sqrt(pow(game->ray->inter.x - game->camera.pos.x, 2) + \
				pow(game->ray->inter.y - game->camera.pos.y, 2)));
}


void reach_nearest_wall_block2(t_game *game, t_pos start, double angle)
{
	(void)start;
	

	//printf ("quad is %d\n\n", game->ray->angle_quad);
	if (horiz_intersect(game, angle) > vertical_intersect(game, angle))
	{	
		//printf ("I met vertical first\n");
		game->ray->found_vertical_first = true;
		game->ray->end.x = game->ray->v_hit_x;
		game->ray->end.y = game->ray->v_hit_y;
		game->ray->distance = get_distance(game->camera.pos, game->ray->end);
	}
	else
	{
		//printf ("I met horizontal first\n");
		game->ray->found_vertical_first = false;
		game->ray->end.x = game->ray->h_hit_x;
		game->ray->end.y = game->ray->h_hit_y;
		game->ray->distance = get_distance(game->camera.pos, game->ray->end);
	}
}