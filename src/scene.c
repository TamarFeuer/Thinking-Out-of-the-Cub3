#include "../inc/game.h"

float	calculate_texture_x_offset(mlx_texture_t *texture, t_game *game)
{
	double	calculated_x_offset;
	
	if (!game->ray->is_vertical_first)
		calculated_x_offset = (int)fmodf((game->ray->end.x *
				(texture->width / (SCENE_BLOCK_SIZE))), texture->width);
	else
	 	calculated_x_offset = (int)fmodf((game->ray->end.y * 
				(texture->width / (SCENE_BLOCK_SIZE))), texture->width);
	return (calculated_x_offset);
}

const char *get_direction(t_game *game)
{
	normalize_angle_to_2pi((double *)&game->ray->current_angle);
	determine_quad(game->ray->current_angle, &game->ray->angle_quad);

	if (game->ray->is_vertical_first == true)
	{
		if (game->ray->angle_quad == 2 || game->ray->angle_quad == 3)
			return "west";
		else if (game->ray->angle_quad == 1 || game->ray->angle_quad == 4)
			return "east";
	}
	else if (game->ray->is_vertical_first == false)
	{
		if (game->ray->angle_quad == 1 || game->ray->angle_quad == 2)
			return "north";
		else if (game->ray->angle_quad == 3 || game->ray->angle_quad == 4)
			return "south";
	}
	return "east";
}

mlx_texture_t	*get_texture(t_game *game)
{
	const char *direction;
	
	direction = get_direction(game);
	if (ft_strncmp(direction, "west", 4) == 0)
		return (game->west);
	else if (ft_strncmp(direction, "north", 4) == 0)
		return (game->north);
	else if (ft_strncmp(direction, "east", 4) == 0)
		return (game->east);
	else
		return (game->south);
}


void	draw_wall_slice(t_game *game, float slice_height, int top_pixel, int low_pixel)
{
	double			horizontal_offset;
	double			vertical_offset;
	double			scale_ratio;
	uint32_t		*pixel_array;
	mlx_texture_t	*texture;

	texture = get_texture(game);
	if (texture == NULL) 
	{
		printf("Error: Texture not found.\n");
		return;
	}
	pixel_array = (uint32_t *)texture->pixels;
	scale_ratio = (double)texture->height / slice_height;
	horizontal_offset = calculate_texture_x_offset(texture, game);
	//printf ("horizontal_offset is %f\n", horizontal_offset);
	vertical_offset = (top_pixel - (SCENE_HEIGHT / 2) + (slice_height / 2)) * scale_ratio;
	if (vertical_offset < 0)
		vertical_offset = 0;
	while (top_pixel < low_pixel)
	{
		if ((int)vertical_offset >= 0 && (int)vertical_offset < (int)texture->height
			&& (int)horizontal_offset >= 0 && (int)horizontal_offset < (int)texture->width)
			safe_put_pixel(game, game->ray->ray_num, top_pixel, 
				convert_to_mlx42_endian(pixel_array[(int)vertical_offset * texture->width + (int)horizontal_offset]));
		//safe_put_pixel(game, game->ray->ray_num, top_pixel, 0xFF8342FC);
		else
			safe_put_pixel(game, game->ray->ray_num, top_pixel, 0x000000FF);
		vertical_offset += scale_ratio;
		top_pixel++;
	}
}

void	draw_vertical_slice(t_game *game)
{
	float	slice_height;
	int		bottom_pixel;
	int		top_pixel;
	float	relative_ray_angle;

	//printf ("current_angle %f\n", game->ray->current_angle);
	relative_ray_angle = game->ray->current_angle - game->player.angle;
	//printf ("relative_ray_angle %f\n", relative_ray_angle);
	normalize_angle_to_2pi((double *)&relative_ray_angle);
	game->ray->corrected_distance = game->ray->distance * cos(relative_ray_angle);  //fixing fish eye
	if (game->ray->corrected_distance < MIN_RAY_DISTANCE)
	game->ray->corrected_distance = MIN_RAY_DISTANCE;
	//printf ("game->camera.frustum_plane_distance is %f\n", game->camera.frustum_plane_distance);
	float aspect_ratio = (float) SCENE_WIDTH / SCENE_HEIGHT;
	
	game->camera.frustum_plane_distance = BASE_FRUSTUM_DISTANCE * aspect_ratio;
	slice_height = (SCENE_BLOCK_SIZE * game->camera.frustum_plane_distance) / (game->ray->corrected_distance + .1);
	//printf ("slice_height is %f\n", slice_height);
	//printf ("game->camera.plane_distance is %f\n", game->camera.plane_distance);
	//printf ("game->ray->corrected_distance is %f\n", game->ray->corrected_distance);
	bottom_pixel = SCENE_HEIGHT / 2 + slice_height / 2;
	//printf ("bottom pixel is %d\n", bottom_pixel);
	top_pixel = SCENE_HEIGHT / 2 - slice_height / 2;
	if (top_pixel < 0)
		top_pixel = 0;
	if (bottom_pixel > SCENE_HEIGHT)
		bottom_pixel = SCENE_HEIGHT;
	
	draw_wall_slice(game, slice_height, top_pixel, bottom_pixel);
	
	while (bottom_pixel < SCREEN_HEIGHT)
		safe_put_pixel(game, game->ray->ray_num, bottom_pixel++, game->data->map_data.floor_color);
	while (top_pixel > 0) 
		safe_put_pixel(game, game->ray->ray_num, --top_pixel, game->data->map_data.ceiling_color);

}
