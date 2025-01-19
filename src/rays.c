#include "../inc/game.h"

//block starts at n * PIXELS_PER_CLOCK * CONST
//block ends at n * PIXELS_PER_CLOCK * CONST + PIXELS_PER_CLOCK * CONST - 1 = (n + 1) *  PIXELS_PER_CLOCK * CONST - 1
int get_block_index(t_pos *grid_pos)
{
	int result = -1;
	int block_index_x = (int)((grid_pos->x - X_START) / (PIXELS_PER_BLOCK * CONST));
	int block_index_y = (int)((grid_pos->y - Y_START) / (PIXELS_PER_BLOCK * CONST));
	//printf("on grid_x %d, on grid Y %d\n", block_index_x, block_index_y);
	result = (block_index_y) * COLS + (block_index_x);
	//printf ("result is %d\n", result);
	//printf ("game->ray->end.x %f, game->ray->end.y %f\n", game->ray->end.x, game->ray->end.y);
	return result;
}

double get_distance(t_pos start, t_pos end)
{
	double dx = end.x - start.x;
	double dy = end.y - start.y;
	return sqrt(dx * dx + dy * dy);
}

void cast_rays(t_game *game)
{
	t_pos start = {game->camera.x, game->camera.y};

	float step = FOV * DEG_TO_RAD / NUMBER_OF_RAYS;
	// printf ("step is %f\n", step);
	game->ray->current_angle = game->player.angle + (FOV / 2) * DEG_TO_RAD;
	normalize_angle_to_2pi(&game->ray->current_angle);
	determine_quad(game->ray->current_angle, &game->ray->angle_quad);
	printf ("cast rays: angle is %f\n", game->ray->current_angle);
	
	game->ray->ray_n = 0;
	if (game->debug == false)
		game->ray->number_of_rays = NUMBER_OF_RAYS;
	else
		game->ray->number_of_rays = 1;
		
	while (game->ray->ray_n < game->ray->number_of_rays)
	{
		printf ("cast rays: angle is %f\n", game->ray->current_angle);
		reach_nearest_wall_block(game, start, game->ray->current_angle);
		
		// DDA_ray(game, start, game->ray->end);
		printf("1st: Ray %d: game->ray->distance %f, end.x %f, end.y %f\n\n", game->ray->ray_n, game->ray->distance, game->ray->end.x, game->ray->end.y);
		
		//reach_nearest_wall_block2(game, start, game->ray->current_angle);
		
		//printf("2nd: Ray %d: game->ray->distance %f, end.x %f, end.y %f\n\n", game->ray->ray_n, game->ray->distance, game->ray->end.x, game->ray->end.y);
		//printf(" game->ray->ray_n is %d, angle is %f\n", game->ray->ray_n, game->ray->current_angle / M_PI);
		//printf ("RAYS: end_x is %f and end_y %f\n wall found? %d\n", game->ray->end.x, game->ray->end.y,game->ray->wall_met );
		//printf ("end.x %f, end.y %f\n", game->ray->end.x , game->ray->end.y);
		
		//DDA_ray(game, start, game->ray->end);

		bresenham_ray(game, start, game->ray->end);
		
		draw_the_thing(game);
		
		game->ray->inter.x = 0;
		game->ray->inter.y = 0;
		game->ray->current_angle -= step;
		normalize_angle_to_2pi(&game->ray->current_angle);
		determine_quad(game->ray->current_angle, &game->ray->angle_quad);
		game->ray->ray_n++;
	}
	//draw_player_direction(game, start, game->player.angle);
}

