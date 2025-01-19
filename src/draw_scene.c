#include "../inc/game.h"
float	get_x_o(mlx_texture_t *texture, t_game *game)
{
	double	x_o;
	
	
	if (!game->ray->found_vertical_first)
		x_o = (int)fmodf((game->ray->end.x *
				(texture->width / SCENE_BLOCK_SIZE)), texture->width);
	else
	 	x_o = (int)fmodf((game->ray->end.y * 
				(texture->width /SCENE_BLOCK_SIZE)), texture->width);
	return (x_o);
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
	x_o = get_x_o(texture, game);
	y_o = (high_pixel - (SCENE_HEIGHT / 2) + (slice_height / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (high_pixel < low_pixel)
	{
		if ((int)y_o >= 0 && (int)y_o < (int)texture->height
			&& (int)x_o >= 0 && (int)x_o < (int)texture->width)
			protected_put_pixel(game, game->ray->ray_n, high_pixel, 
				convert_to_mlx42_endian(arr[(int)y_o * texture->width + (int)x_o]));
		else
			protected_put_pixel(game, game->ray->ray_n, 
				high_pixel, 0x000000FF);
		y_o += factor;
		high_pixel++;
	}
}


void	manage_wall_slice(t_game *game)
{
	float	slice_height;
	int		low_pixel;
	int		high_pixel;
	float	relative_ray_angle;

	relative_ray_angle = game->ray->current_angle - game->player.angle;
	normalize_angle_to_2pi(&relative_ray_angle);
	game->ray->corrected_distance = game->ray->distance * cos(relative_ray_angle);  //fixing fish eye
	
	slice_height = SCENE_BLOCK_SIZE / game->ray->corrected_distance * 
					game->camera.plane_distance;
	low_pixel = SCENE_HEIGHT / 2 + slice_height / 2;
	high_pixel = SCENE_HEIGHT / 2 - slice_height / 2;
	if (high_pixel < 0)
		high_pixel = 0;
	if (low_pixel > SCENE_HEIGHT)
		low_pixel = SCENE_HEIGHT;
	
	wall_drawing(game, slice_height, high_pixel, low_pixel);
	
	// while (low_pixel < SCREEN_HEIGHT)
	// 	mlx_put_pixel(game->scene, 
	// 				game->ray->ray_n, low_pixel++, 0xFF00cc40);
}


void draw_the_thing(t_game *game)
{
	manage_wall_slice(game);
	
}