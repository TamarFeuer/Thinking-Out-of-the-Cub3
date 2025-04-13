#include "../inc/game.h"

bool is_out_of_bounds(t_game *game, t_vec2 position)
{
	if (position.y < 0 || position.x < 0 || position.y >= game->data->map_data.rows * game->cell_size || position.x >= game->data->map_data.cols * game->cell_size)
	{
		//printf ("out of bounds\n");
		return (true);
	}
	return (false);
}

// int	is_wall_hit(t_game *game, t_vec2 inter)
// {
// 	if (game->mapdata[get_block_index(&inter)] == 1)
// 	{	
// 		//printf ("game->ray->end.x %f, game->ray->end.y %f\n", game->ray->end.x, game->ray->end.y);
// 		//printf ("hit wall\n");
// 		return (true);
// 	}
// 	return (false);
// }

int	is_wall_hit(t_game *game, t_vec2 inter, t_intersect_type intersect_type)
{
	return (game->data->map[get_block_index(game, &inter, intersect_type)] == '1');
}

void reach_nearest_wall_by_intersections(t_game *game)
{
	double	horiz_distance, vertical_distance;
	
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

bool	should_continue_stepping(t_game *game, t_vec2 intersect, \
	t_intersect_type intersect_type)
{
	if (is_out_of_bounds(game, intersect))
		return (false);
	if (is_wall_hit(game, intersect, intersect_type))
		return (false);
	return (true);
}
