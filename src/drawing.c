#include "../inc/game.h"

// mlx_texture_t	*get_texture(t_game *game)
// {
// 	game->ray->current_angle = normalize_angle(game->ray->current_angle);
// 	if (!game->ray->found_vertical_first) //here i changed horiz to vertical
// 	{
// 		if (game->ray->current_angle > M_PI / 2
// 			&& game->ray->current_angle < (3 * M_PI / 2))
// 			return (game->east);
// 		else
// 			return (game->west);
// 	}
// 	else
// 	{
// 		if (game->ray->current_angle > 0
// 			&& game->ray->current_angle < M_PI)
// 			return (game->south);
// 		else
// 			return (game->north);
// 	}
// }

// int	reverse_bytes(int c)
// {
// 	unsigned int	b;

// 	b = 0;
// 	b |= (c & 0xFF) << 24;
// 	b |= (c & 0xFF00) << 8;
// 	b |= (c & 0xFF0000) >> 8;
// 	b |= (c & 0xFF000000) >> 24;
// 	return (b);
// }



// mlx_texture_t	*get_texture(t_game *game)
// {
// 	game->ray->current_angle = normalize_angle(game->ray->current_angle);
// 	if (!game->ray->found_vertical_first) ///changed this from horiz to vertical
// 	{
// 		if (game->ray->current_angle > M_PI / 2
// 			&& game->ray->current_angle < (3 * M_PI / 2))
// 			return (game->east);
// 		else
// 			return (game->west);
// 	}
// 	else
// 	{
// 		if (game->ray->current_angle > 0
// 			&& game->ray->current_angle < M_PI)
// 			return (game->south);
// 		else
// 			return (game->north);
// 	}
// }

// void	wall_drawing(t_game *game, float slice_height, int high_pixel, int low_pixel)
// {
// 	double			x_o;
// 	double			y_o;
// 	double			factor;
// 	uint32_t		*arr;
// 	mlx_texture_t	*texture;

// 	texture = get_texture(game);
// 	arr = (uint32_t *)texture->pixels;
// 	factor = (double)texture->height / slice_height;
// 	x_o = get_x_o(texture, game);
// 	y_o = (high_pixel - (SCREEN_HEIGHT / 2) + (slice_height / 2)) * factor;
// 	if (y_o < 0)
// 		y_o = 0;
// 	while (high_pixel < low_pixel)
// 	{
// 		if ((int)y_o >= 0 && (int)y_o < (int)texture->height
// 			&& (int)x_o >= 0 && (int)x_o < (int)texture->width)
// 			mlx_put_pixel_special(game, game->ray->ray_n, high_pixel, \
// 				reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
// 		else
// 			mlx_put_pixel_special(game, game->ray->ray_n, \
// 				high_pixel, 0x000000FF);
// 		y_o += factor;
// 		high_pixel++;
// 	}
// }

// void	fill_hex_color(uint32_t *final_color, int *floor_rbg_array, int bright)
// {
// 	*final_color |= (floor_rbg_array[0] & 0xFF) << 24;
// 	*final_color |= (floor_rbg_array[1] & 0xFF) << 16;
// 	*final_color |= (floor_rbg_array[2] & 0xFF) << 8;
// 	*final_color |= (bright & 0xFF);
// }

// void	manage_wall_slice(t_game *game)
// {
// 	float	slice_height;
// 	int		low_pixel;
// 	int		high_pixel;
// 	float	relative_angle;

// 	relative_angle = normalize_angle(game->ray->current_angle \
// 										- game->camera->angle);  //game->camera->angle ??
// 	game->ray->wall_dst *= cos(relative_angle);
// 	slice_height = CELL_SIZE / game->ray->wall_dst * \
// 											game->camera->plane_distance;
// 	low_pixel = SCREEN_HEIGHT / 2 + slice_height / 2;
// 	high_pixel = SCREEN_HEIGHT / 2 - slice_height / 2;
// 	if (high_pixel < 0)
// 		high_pixel = 0;
// 	if (low_pixel > SCREEN_HEIGHT)
// 		low_pixel = SCREEN_HEIGHT;
// 	wall_drawing(game, slice_height, high_pixel, low_pixel);
// 	//floor_and_ceiling_drawing(game, high_pixel, low_pixel);
// }




// float	get_x_o(mlx_texture_t *texture, t_game *game)
// {
// 	double	x_o;

// 	if (game->ray->found_vertical_first )  //changed from horiz to vertical
// 		x_o = (int)fmodf((game->ray->h_hit_x * \
// 						(texture->width / CELL_SIZE)), texture->width);
// 	else
// 		x_o = (int)fmodf((game->ray->v_hit_y * \
// 						(texture->width / CELL_SIZE)), texture->width);
// 	return (x_o);
// }

// void	mlx_put_pixel_special(game *game, int x, int y, int color)
// {
// 	if (x < 0)
// 		return ;
// 	else if (x >= SCREEN_WIDTH)
// 		return ;
// 	if (y < 0)
// 		return ;
// 	else if (y >= SCREEN_HEIGHT)
// 		return ;
// 	mlx_put_pixel(game->main_image, x, y, color);
// }

// static void	fill_hex_color(uint32_t *final_color, \
// 							int *floor_rbg_array, int bright)
// {
// 	*final_color |= (floor_rbg_array[0] & 0xFF) << 24;
// 	*final_color |= (floor_rbg_array[1] & 0xFF) << 16;
// 	*final_color |= (floor_rbg_array[2] & 0xFF) << 8;
// 	*final_color |= (bright & 0xFF);
// }

