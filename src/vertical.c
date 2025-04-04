#include "../inc/game.h"

/*
void	set_inc_vert(t_game *game, float *increase_x, int *delta_x_to_next_vertical, float *increase_y)
{
	if (game->ray->angle_quad == 1 || game->ray->angle_quad == 4) // ray facing right
	{
		*increase_x = game->cell_size;
		*delta_x_to_next_vertical = game->cell_size; //proceed to the first location on the new block
	}
	else if (game->ray->angle_quad == 2 || game->ray->angle_quad == 3) // ray facing left
	{
		*increase_x = -game->cell_size;
		*delta_x_to_next_vertical = -1; //proceed to the last location on the new block
	}
	if (game->ray->angle_quad == 1 || game->ray->angle_quad == 4)
		*increase_y *= -1;
}
*/

double	vertical_intersect(t_game *game)
{
	double	increase_y;

	if (game->ray->tan_current == HUGE_VAL || game->ray->tan_current == -HUGE_VAL)
		return (OUT_OF_BOUNDS);

	//printf ("\nVERTICAL:\n");
	increase_y = game->cell_size * game->ray->tan_current; //how much y changes when x changes by 1 (or -1) block_size
	
	//set_inc_vert(game, &increase_x, &delta_x_to_next_vertical, &increase_y);
	//printf ("increase_y is %f\n", increase_y);
	//printf ("increase_x is %f, delta_x_to_next_vertical is %d, \n", increase_x, delta_x_to_next_vertical);
	if (game->ray->angle_quad == 1 || game->ray->angle_quad == 4)
	{
		increase_y *= -1;
		game->ray->intersect.x = ceil((game->camera.pos.x - X_START) / game->cell_size) * game->cell_size;
		game->ray->intersect.y = game->camera.pos.y - Y_START - (game->ray->intersect.x - game->camera.pos.x) * game->ray->tan_current;
	}
	else
	{
		game->ray->intersect.x = floor((game->camera.pos.x - X_START) / game->cell_size) * game->cell_size;
		game->ray->intersect.y = game->camera.pos.y - Y_START + (game->ray->intersect.x - game->camera.pos.x) * game->ray->tan_current;
	}
		
	
	//printf ("game->ray->intersect.x %f\n", game->ray->intersect.x);
	//printf ("game->camera.pos.x %f, floor(game->camera.pos.x / (game->cell_size)) %f\n", game->camera.pos.x, floor(game->camera.pos.x / (game->cell_size)));
	
	//printf ("game->ray->intersect.y %f\n", game->ray->intersect.y);
	while (!is_out_of_bounds(game, game->ray->intersect) && !is_wall_hit(game, game->ray->intersect, 1))
	{
		//if (game->is_debug)
		//	safe_put_pixel(game, (int)game->ray->intersect.x, (int)game->ray->intersect.y, 0xFFFF00FF);
		//printf ("vertical intersect. did not hit wall yet\n");
		//mlx_put_pixel(game->scene, (int)round(game->ray->intersect.x) - X_START,  (int)round(game->ray->intersect.y) - Y_START, 0xFFFF00FF);
		game->ray->intersect.x += game->cell_size;
		game->ray->intersect.y += increase_y; //the sign was already dealt with
		//printf ("intersect_x is %f, intersect_y is %f\n", game->ray->intersect.x, game->ray->intersect.y);
	}
	
	if (is_out_of_bounds(game, game->ray->intersect))
		return (OUT_OF_BOUNDS);
	//printf ("	in the function, game->ray->intersect.x is %f and game->ray->intersect.y is %f\n", game->ray->intersect.x, game->ray->intersect.y);
	//printf ("in horiz intersect\n");
	//if (game->is_debug )
	//	safe_put_pixel(game, (int)game->ray->intersect.x, (int)game->ray->intersect.y, 0xFFFF00FF);
	game->ray->v_hit.x = game->ray->intersect.x;
	game->ray->v_hit.y = game->ray->intersect.y;
	//printf ("vertical intersect, end.x is %f and end.y is %f\n", game->ray->v_hit.x = game->ray->intersect.x, game->ray->v_hit.y = game->ray->intersect.y);
	// return (sqrt(pow(game->ray->inter.x - game->camera.pos.x, 2) + 
	// 			pow(game->ray->inter.y - game->camera.pos.y, 2)));
	return (get_distance(game->camera.pos, game->ray->v_hit));
}
