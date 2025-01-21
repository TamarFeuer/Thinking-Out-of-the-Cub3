#include "../inc/game.h"

void	set_inc_vert(t_game *game, float *increase_x, int *delta_x_to_next_vertical, float *increase_y)
{
	if (game->ray->angle_quad == 1 || game->ray->angle_quad == 4) // ray facing right
	{
		*increase_x = 4 * 8;
		*delta_x_to_next_vertical = 4 * 8; //proceed to the first location on the new block
	}
	else if (game->ray->angle_quad == 2 || game->ray->angle_quad == 3) // ray facing left
	{
		*increase_x = -4 * 8;
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
	while (!is_out_of_bounds(game->ray->inter) && !is_wall_hit(game, game->ray->inter, 1))
	{
		if (game->is_debug)
			safe_put_pixel(game, (int)game->ray->inter.x, (int)game->ray->inter.y, 0xFFFF00FF);
		//printf ("vertical intersect. did not hit wall yet\n");
		//mlx_put_pixel(game->scene, (int)round(game->ray->inter.x) - X_START,  (int)round(game->ray->inter.y) - Y_START, 0xFFFF00FF);
		game->ray->inter.y += increase_y; //the sign was already dealt with
		game->ray->inter.x += increase_x;
		//printf ("inter_x is %f, inter_y is %f\n", game->ray->inter.x, game->ray->inter.y);
	}
	if (is_out_of_bounds(game->ray->inter))
		return (OUT_OF_BOUNDS);
	//printf ("	in the function, game->ray->inter.x is %f and game->ray->inter.y is %f\n", game->ray->inter.x, game->ray->inter.y);
	if (game->is_debug )
		safe_put_pixel(game, (int)game->ray->inter.x, (int)game->ray->inter.y, 0xFFFF00FF);
	game->ray->v_hit.x = game->ray->inter.x;
	game->ray->v_hit.y = game->ray->inter.y;
	//printf ("vertical intersect, end.x is %f and end.y is %f\n", game->ray->v_hit_x = inter_x, game->ray->v_hit_y = inter_y);
	// return (sqrt(pow(game->ray->inter.x - game->camera.pos.x, 2) + 
	// 			pow(game->ray->inter.y - game->camera.pos.y, 2)));
	return (get_distance(game->camera.pos, game->ray->v_hit));
}