// void	floor_and_ceiling_drawing(t_game *game, \
// 									int high_pixel, int low_pixel)
// {
// 	uint32_t	final_color_floor;
// 	uint32_t	final_color_ceiling;
// 	int			i;

// 	final_color_floor = 0;
// 	final_color_ceiling = 0;
// 	i = 0;
// 	fill_hex_color(&final_color_floor, \
// 					game->floor_rbg_array, 0xAA);
// 	fill_hex_color(&final_color_ceiling, \
// 					game->cealing_rbg_array, 0xAA);
// 	while (low_pixel < SCREEN_HEIGHT)
// 		mlx_put_pixel(game->main_image, \
// 					game->ray->ray_n, low_pixel++, final_color_floor);
// 	while (i < high_pixel)
// 		mlx_put_pixel(game->main_image, \
// 					game->ray->ray_n, i++, final_color_ceiling);
// }


// float	calc_h_inter(game *game, float angle)
// {
// 	float	x_inc;
// 	float	y_inc;
// 	float	inter_x;
// 	float	inter_y;
// 	int		y_add_pixel;

// 	y_add_pixel = 0;
// 	x_inc = CELL_SIZE / tan(angle);
// 	inc_and_pixel_horiz(angle, &y_inc, &y_add_pixel, &x_inc);
// 	inter_y = floor(game->camera->pixel_y / CELL_SIZE) * CELL_SIZE + \
// 															y_add_pixel;
// 	inter_x = game->camera->pixel_x + \
// 						(inter_y - game->camera->pixel_y) / tan(angle);
// 	while (!wall_hit_or_out_bounds(game, inter_y, inter_x, 0))
// 	{
// 		inter_y += y_inc;
// 		inter_x += x_inc;
// 	}
// 	game->ray->h_hit_x = inter_x;
// 	game->ray->h_hit_y = inter_y;
// 	return (sqrt(pow(inter_x - game->camera->pixel_x, 2) + \
// 				pow(inter_y - game->camera->pixel_y, 2)));
// }

// float	calc_v_inter(t_game *game, float angle)
// {
// 	float	x_inc;
// 	float	y_inc;
// 	float	inter_x;
// 	float	inter_y;
// 	int		x_add_pixel;

// 	x_add_pixel = 0;
// 	if (angle == M_PI / 2 || angle == 3 * M_PI / 2)
// 		angle += 0.0001;
// 	y_inc = CELL_SIZE * tan(angle);
// 	inc_and_pixel_vert(angle, &x_inc, &x_add_pixel, &y_inc);
// 	inter_x = floor(game->camera->pixel_x / CELL_SIZE) * CELL_SIZE + \
// 															x_add_pixel;
// 	inter_y = game->camera->pixel_y + \
// 						(inter_x - game->camera->pixel_x) * tan(angle);
// 	while (!wall_hit_or_out_bounds(game, inter_y, inter_x, 1))
// 	{
// 		inter_y += y_inc;
// 		inter_x += x_inc;
// 	}
// 	game->ray->v_hit_x = inter_x;
// 	game->ray->v_hit_y = inter_y;
// 	return (sqrt(pow(inter_x - game->camera->pixel_x, 2) + \
// 				pow(inter_y - game->camera->pixel_y, 2)));
// }

// void	store_info_and_set_distance(t_game *game, float h_inter_dist, \
// 															float v_inter_dist)
// {
// 	if (h_inter_dist < v_inter_dist)
// 	{
// 		game->ray->found_vertical_first = 1;  //changed from horiz to vertical
// 		game->ray->wall_dst = h_inter_dist;
// 		game->ray->x_final_hit = game->ray->h_hit_x;
// 		game->ray->y_final_hit = game->ray->h_hit_y;
// 	}
// 	else
// 	{
// 		game->ray->horiz_met_first = 0;
// 		game->ray->wall_dst = v_inter_dist;
// 		game->ray->x_final_hit = game->ray->v_hit_x;
// 		game->ray->y_final_hit = game->ray->v_hit_y;
// 	}
// }

// void	ray_casting(t_game *game)
// {
// 	float	h_inter_dist;
// 	float	v_inter_dist;

// 	game->ray->ray_n = 0;
// 	game->ray->unit_angle = game->camera->fov_radi / SCREEN_WIDTH;
// 	game->ray->current_angle = normalize_angle(game->camera->angle - \
// 	(game->camera->fov_radi / 2));
// 	while (game->ray->ray_n < SCREEN_WIDTH)
// 	{
// 		h_inter_dist = calc_h_inter(game, game->ray->current_angle);
// 		v_inter_dist = calc_v_inter(game, game->ray->current_angle);
// 		store_info_and_set_distance(game, h_inter_dist, v_inter_dist);
// 		if (game->game->yes_minimap)
// 			store_bresenham_coordinates(game->ray, game->camera);
// 		game->ray->current_angle = normalize_angle(game->\
// 								ray->current_angle + game->ray->unit_angle);
// 		manage_wall_slice(game);
// 		game->ray->ray_n++;
// 	}
// }


void draw_the_thing(t_game *game)
{
	
	game->scene = mlx_new_image(game->mlx, 1024, 512);
	if (!game->scene|| (mlx_image_to_window(game->mlx, game->scene, 0, 0) < 0))
		return (EXIT_FAILURE);
}