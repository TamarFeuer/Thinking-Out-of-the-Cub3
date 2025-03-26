/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   perspective_scene.c                                 :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/03/18 11:17:21 by rtorrent       #+#    #+#                */
/*   Updated: 2025/03/26 12:06:55 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static enum e_dir	which_texture(t_ray *ray)
{
	if (ray->is_vertical_first)
	{
		if (ray->angle_quad == 1 || ray->angle_quad == 4)
			return (W);
		else
			return (E);
	}
	if (ray->angle_quad == 1 || ray->angle_quad == 2)
		return (S);
	return (N);
}

static uint32_t	pixel_color(t_game *game, int h0, int h, t_pos *end)
{
	const enum e_dir		wall_dir = which_texture(game->ray);
	mlx_texture_t *const	t = game->textures[wall_dir];
	uint32_t *const			pixels = (uint32_t *)t->pixels;
	int						x_pixel;
	int						y_pixel;

	if (wall_dir == E)
		x_pixel = t->width - 1 - (int)(fmod(end->y,
					(double)game->cell_size) * t->width / game->cell_size);
	else if (wall_dir == N)
		x_pixel = t->width - 1 - (int)(fmod(end->x,
					(double)game->cell_size) * t->width / game->cell_size);
	else if (wall_dir == W)
		x_pixel = (int)(fmod(end->y,
					(double)game->cell_size) * t->width / game->cell_size);
	else
		x_pixel = (int)(fmod(end->x,
					(double)game->cell_size) * t->width / game->cell_size);
	y_pixel = min(
			max(h0 + 2 * h - SCREEN_HEIGHT, 0) * t->height / (2 * h0),
			t->height - 1);
	return (color_abgr_to_rgba(pixels[y_pixel * t->width + x_pixel]));
}

void	draw_scene(t_game *game, t_ray *ray)
{
	const int	h0 = (int)(game->cell_size * game->pplane / ray->distance
			/ cos(ray->relative_angle));
	const int	h[2] = {min((SCREEN_HEIGHT + h0) / 2, SCREEN_HEIGHT - 1),
		max((SCREEN_HEIGHT - h0) / 2, 0)};
	int			y;

	y = 0;
	while (y < h[CE])
		safe_put_pixel(game, ray->ray_num, y++, game->data->map_data.rgba[CE]);
	while (y <= h[FL] && h0)
	{
		safe_put_pixel(game, ray->ray_num, y,
			pixel_color(game, h0, y, &ray->end));
		y++;
	}
	while (y < SCREEN_HEIGHT)
		safe_put_pixel(game, ray->ray_num, y++, game->data->map_data.rgba[FL]);
}
