/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   perspective_scene.c                                 :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/03/18 11:17:21 by rtorrent       #+#    #+#                */
/*   Updated: 2025/03/25 17:24:00 by rtorrent       ########   odam.nl        */
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

static int	horizontal_pixel(int tw, double d)
{
	return ((int)(fmod(d, (double)SCENE_BLOCK_SIZE) * tw / SCENE_BLOCK_SIZE));
}

static uint32_t	pixel_color(t_game *game, int h0, int h, t_pos *end)
{
	const enum e_dir		wall_dir = which_texture(game->ray);
	mlx_texture_t *const	texture = game->textures[wall_dir];
	uint32_t *const			pixels = (uint32_t *)texture->pixels;
	int						x_pixel;
	int						y_pixel;

	if (wall_dir == E)
		x_pixel = texture->width - 1 - horizontal_pixel(texture->width, end->y);
	else if (wall_dir == N)
		x_pixel = texture->width - 1 - horizontal_pixel(texture->width, end->x);
	else if (wall_dir == W)
		x_pixel = horizontal_pixel(texture->width, end->y);
	else
		x_pixel = horizontal_pixel(texture->width, end->x);
	y_pixel = min(
			max(h0 + 2 * h - SCREEN_HEIGHT, 0) * texture->height / (2 * h0),
			texture->height - 1);
	return (color_abgr_to_rgba(pixels[y_pixel * texture->width + x_pixel]));
}

void	draw_scene(t_game *game, t_ray *ray)
{
	const int	h0 = (int)(SCENE_BLOCK_SIZE * game->pplane / ray->distance
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
