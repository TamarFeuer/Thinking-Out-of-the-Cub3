#include "../inc/game.h"
float	get_x_offset(mlx_texture_t *texture, t_game *game)
{
	double	x_offset;
	
	
	if (!game->ray->found_vertical_first)
		x_offset = (int)fmodf((game->ray->end.x *
				(texture->width / SCENE_BLOCK_SIZE)), texture->width);
	else
	 	x_offset = (int)fmodf((game->ray->end.y * 
				(texture->width /SCENE_BLOCK_SIZE)), texture->width);
	return (x_offset);
}

mlx_texture_t	*get_texture(t_game *game)
{
	normalize_angle_to_2pi(&game->ray->current_angle);
	determine_quad(game->ray->current_angle, &game->ray->angle_quad);
	if (game->ray->found_vertical_first)
	{
		if (game->ray->current_angle > M_PI / 2
			&& game->ray->current_angle < (3 * M_PI / 2))
	{
			//printf ("west, game->ray->found_vertical_first? %d\n", game->ray->found_vertical_first);
			return (game->west);
	}
		else
		{
			//printf ("east, game->ray->found_vertical_first? %d\n", game->ray->found_vertical_first);
			return (game->east);
		}
	}
	else
	{
		if (game->ray->current_angle > 0
			&& game->ray->current_angle < M_PI)
			{
				//printf ("north, game->ray->found_vertical_first? %d\n", game->ray->found_vertical_first); //why north instead of west?
				return (game->north);
			}
		else
		{
			//printf ("south, game->ray->found_vertical_first? %d\n", game->ray->found_vertical_first);
			return (game->south);
		}
	}
}


void	wall_drawing(t_game *game, float slice_height, int top_pixel, int low_pixel)
{
	double			horizontal_offset;
	double			vertical_offset;
	double			factor;
	uint32_t		*arr;
	mlx_texture_t	*texture;

	texture = get_texture(game);
	if (texture == NULL) 
	{
    	printf("Error: Texture not found.\n");
    	return;
	}
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / slice_height;
	horizontal_offset = get_x_offset(texture, game);
	vertical_offset = (top_pixel - (SCENE_HEIGHT / 2) + (slice_height / 2)) * factor;
	if (vertical_offset < 0)
		vertical_offset = 0;
	while (top_pixel < low_pixel)
	{
		if ((int)vertical_offset >= 0 && (int)vertical_offset < (int)texture->height
			&& (int)horizontal_offset >= 0 && (int)horizontal_offset < (int)texture->width)
			safe_put_pixel(game, game->ray->ray_n, top_pixel, 
				convert_to_mlx42_endian(arr[(int)vertical_offset * texture->width + (int)horizontal_offset]));
		else
			safe_put_pixel(game, game->ray->ray_n, top_pixel, 0x000000FF);
		vertical_offset += factor;
		top_pixel++;
	}
}



void	manage_wall_slice(t_game *game)
{
	float	slice_height;
	int		bottom_pixel;
	int		top_pixel;
	float	relative_ray_angle;

	printf ("current_angle %f\n", game->ray->current_angle);
	relative_ray_angle = game->ray->current_angle - game->player.angle;
	printf ("relative_ray_angle %f\n", relative_ray_angle);
	normalize_angle_to_2pi(&relative_ray_angle);
	game->ray->corrected_distance = game->ray->distance * cos(relative_ray_angle);  //fixing fish eye
	
	slice_height = SCENE_BLOCK_SIZE / game->ray->corrected_distance * game->camera.plane_distance;
	printf ("slice_height is %f\n", slice_height);
	printf ("game->camera.plane_distance is %f\n", game->camera.plane_distance);
	printf ("game->ray->corrected_distance is %f\n", game->ray->corrected_distance);
	bottom_pixel = SCENE_HEIGHT / 2 + slice_height / 2;
	printf ("bottom pixel is %d\n", bottom_pixel);
	top_pixel = SCENE_HEIGHT / 2 - slice_height / 2;
	if (top_pixel < 0)
		top_pixel = 0;
	if (bottom_pixel > SCENE_HEIGHT)
		bottom_pixel = SCENE_HEIGHT;
	
	wall_drawing(game, slice_height, top_pixel, bottom_pixel);
	
	while (bottom_pixel < SCREEN_HEIGHT)
		//mlx_put_pixel(game->scene, game->ray->ray_n, bottom_pixel++, FLOOR_COLOR);
		safe_put_pixel(game, game->ray->ray_n, bottom_pixel++, FLOOR_COLOR);
}


void draw_the_thing(t_game *game)
{
	manage_wall_slice(game);
	
}