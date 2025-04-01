#include "../inc/game.h"


int get_block_index(t_game *game, t_pos *grid_pos, int flag)
{
	int result = -1;
	int block_index_x = (int)((floor(grid_pos->x) - X_START) / (game->cell_size));
	int block_index_y = (int)((floor(grid_pos->y) - Y_START) / (game->cell_size));
	//printf("on grid_x %d, on grid Y %d\n", block_index_x, block_index_y);
	// if (flag == 4 && (game->ray->angle_quad == 1 || game->ray->angle_quad == 2))
	// 	block_index_y = (int)(ceil(grid_pos->y) - Y_START) / (game->cell_size);
	// if (flag ==4 && (game->ray->angle_quad == 2 || game->ray->angle_quad == 3))
	// 	block_index_x = (int)(ceil(grid_pos->x) - Y_START) / (game->cell_size);	
	if (flag == 1 && (game->ray->angle_quad == 1 || game->ray->angle_quad == 2))
		block_index_y = (int)(ceil(grid_pos->y) - Y_START) / (game->cell_size);
	else if (!flag && (game->ray->angle_quad == 2 || game->ray->angle_quad == 3))
		block_index_x = (int)(ceil(grid_pos->x) - Y_START) / (game->cell_size);
	
	result = (block_index_y) * game->data->map_data.cols + (block_index_x);
	
	//printf ("game->ray->end.x %f, game->ray->end.y %f\n", game->ray->end.x, game->ray->end.y);
	return result;
}

t_block_index get_block_index2(t_game *game, t_pos *grid_pos, int flag)
{
	t_block_index block_index;
	block_index.index = -1;
	block_index.x = (int)((floor(grid_pos->x) - X_START) / (game->cell_size));
	block_index.y = (int)((floor(grid_pos->y) - Y_START) / (game->cell_size));
	//printf("on grid_x %d, on grid Y %d\n", block_index_x, block_index_y);
	if (flag == 1 && (game->ray->angle_quad == 1 || game->ray->angle_quad == 2))
	{
		
		block_index.y = (int)(ceil(grid_pos->y) - Y_START) / (game->cell_size);
	}
	else if (flag == 0 && (game->ray->angle_quad == 2 || game->ray->angle_quad == 3))
	{
		
		block_index.x = (int)(ceil(grid_pos->x) - Y_START) / (game->cell_size);
	}
	
	block_index.index = (block_index.y) * game->data->map_data.cols + block_index.x;
	//printf ("flag is %d, result is %d\n", flag, result);
	//printf ("game->ray->end.x %f, game->ray->end.y %f\n", game->ray->end.x, game->ray->end.y);
	return block_index;
}

//flag: vertical 1, horizontal 0
t_block_index get_block_index3(t_game *game, t_pos *grid_pos, int flag)
{
	t_block_index block_index;
	block_index.index = -1;
	block_index.x = (int)((floor(grid_pos->x) - X_START) / (game->cell_size));
	block_index.y = (int)((floor(grid_pos->y) - Y_START) / (game->cell_size));
	//printf("on grid_x %d, on grid Y %d\n", block_index_x, block_index_y);
	if (flag == 0 && (game->ray->angle_quad == 1 || game->ray->angle_quad == 2))
	{
		
		block_index.y = (int)(ceil(grid_pos->y) - Y_START) / (game->cell_size);
	}
	else if (flag == 1 && (game->ray->angle_quad == 2 || game->ray->angle_quad == 3))
	{
		
		block_index.x = (int)(ceil(grid_pos->x) - Y_START) / (game->cell_size);
	}
	
	block_index.index = (block_index.y) * game->data->map_data.cols + block_index.x;
	//printf ("flag is %d, result is %d\n", flag, result);
	//printf ("game->ray->end.x %f, game->ray->end.y %f\n", game->ray->end.x, game->ray->end.y);
	return block_index;
}


double get_distance(t_pos start, t_pos end)
{
	double dx = end.x - start.x;
	double dy = end.y - start.y;
	return sqrt(dx * dx + dy * dy);
}

void cast_rays(t_game *game)
{
	t_ray *const		ray = game->ray;

	ray->ray_num = 0;
	while (ray->ray_num < SCREEN_WIDTH)
	{	
		ray->relative_angle = atan((SCREEN_WIDTH / 2.0 - ray->ray_num) / game->pplane);
		ray->current_angle = game->player.angle + ray->relative_angle;
		normalize_angle_to_2pi(&ray->current_angle);
		determine_quad(ray->current_angle, &ray->angle_quad);
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
		reach_nearest_wall_by_intersections(game);
		// printf("Ray %d: angle %f, distance %f, camera.x %f, camera.y %f\n", game->ray->ray_num, game->ray->current_angle, game->ray->distance, game->camera.pos.x, game->camera.pos.y);
		// printf ("facing %s wall, end.x %f, end.y %f\n", get_direction(game), game->ray->end.x, game->ray->end.y);
		// printf ("is vertical first? %d\n\n", game->ray->is_vertical_first);
		// if (game->is_mmap == true && game->is_debug == false)
		//DDA_ray(game, game->camera.pos, game->ray->end, 0xFF00FFFF);
																		//or
		// if (game->is_mmap == true && game->is_debug == false)
		
		ray->ray_start[ray->ray_num].x = game->camera.pos.x;
		ray->ray_start[ray->ray_num].y = game->camera.pos.y;
		ray->ray_end[ray->ray_num].x = ray->end.x;
		ray->ray_end[ray->ray_num].y = ray->end.y;

		//draw_ray(game, game->camera.pos, game->ray->end);
		//printf ("in cast_rays: angle is %f\n", game->ray->current_angle);
		draw_scene(game, game->ray);
		
		ray->intersect.x = 0;
		ray->intersect.y = 0;

		ray->ray_num++;
	}
}
