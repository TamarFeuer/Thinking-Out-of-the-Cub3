#include "../inc/game.h"

int get_block_index(t_game *game, t_pos *grid_pos, t_intersection_flag flag)
{
	t_block_index block_index;

	block_index.x = (int)(grid_pos->x / game->cell_size);
	block_index.y = (int)(grid_pos->y / game->cell_size);
	if (flag == INTERSECT_W_HORIZONTAL && (game->ray->angle_quad == 1 || game->ray->angle_quad == 2))
		block_index.y--;
		
	else if (flag == INTERSECT_W_VERTICAL && (game->ray->angle_quad == 2 || game->ray->angle_quad == 3))
		block_index.x--;
		
	block_index.index = block_index.y * game->data->map_data.cols + block_index.x;
	return (block_index.index);
}

double get_distance(t_pos start, t_pos end)
{
	double dx = end.x - start.x;
	double dy = end.y - start.y;
	return sqrt(dx * dx + dy * dy);
}

void cast_rays(t_game *game)
{
	t_ray *const		ray = game->ray;

	ray->ray_num = 0;
	while (ray->ray_num < SCREEN_WIDTH)
	{	
		ray->relative_angle = atan((SCREEN_WIDTH / 2.0 - ray->ray_num) / game->pplane);
		ray->current_angle = game->player.angle + ray->relative_angle;
		normalize_angle_to_2pi(&ray->current_angle);
		determine_quad(ray->current_angle, &ray->angle_quad);
		ray->tan_current = tan(ray->current_angle);
		reach_nearest_wall_by_intersections(game);
		ray->ray_end[ray->ray_num].x = ray->end.x;
		ray->ray_end[ray->ray_num].y = ray->end.y;

		//draw_ray(game, game->camera.pos, game->ray->end);
		//printf ("in cast_rays: angle is %f\n", game->ray->current_angle);
		draw_scene(game, game->ray);

		ray->ray_num++;
	}
}
