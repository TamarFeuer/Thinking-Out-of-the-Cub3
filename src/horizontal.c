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
	if (game->ray->angle_quad == 1 || game->ray->angle_quad == 2)
	{
		game->ray->intersect.y = floor(game->camera_pos.y / game->cell_size) * game->cell_size;
		game->ray->intersect.x = game->camera_pos.x - (game->ray->intersect.y - game->camera_pos.y) * cotan_current;
		increase_x = game->cell_size * cotan_current;
		increase_y = -game->cell_size;
	}
	else
	{
		game->ray->intersect.y = ceil(game->camera_pos.y / game->cell_size) * game->cell_size;
		game->ray->intersect.x = game->camera_pos.x - (game->ray->intersect.y - game->camera_pos.y) * cotan_current;
		increase_x = -game->cell_size * cotan_current;
		increase_y = game->cell_size;
	}
	while (!is_out_of_bounds(game, game->ray->intersect) && !is_wall_hit(game, game->ray->intersect, INTERSECT_W_HORIZONTAL))
	{
		game->ray->intersect.x += increase_x;
		game->ray->intersect.y += increase_y;
	}
	if (is_out_of_bounds(game, game->ray->intersect))
		return (OUT_OF_BOUNDS);
	game->ray->h_hit.x = game->ray->intersect.x;
	game->ray->h_hit.y = game->ray->intersect.y;
	return (get_distance(game->camera_pos, game->ray->h_hit));
}
