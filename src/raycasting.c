/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfeuer <tfeuer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:14:57 by tfeuer            #+#    #+#             */
/*   Updated: 2025/04/20 15:41:35 by tfeuer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

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

void	cast_rays(t_game *game)
{
	t_ray *const		ray = game->ray;

	ray->ray_num = 0;
	while (ray->ray_num < game->number_of_rays)
	{
		ray->relative_angle = atan((SCREEN_WIDTH / 2.0 - ray->ray_num) / \
			game->pplane);
		if (game->is_debug == true)
			ray->relative_angle = 0;
		ray->current_angle = game->player.angle + ray->relative_angle;
		normalize_angle_to_2pi(&ray->current_angle);
		determine_quad(ray->current_angle, &ray->angle_quad);
		ray->tan_current = tan(ray->current_angle);
		reach_nearest_wall_by_intersections(game);
		game->ray_end[ray->ray_num].x = ray->end.x;
		game->ray_end[ray->ray_num].y = ray->end.y;
		draw_scene(game, game->ray);
		ray->ray_num++;
	}
}
