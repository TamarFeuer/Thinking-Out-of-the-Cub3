#include "../inc/game.h"

void	set_inc_vert(t_game *game, float *increase_x, int *delta_x_to_next_vertical, float *increase_y)
{
	if (game->ray->angle_quad == 1 || game->ray->angle_quad == 4) // ray facing right
	{
		*increase_x = CONST * PIXELS_PER_BLOCK;
		*delta_x_to_next_vertical = CONST * PIXELS_PER_BLOCK; //proceed to the first location on the new block
	}
	else if (game->ray->angle_quad == 2 || game->ray->angle_quad == 3) // ray facing left
	{
		*increase_x = -CONST * PIXELS_PER_BLOCK;
		*delta_x_to_next_vertical = -1; //proceed to the last location on the new block
	}
	if (game->ray->angle_quad == 1 || game->ray->angle_quad == 4)
		*increase_y *= -1;
}

float	vertical_intersect(t_game *game, float angle)
{
	float	increase_x;
	float	increase_y;
	int		delta_x_to_next_vertical;

	// printf ("\nVERTICAL:\n");
	delta_x_to_next_vertical = 0;
	if (angle == M_PI / 2 || angle == 3 * M_PI / 2)
		angle += 0.0001;
	//increase_x = CONST * PIXELS_PER_BLOCK;
	increase_y = CONST * PIXELS_PER_BLOCK * tan(angle); //how much y changes when x changes by 1 (or -1) block_size
	
	set_inc_vert(game, &increase_x, &delta_x_to_next_vertical, &increase_y);
	//printf ("increase_y is %f\n", increase_y);
	//printf ("increase_x is %f, delta_x_to_next_vertical is %d, \n", increase_x, delta_x_to_next_vertical);
	
	game->ray->intersect.x = floor(game->camera.pos.x / (CONST * PIXELS_PER_BLOCK)) * CONST * PIXELS_PER_BLOCK + delta_x_to_next_vertical;
	//printf ("game->ray->intersect.x %f\n", game->ray->intersect.x);
	//printf ("game->camera.x %d, floor(game->camera.x / (CONST * PIXELS_PER_BLOCK)) %f\n", game->camera.x, floor(game->camera.x / (CONST * PIXELS_PER_BLOCK)));
	game->ray->intersect.y = game->camera.pos.y - (game->ray->intersect.x - game->camera.pos.x) * tan(angle);
	
	//printf ("game->ray->intersect.y %f\n", game->ray->intersect.y);
	while (!is_out_of_bounds(game, game->ray->intersect) && !is_wall_hit(game, game->ray->intersect, 1))
	{
		if (game->is_debug)
			safe_put_pixel(game, (int)game->ray->intersect.x, (int)game->ray->intersect.y, 0xFFFF00FF);
		//printf ("vertical intersect. did not hit wall yet\n");
		//mlx_put_pixel(game->scene, (int)round(game->ray->intersect.x) - X_START,  (int)round(game->ray->intersect.y) - Y_START, 0xFFFF00FF);
		game->ray->intersect.y += increase_y; //the sign was already dealt with
		game->ray->intersect.x += increase_x;
		//printf ("intersect_x is %f, intersect_y is %f\n", game->ray->intersect.x, game->ray->intersect.y);
	}
	if (is_out_of_bounds(game, game->ray->intersect))
		return (OUT_OF_BOUNDS);
	//printf ("	in the function, game->ray->intersect.x is %f and game->ray->intersect.y is %f\n", game->ray->intersect.x, game->ray->intersect.y);
	if (game->is_debug )
		safe_put_pixel(game, (int)game->ray->intersect.x, (int)game->ray->intersect.y, 0xFFFF00FF);
	game->ray->v_hit.x = game->ray->intersect.x;
	game->ray->v_hit.y = game->ray->intersect.y;
	//printf ("vertical intersect, end.x is %f and end.y is %f\n", game->ray->v_hit_x = inter_x, game->ray->v_hit_y = inter_y);
	// return (sqrt(pow(game->ray->inter.x - game->camera.pos.x, 2) + 
	// 			pow(game->ray->inter.y - game->camera.pos.y, 2)));
	return (get_distance(game->camera.pos, game->ray->v_hit));
}
