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

void draw_player_direction(t_game *game, t_pos start, double angle)
{
	if (game->player_dir)
		mlx_delete_image(game->mlx, game->player_dir);

	game->player_dir = mlx_new_image(game->mlx, 1024, 512);
	if (!game->player_dir|| (mlx_image_to_window(game->mlx, game->player_dir, 0, 0) < 0))
		return; //error msg
	double end_x = start.x;
	double end_y = start.y;
	double step_size = .1;
	double distance = 0.0;
	while (distance < PLAYER_DIRECTION_SIZE)
	{
		end_x += cos(angle) * step_size;
		end_y -= sin(angle) * step_size;
		distance += step_size;
		if (game->mapdata[get_block_index(&(t_pos){end_x, end_y})] == 1)
			return;

		mlx_put_pixel(game->player_dir, (int)end_x, (int)end_y, 0xFF0000FF);
	}
}


float cast_ray(t_game *game, t_pos start, t_pos *end, double angle) //start and end include X_START and Y_START
{
	(void)game;
	end->x = start.x;
	end->y = start.y;
	double step_size = .1;  // Small step to move along the ray
	double distance = 0.0;
   
	//printf ("angle is %f\n", angle);
	//printf ("starting in x=%f y=%f\n", start.x, start.y);
	if (game->rays)
		mlx_delete_image(game->mlx, game->rays);

	game->rays = mlx_new_image(game->mlx, 1024, 512);
	if (!game->rays|| (mlx_image_to_window(game->mlx, game->rays, 0, 0) < 0))
		exit (EXIT_FAILURE); //error msg

	while (distance < MAX_RAY_LENGTH)
	{
		end->x += cos(angle) * step_size;
		end->y -= sin(angle) * step_size;
		distance += step_size;
		// printf ("ray_x %f ray_y %f\n", ray_x, ray_y);
		mlx_put_pixel(game->rays, (int)end->x, (int)end->y, 0xFF0000FF);

		//check map limits
		{
			if (game->mapdata[get_block_index(end)] == 1)
			{
				//printf ("Intersection found\n");
				//printf ("With my stats: end->x is %f, end->y is %f\n", (end->x) - X_START,(end->y)- Y_START);
				return distance;
			}
		}
		// else
		// {
		//     // Out of bounds, stop casting
		//     break;
		// }
	}
	return MAX_RAY_LENGTH;
}

void cast_rays(t_game *game)
{
	t_pos start = {game->player.x + PLAYER_SIZE * CONST / 2, game->player.y + PLAYER_SIZE * CONST / 2};
	t_pos end = start;
	
	draw_player_direction(game, start, game->player.angle);

	if (game->rays)
		mlx_delete_image(game->mlx, game->rays);

	game->rays = mlx_new_image(game->mlx, 1024, 512);
	if (!game->rays|| (mlx_image_to_window(game->mlx, game->rays, 0, 0) < 0))
		return; //error msg

	float start_angle = game->player.angle - (FOV / 2) * DEG_TO_RAD;
	while (start_angle >= 2 * M_PI)
		start_angle -= 2 * M_PI;
	while (start_angle < 0)
		start_angle += 2 * M_PI;

	float step = FOV * DEG_TO_RAD / RAY_COUNT;

	float ray_angle = start_angle;
	for (int i = 0; i < RAY_COUNT; i++)
	{
		//float distance = cast_ray(game, start, &end, ray_angle);
		//cast_ray(game, start, &end, ray_angle);
		//printf("Ray %d: distance %f, end.x %f, end.y %f\n", i, distance, end.x, end.y);

		DDA_rays(game, start, end);
		ray_angle += step;
		while (ray_angle >= 2 * M_PI)
			ray_angle -= 2 * M_PI;
		while (ray_angle < 0)
			ray_angle += 2 * M_PI;
	}
}

