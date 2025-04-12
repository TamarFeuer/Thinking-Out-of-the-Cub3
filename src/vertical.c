#include "../inc/game.h"

double	vertical_intersect(t_game *game)
{
	double	increase_x;
	double	increase_y;

	if (game->ray->tan_current == HUGE_VAL || game->ray->tan_current == -HUGE_VAL)
		return (OUT_OF_BOUNDS);
	if (game->ray->angle_quad == 1 || game->ray->angle_quad == 4)
	{
		game->ray->intersect.x = ceil(game->camera_pos.x / game->cell_size) * game->cell_size;
		game->ray->intersect.y = game->camera_pos.y - (game->ray->intersect.x - game->camera_pos.x) * game->ray->tan_current;
		increase_x = game->cell_size;
		increase_y = -game->cell_size * game->ray->tan_current;
	}
	else
	{
		game->ray->intersect.x = floor(game->camera_pos.x / game->cell_size) * game->cell_size;
		game->ray->intersect.y = game->camera_pos.y - (game->ray->intersect.x - game->camera_pos.x) * game->ray->tan_current;
		increase_x = -game->cell_size;
		increase_y = game->cell_size * game->ray->tan_current;
	}
	while (!is_out_of_bounds(game, game->ray->intersect) && !is_wall_hit(game, game->ray->intersect, INTERSECT_W_VERTICAL))
	{
		game->ray->intersect.x += increase_x;
		game->ray->intersect.y += increase_y;
	}
	if (is_out_of_bounds(game, game->ray->intersect))
		return (OUT_OF_BOUNDS);
	game->ray->v_hit.x = game->ray->intersect.x;
	game->ray->v_hit.y = game->ray->intersect.y;
	return (get_distance(game->camera_pos, game->ray->v_hit));
}
