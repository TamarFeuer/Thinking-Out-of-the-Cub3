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

void reach_nearest_wall_block(t_game *game, t_pos start, double angle) //start and end include X_START and Y_START
{
	(void)game;
	game->ray->end.x = start.x;
	game->ray->end.y = start.y;
	double step_size = .1;  // Small step to move along the ray
	double distance = 0.0;
   
	//printf ("angle is %f\n", angle);
	//printf ("starting in x=%f y=%f\n", start.x, start.y);
	// if (game->rays)
	// 	mlx_delete_image(game->mlx, game->rays);

	// game->rays = mlx_new_image(game->mlx, 1024, 512);
	// if (!game->rays|| (mlx_image_to_window(game->mlx, game->rays, 0, 0) < 0))
	// 	exit (EXIT_FAILURE); //error msg

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

void cast_rays(t_game *game)
{
	t_pos start = {game->player.x + PLAYER_SIZE * CONST / 2, game->player.y + PLAYER_SIZE * CONST / 2};
	//t_pos start = {206, 380};
	
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
	//printf ("in CAST RAYS start angle is %f\n", start_angle);  //!
	float step = FOV * DEG_TO_RAD / RAY_COUNT;
	//printf ("step is %f\n", step);
	double ray_angle = start_angle;
	int i = 0;
	while (i < RAY_COUNT)
	// while (i < 5)
	{
		
		//float distance = cast_ray(game, start, &end, ray_angle);
		reach_nearest_wall_block(game, start, ray_angle);
		printf("Ray %d: distance %f, end.x %f, end.y %f\n", i, game->ray->distance, game->ray->end.x, game->ray->end.y);
		printf(" i is %d, angle is %f\n", i, ray_angle / M_PI);
		printf ("RAYS: end_x is %f and end_y %f\n wall found? %d\n", game->ray->end.x, game->ray->end.y,game->ray->wall_met );
		//DDA_ray(game, start, game->ray->end);  			//what happens with pi/4 5pi/4 etc?
		bresenham_ray(game, start, game->ray->end);   //what happens after moving the player?

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

