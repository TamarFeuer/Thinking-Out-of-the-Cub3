/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   perspective_scene.c                                 :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/03/18 11:17:21 by rtorrent       #+#    #+#                */
/*   Updated: 2025/03/18 12:49:23 by rtorrent       ########   odam.nl        */
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
	const int		h0 = (int)(SCREEN_HEIGHT / ray->distance);
	const int		h[2] = {min((SCREEN_HEIGHT - h0) / 2, SCREEN_HEIGHT - 1),
			max((SCREEN_HEIGHT - h0) / 2, 0)};
	int				y;

	y = 0;
	while (y < h[CE])
		safe_put_pixel(game, ray->ray_num, y++, game->data->map_data.rgba[CE]);
	while (y < h[FL])
		safe_put_pixel(game, ray->ray_num, y++, 0x0000FF00);
	while (y < SCREEN_HEIGHT)
		safe_put_pixel(game, ray->ray_num, y++, game->data->map_data.rgba[FL]);
}
