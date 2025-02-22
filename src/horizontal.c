#include "../inc/game.h"

void	set_inc_horiz(t_game *game, float *increase_y, int *delta_y_to_next_horiz, float *increase_x)
{
	(void)increase_x;
	if (game->ray->angle_quad == 3 || game->ray->angle_quad == 4) //ray facing down
	{
		*increase_y = game->cell_size;
		*delta_y_to_next_horiz = game->cell_size; //proceed to the first location on the new block
	}
	else if (game->ray->angle_quad == 1 || game->ray->angle_quad == 2) //ray facing up
	{
		*increase_y = -game->cell_size;
		*delta_y_to_next_horiz =  -1; //proceed to the last location on the new block
	}
	if (game->ray->angle_quad == 3 || game->ray->angle_quad == 4)
		*increase_x *= -1;
	
}

float	horiz_intersect(t_game *game, float angle)
{
	float	increase_x;
	float	increase_y;
	int		delta_y_to_next_horiz;
	
	printf ("\nHORIZONTAL:\n");
	delta_y_to_next_horiz = 0;
	increase_x = game->cell_size / tan(angle);
	set_inc_horiz(game, &increase_y, &delta_y_to_next_horiz, &increase_x);
	printf ("increase_x is %f\n", increase_x);
	printf ("increase_y is %f, delta_y_to_next_horiz is %d, \n", increase_y, delta_y_to_next_horiz);
	
	game->ray->intersect.y = floor((game->camera.pos.y - Y_START) / (game->cell_size)) * (game->cell_size) + delta_y_to_next_horiz;
	printf ("game->ray->inter.y %f\n", game->ray->intersect.y);
	printf ("game->camera.pos.x %f\n", game->camera.pos.x);
	printf ("game->camera.pos.y %f, floor(game->camera.pos.y / (game->cell_size)) %f\n", game->camera.pos.y, floor(game->camera.pos.y / (game->cell_size)));
	game->ray->intersect.x = (game->camera.pos.x - X_START) - (game->ray->intersect.y - game->camera.pos.y) / tan(angle);
	//printf ("game->ray->inter.x %f\n", game->ray->inter.x);
	
	while (!is_out_of_bounds(game, game->ray->intersect) && !is_wall_hit(game, game->ray->intersect, 0))
	{
		if (game->is_debug )
			safe_put_pixel(game, (int)game->ray->intersect.x, (int)game->ray->intersect.y, 0xFF00FFFF);
		//mlx_put_pixel(game->scene, (int)round(game->ray->inter.x) - X_START, (int)round(game->ray->inter.y) - Y_START, 0xFF0000FF);
		printf ("horiz intersect: did not hit wall yet\n");
		game->ray->intersect.y += increase_y;
		game->ray->intersect.x += increase_x;
	}
	if (is_out_of_bounds(game, game->ray->intersect))
		return (OUT_OF_BOUNDS);
	if (game->is_debug )
		safe_put_pixel(game, (int)game->ray->intersect.x, (int)game->ray->intersect.y, 0xFF00FFFF);
	game->ray->h_hit.x = game->ray->intersect.x;
	game->ray->h_hit.y = game->ray->intersect.y;
	printf ("horiz intersectsect: end.x is %f and end.y is %f\n", game->ray->h_hit.x, game->ray->h_hit.y = game->ray->h_hit.x);
	// return (sqrt(pow(game->ray->intersect.x - game->camera.pos.x, 2) + 
	// 			pow(game->ray->intersect.y - game->camera.pos.y, 2)));
	return (get_distance(game->camera.pos, game->ray->h_hit));
}