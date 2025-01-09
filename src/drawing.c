#include "../inc/game.h"

mlx_texture_t	*get_texture(t_mlx_data *mlx_data)
{
	mlx_data->ray->current_angle = normalize_angle(mlx_data \
														->ray->current_angle);
	if (!mlx_data->ray->horiz_met_first)
	{
		if (mlx_data->ray->current_angle > PI / 2
			&& mlx_data->ray->current_angle < (3 * PI / 2))
			return (mlx_data->east);
		else
			return (mlx_data->west);
	}
	else
	{
		if (mlx_data->ray->current_angle > 0
			&& mlx_data->ray->current_angle < PI)
			return (mlx_data->south);
		else
			return (mlx_data->north);
	}
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}



mlx_texture_t	*get_texture(t_game *game)
{
	game->ray->current_angle = normalize_angle(game->ray->current_angle);
	if (!game->ray->horiz_met_first)
	{
		if (game->ray->current_angle > M_PI / 2
			&& game->ray->current_angle < (3 * M_PI / 2))
			return (game->east);
		else
			return (game->west);
	}
	else
	{
		if (game->ray->current_angle > 0
			&& game->ray->current_angle < M_PI)
			return (game->south);
		else
			return (game->north);
	}
}

void	wall_drawing(t_game *game, float slice_height, int high_pixel, int low_pixel)
{
	double			x_o;
	double			y_o;
	double			factor;
	uint32_t		*arr;
	mlx_texture_t	*texture;

	texture = get_texture(game);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / slice_height;
	x_o = get_x_o(texture, mlx_data);
	y_o = (high_pixel - (SCREEN_HEIGHT / 2) + (slice_height / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (high_pixel < low_pixel)
	{
		if ((int)y_o >= 0 && (int)y_o < (int)texture->height
			&& (int)x_o >= 0 && (int)x_o < (int)texture->width)
			mlx_put_pixel_special(mlx_data, mlx_data->ray->ray_n, high_pixel, \
				reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
		else
			mlx_put_pixel_special(mlx_data, mlx_data->ray->ray_n, \
				high_pixel, 0x000000FF);
		y_o += factor;
		high_pixel++;
	}
}

void	fill_hex_color(uint32_t *final_color, int *floor_rbg_array, int bright)
{
	*final_color |= (floor_rbg_array[0] & 0xFF) << 24;
	*final_color |= (floor_rbg_array[1] & 0xFF) << 16;
	*final_color |= (floor_rbg_array[2] & 0xFF) << 8;
	*final_color |= (bright & 0xFF);
}

void	manage_wall_slice(t_mlx_data *mlx_data)
{
	float	slice_height;
	int		low_pixel;
	int		high_pixel;
	float	relative_angle;

	relative_angle = normalize_angle(mlx_data->ray->current_angle \
										- mlx_data->camera->angle);
	mlx_data->ray->wall_dst *= cos(relative_angle);
	slice_height = CELL_SIZE / mlx_data->ray->wall_dst * \
											mlx_data->camera->plane_distance;
	low_pixel = SCREEN_HEIGHT / 2 + slice_height / 2;
	high_pixel = SCREEN_HEIGHT / 2 - slice_height / 2;
	if (high_pixel < 0)
		high_pixel = 0;
	if (low_pixel > SCREEN_HEIGHT)
		low_pixel = SCREEN_HEIGHT;
	wall_drawing(mlx_data, slice_height, high_pixel, low_pixel);
	//floor_and_ceiling_drawing(mlx_data, high_pixel, low_pixel);
}




float	get_x_o(mlx_texture_t *texture, t_mlx_data *mlx_data)
{
	double	x_o;

	if (mlx_data->ray->horiz_met_first)
		x_o = (int)fmodf((mlx_data->ray->h_hit_x * \
						(texture->width / CELL_SIZE)), texture->width);
	else
		x_o = (int)fmodf((mlx_data->ray->v_hit_y * \
						(texture->width / CELL_SIZE)), texture->width);
	return (x_o);
}

void	mlx_put_pixel_special(t_mlx_data *mlx_data, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= SCREEN_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= SCREEN_HEIGHT)
		return ;
	mlx_put_pixel(mlx_data->main_image, x, y, color);
}

static void	fill_hex_color(uint32_t *final_color, \
							int *floor_rbg_array, int bright)
{
	*final_color |= (floor_rbg_array[0] & 0xFF) << 24;
	*final_color |= (floor_rbg_array[1] & 0xFF) << 16;
	*final_color |= (floor_rbg_array[2] & 0xFF) << 8;
	*final_color |= (bright & 0xFF);
}

void	floor_and_ceiling_drawing(t_mlx_data *mlx_data, \
									int high_pixel, int low_pixel)
{
	uint32_t	final_color_floor;
	uint32_t	final_color_ceiling;
	int			i;

	final_color_floor = 0;
	final_color_ceiling = 0;
	i = 0;
	fill_hex_color(&final_color_floor, \
					mlx_data->game->floor_rbg_array, 0xAA);
	fill_hex_color(&final_color_ceiling, \
					mlx_data->game->cealing_rbg_array, 0xAA);
	while (low_pixel < SCREEN_HEIGHT)
		mlx_put_pixel(mlx_data->main_image, \
					mlx_data->ray->ray_n, low_pixel++, final_color_floor);
	while (i < high_pixel)
		mlx_put_pixel(mlx_data->main_image, \
					mlx_data->ray->ray_n, i++, final_color_ceiling);
}


float	calc_h_inter(t_mlx_data *mlx_data, float angle)
{
	float	x_inc;
	float	y_inc;
	float	inter_x;
	float	inter_y;
	int		y_add_pixel;

	y_add_pixel = 0;
	x_inc = CELL_SIZE / tan(angle);
	inc_and_pixel_horiz(angle, &y_inc, &y_add_pixel, &x_inc);
	inter_y = floor(mlx_data->camera->pixel_y / CELL_SIZE) * CELL_SIZE + \
															y_add_pixel;
	inter_x = mlx_data->camera->pixel_x + \
						(inter_y - mlx_data->camera->pixel_y) / tan(angle);
	while (!wall_hit_or_out_bounds(mlx_data, inter_y, inter_x, 0))
	{
		inter_y += y_inc;
		inter_x += x_inc;
	}
	mlx_data->ray->h_hit_x = inter_x;
	mlx_data->ray->h_hit_y = inter_y;
	return (sqrt(pow(inter_x - mlx_data->camera->pixel_x, 2) + \
				pow(inter_y - mlx_data->camera->pixel_y, 2)));
}

float	calc_v_inter(t_mlx_data *mlx_data, float angle)
{
	float	x_inc;
	float	y_inc;
	float	inter_x;
	float	inter_y;
	int		x_add_pixel;

	x_add_pixel = 0;
	if (angle == PI / 2 || angle == 3 * PI / 2)
		angle += 0.0001;
	y_inc = CELL_SIZE * tan(angle);
	inc_and_pixel_vert(angle, &x_inc, &x_add_pixel, &y_inc);
	inter_x = floor(mlx_data->camera->pixel_x / CELL_SIZE) * CELL_SIZE + \
															x_add_pixel;
	inter_y = mlx_data->camera->pixel_y + \
						(inter_x - mlx_data->camera->pixel_x) * tan(angle);
	while (!wall_hit_or_out_bounds(mlx_data, inter_y, inter_x, 1))
	{
		inter_y += y_inc;
		inter_x += x_inc;
	}
	mlx_data->ray->v_hit_x = inter_x;
	mlx_data->ray->v_hit_y = inter_y;
	return (sqrt(pow(inter_x - mlx_data->camera->pixel_x, 2) + \
				pow(inter_y - mlx_data->camera->pixel_y, 2)));
}

void	store_info_and_set_distance(t_mlx_data *mlx_data, float h_inter_dist, \
															float v_inter_dist)
{
	if (h_inter_dist < v_inter_dist)
	{
		mlx_data->ray->horiz_met_first = 1;
		mlx_data->ray->wall_dst = h_inter_dist;
		mlx_data->ray->x_final_hit = mlx_data->ray->h_hit_x;
		mlx_data->ray->y_final_hit = mlx_data->ray->h_hit_y;
	}
	else
	{
		mlx_data->ray->horiz_met_first = 0;
		mlx_data->ray->wall_dst = v_inter_dist;
		mlx_data->ray->x_final_hit = mlx_data->ray->v_hit_x;
		mlx_data->ray->y_final_hit = mlx_data->ray->v_hit_y;
	}
}

void	ray_casting(t_mlx_data *mlx_data)
{
	float	h_inter_dist;
	float	v_inter_dist;

	mlx_data->ray->ray_n = 0;
	mlx_data->ray->unit_angle = mlx_data->camera->fov_radi / SCREEN_WIDTH;
	mlx_data->ray->current_angle = normalize_angle(mlx_data->camera->angle - \
	(mlx_data->camera->fov_radi / 2));
	while (mlx_data->ray->ray_n < SCREEN_WIDTH)
	{
		h_inter_dist = calc_h_inter(mlx_data, mlx_data->ray->current_angle);
		v_inter_dist = calc_v_inter(mlx_data, mlx_data->ray->current_angle);
		store_info_and_set_distance(mlx_data, h_inter_dist, v_inter_dist);
		if (mlx_data->game->yes_minimap)
			store_bresenham_coordinates(mlx_data->ray, mlx_data->camera);
		mlx_data->ray->current_angle = normalize_angle(mlx_data->\
								ray->current_angle + mlx_data->ray->unit_angle);
		manage_wall_slice(mlx_data);
		mlx_data->ray->ray_n++;
	}
}