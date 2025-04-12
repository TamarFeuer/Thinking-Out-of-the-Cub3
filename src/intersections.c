#include "../inc/game.h"

bool	is_out_of_bounds(t_game *game, t_pos position)
{
	if (position.y < 0 || position.x < 0 || position.y >= game->data->map_data.rows * game->cell_size || position.x >= game->data->map_data.cols * game->cell_size)
		return (true);
	return (false);
}

int	is_wall_hit(t_game *game, t_pos inter, t_intersection_flag flag)
{
	return (game->data->map[get_block_index(game, &inter, flag)] == '1');
}

void	reach_nearest_wall_by_intersections(t_game *game)
{
	double	horiz_distance;
	double	vertical_distance;

	horiz_distance = horiz_intersect(game);
	vertical_distance = vertical_intersect(game);
	if (horiz_distance > vertical_distance)
	{
		game->ray->is_vertical_first = true;
		game->ray->end.x = game->ray->v_hit.x;
		game->ray->end.y = game->ray->v_hit.y;
		game->ray->distance = vertical_distance;
	}
	else
	{
		game->ray->is_vertical_first = false;
		game->ray->end.x = game->ray->h_hit.x;
		game->ray->end.y = game->ray->h_hit.y;
		game->ray->distance = horiz_distance;
	}
}
