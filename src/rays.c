#include "../inc/game.h"

// //block starts at n * game->cell_size
// //block ends at n * game->cell_size + game->cell_size - 1 = (n + 1) *  game->cell_size - 1
// int get_block_index(t_pos *grid_pos)
// {
// 	int result = -1;
// 	int block_index_x = (int)((floor(grid_pos->x) - X_START) / (game->cell_size));
// 	int block_index_y = (int)((floor(grid_pos->y) - Y_START) / (game->cell_size));
// 	//printf("on grid_x %d, on grid Y %d\n", block_index_x, block_index_y);
// 	result = (block_index_y) * COLS + (block_index_x);
// 	//printf ("result is %d\n", result);
// 	//printf ("game->ray->end.x %f, game->ray->end.y %f\n", game->ray->end.x, game->ray->end.y);
// 	return result;
// }

//flag: 1 vertical, horizontal 0
int get_block_index2(t_game *game, t_pos *grid_pos, int flag)
{
	int result = -1;
	int block_index_x = (int)((floor(grid_pos->x) - X_START) / (game->cell_size));
	int block_index_y = (int)((floor(grid_pos->y) - Y_START) / (game->cell_size));
	//printf("on grid_x %d, on grid Y %d\n", block_index_x, block_index_y);
	if (flag && (game->ray->angle_quad == 1 || game->ray->angle_quad == 2))
		block_index_y = (int)(ceil(grid_pos->y) - Y_START) / (game->cell_size);
	else if (!flag && (game->ray->angle_quad == 2 || game->ray->angle_quad == 3))
		block_index_x = (int)(ceil(grid_pos->x) - Y_START) / (game->cell_size);
	
	result = (block_index_y) * game->data->map_data.cols + (block_index_x);
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
	// t_pos start = {game->camera.pos.x, game->camera.pos.y};

	float step = FOV * DEG_TO_RAD / SCREEN_WIDTH;
	// printf ("step is %f\n", step);
	game->ray->current_angle = game->player.angle + (FOV / 2) * DEG_TO_RAD;
	normalize_angle_to_2pi((double *)&game->ray->current_angle);
	determine_quad(game->ray->current_angle, &game->ray->angle_quad);
	//printf ("cast rays: angle is %f\n", game->ray->current_angle);
	
	
	game->ray->ray_num = 0;
	if (game->is_debug == false)
		game->ray->number_of_rays = SCREEN_WIDTH;
	else
		game->ray->number_of_rays = 1;
		
	while (game->ray->ray_num < game->ray->number_of_rays)
	// while (game->ray->ray_num < 1)
	{	
		// printf("by_plotting: \n");
		//reach_nearest_wall_by_plotting(game, game->ray->current_angle);
		// printf("Ray %d: angle %f, distance %f, camera.x %f, camera.y %f\n", game->ray->ray_n, game->ray->current_angle, game->ray->distance, game->camera.pos.x, game->camera.pos.y);
		// printf ("facing %s wall, end.x %f, end.y %f\n", get_direction(game), game->ray->end.x, game->ray->end.y);
		// printf ("found vertical first? %d\n\n", game->ray->found_vertical_first);
		
		// if (game->is_mmap == true && game->is_debug == false)
		//DDA_ray(game, game->camera.pos, game->ray->end, 0xFFFF00FF);
																		//or
		// if (game->is_mmap == true && game->is_debug == false)
		// 	bresenham_ray(game, game->camera.pos, game->ray->end);
		
		// printf("by_intersections: \n");
		reach_nearest_wall_by_intersections(game, game->ray->current_angle);
		//printf("Ray %d: angle %f, distance %f, camera.x %f, camera.y %f\n", game->ray->ray_num, game->ray->current_angle, game->ray->distance, game->camera.pos.x, game->camera.pos.y);
		//printf ("facing %s wall, end.x %f, end.y %f\n", get_direction(game), game->ray->end.x, game->ray->end.y);
		//printf ("found vertical first? %d\n\n", game->ray->found_vertical_first);
		// if (game->is_mmap == true && game->is_debug == false)
		//DDA_ray(game, game->camera.pos, game->ray->end, 0xFF00FFFF);
																		//or
		// if (game->is_mmap == true && game->is_debug == false)
		
		game->ray->ray_start[game->ray->ray_num] = game->camera.pos;
		game->ray->ray_start[game->ray->ray_num] = game->camera.pos;
		game->ray->ray_end[game->ray->ray_num] = game->ray->end;
		game->ray->ray_end[game->ray->ray_num] = game->ray->end;

		//draw_ray(game, game->camera.pos, game->ray->end);
		
		draw_vertical_slice(game);
		
		game->ray->intersect.x = 0;
		game->ray->intersect.y = 0;
		game->ray->current_angle -= step;
		normalize_angle_to_2pi((double *)&game->ray->current_angle);
		determine_quad(game->ray->current_angle, &game->ray->angle_quad);
		game->ray->ray_num++;
		
		
	}
}

