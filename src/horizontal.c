#include "../inc/game.h"

double	horiz_intersect(t_game *game)
{
	double	increase_x;
	double	increase_y;
	double	cotan_current;

	if (game->ray->tan_current == 0)
		return (OUT_OF_BOUNDS);
	else if (game->ray->tan_current == HUGE_VAL || game->ray->tan_current == -HUGE_VAL)
		cotan_current = 0;
	else
		cotan_current = 1.0 / game->ray->tan_current;

	//printf ("\nHORIZONTAL:\n");
	//set_inc_horiz(game, &increase_y, &delta_y_to_next_horiz, &increase_x);
	//printf ("increase_x is %f\n", increase_x);
	//printf ("increase_y is %f, delta_y_to_next_horiz is %d, \n", increase_y, delta_y_to_next_horiz);
	
	if (game->ray->angle_quad == 1 || game->ray->angle_quad == 2)
	{
		game->ray->intersect.y = floor(game->camera_pos.y / game->cell_size) * game->cell_size;
		game->ray->intersect.x = game->camera_pos.x - (game->ray->intersect.y - game->camera_pos.y) * cotan_current;
		increase_x = game->cell_size * cotan_current;
		increase_y = -game->cell_size;
	}
	else
	{
		game->ray->intersect.y = ceil(game->camera_pos.y  / game->cell_size) * game->cell_size;
		game->ray->intersect.x = game->camera_pos.x - (game->ray->intersect.y - game->camera_pos.y) * cotan_current;
		increase_x = -game->cell_size * cotan_current;
		increase_y = game->cell_size;
	}

	//printf ("game->ray->inter.y %f\n", game->ray->intersect.y);
	//printf ("game->camera.pos.x %f\n", game->camera.pos.x);
	//printf ("game->camera.pos.y %f, floor(game->camera.pos.y / (game->cell_size)) %f\n", game->camera.pos.y, floor(game->camera.pos.y / (game->cell_size)));
	//printf ("game->ray->intersect.x %f, game->ray->intersect.y %f\n", game->ray->intersect.x, game->ray->intersect.y);
	while (!is_out_of_bounds(game, game->ray->intersect) && !is_wall_hit(game, game->ray->intersect, INTERSECT_W_HORIZONTAL))
	{
		//printf ("in horiz intersect\n");
		//if (game->is_debug )
		//	safe_put_pixel(game, (int)game->ray->intersect.x, (int)game->ray->intersect.y, 0xFF00FFFF);
		//mlx_put_pixel(game->scene, (int)round(game->ray->inter.x) - X_START, (int)round(game->ray->inter.y) - Y_START, 0xFF0000FF);
		//printf ("horiz intersect: did not hit wall yet\n");
		game->ray->intersect.x += increase_x;
		game->ray->intersect.y += increase_y;

	}
	if (is_out_of_bounds(game, game->ray->intersect))
		return (OUT_OF_BOUNDS);
	//printf ("in horiz intersect\n");
	//if (game->is_debug )
		//safe_put_pixel(game, (int)game->ray->intersect.x, (int)game->ray->intersect.y, 0xFF00FFFF);
	game->ray->h_hit.x = game->ray->intersect.x;
	game->ray->h_hit.y = game->ray->intersect.y;
	//printf ("horiz intersectsect: end.x is %f and end.y is %f\n", game->ray->h_hit.x, game->ray->h_hit.y);
	// return (sqrt(pow(game->ray->intersect.x - game->camera.pos.x, 2) + 
	// 			pow(game->ray->intersect.y - game->camera.pos.y, 2)));
	return (get_distance(game->camera_pos, game->ray->h_hit));
}
