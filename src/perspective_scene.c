/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   perspective_scene.c                                 :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/03/18 11:17:21 by rtorrent       #+#    #+#                */
/*   Updated: 2025/03/18 16:52:28 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	draw_scene(t_game *game)
{
	t_ray *const	ray = game->ray;
	const int		h0 = (int)(SCREEN_HEIGHT / ray->distance
			/ cos(ray->relative_angle));
	const int		h[2] = {min((SCREEN_HEIGHT + h0) / 2, SCREEN_HEIGHT - 1),
			max((SCREEN_HEIGHT - h0) / 2, 0)};
	int				y;

/*
	if (ray->ray_num == SCREEN_WIDTH / 2) {
		printf("** FRUSTRUM %f\n", FRUSTUM_PLANE);
		printf("   SCREEN HEIGHT %d\n", SCREEN_HEIGHT);
		printf("   ray->distance %f\n", ray->distance);
		printf("   ray->relative_angle %f\n", ray->relative_angle * 180 / M_PI);
		printf("   ray->current_angle %f\n", ray->current_angle * 180 / M_PI);
		printf("   h0 %d\n", h0);
		printf("   h[CE] %d\n", h[CE]);
		printf("   h[FL] %d\n", h[FL]);
	}
*/
	y = 0;
	while (y < h[CE])
		safe_put_pixel(game, ray->ray_num, y++, game->data->map_data.rgba[CE]);
	while (y <= h[FL])
		safe_put_pixel(game, ray->ray_num, y++, 0xFF0000FF);
	while (y < SCREEN_HEIGHT)
		safe_put_pixel(game, ray->ray_num, y++, game->data->map_data.rgba[FL]);
}
