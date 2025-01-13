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
	printf ("camera.x is %d , camera.y is %d\n", game->camera.x , game->camera.y);
	// t_pos start = {game->player.p_pos.x, game->player.p_pos.x};
	//t_pos start = {206, 380};
	
	if (game->rays)
		mlx_delete_image(game->mlx, game->rays);

	game->rays = mlx_new_image(game->mlx, MMAP_WIDTH + 100, MMAP_HEIGHT+100);
	if (!game->rays|| (mlx_image_to_window(game->mlx, game->rays, X_START, Y_START ) < 0))
		return; //error msg
	draw_player(game);
	float start_angle = game->player.angle - (FOV / 2) * DEG_TO_RAD;
	
	while (start_angle >= 2 * M_PI)
		start_angle -= 2 * M_PI;
	while (start_angle < 0)
		start_angle += 2 * M_PI;
	//printf ("in CAST RAYS start angle is %f\n", start_angle);  //!
	float step = FOV * DEG_TO_RAD / RAY_NUMBER;
	// //printf ("step is %f\n", step);
	double ray_angle = start_angle;
	int i = 0;
	printf ("sfsdf player.y is %f\n", game->player.p_pos.y);
	while (i < RAY_NUMBER)
	// while (i < 5)
	{
		reach_nearest_wall_block(game, start, ray_angle);
		// reach_nearest_wall_block2(game, ray_angle);
		printf("Ray %d: distance %f, end.x %f, end.y %f\n", i, game->ray->distance, game->ray->end.x, game->ray->end.y);
		printf(" i is %d, angle is %f\n", i, ray_angle / M_PI);
		printf ("RAYS: end_x is %f and end_y %f\n wall found? %d\n", game->ray->end.x, game->ray->end.y,game->ray->wall_met );
		
		DDA_ray(game, start, game->ray->end);
		//bresenham_ray(game, start, game->ray->end);

		ray_angle += step;
		//ray_angle += 0.5;
		//printf ("ray angle is %f\n", ray_angle);
		while (ray_angle >= 2 * M_PI)
			ray_angle -= 2 * M_PI;
		while (ray_angle < 0)
			ray_angle += 2 * M_PI;
		i++;
	}
	draw_player_direction(game, start, game->player.angle);
}

