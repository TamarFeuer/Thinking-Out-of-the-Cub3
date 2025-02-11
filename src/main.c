#include "../inc/game.h"

void draw_all(void *param)
{
	t_game *game;
	game = (t_game *)param;
	if (game->scene)
	{
		mlx_delete_image(game->mlx, game->scene);
		game->scene = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (!game->scene|| (mlx_image_to_window(game->mlx, game->scene, 0, 0 ) < 0))
			return; //error msg
	}
	
	cast_rays(game);
	if (game->is_mmap)
	{
		draw_grid(game, game->data->map_data.rows, game->data->map_data.cols);
		
		int i = 0;
		if (game->is_debug == false)
			game->ray->number_of_rays = SCREEN_WIDTH;
		else
			game->ray->number_of_rays = 1;
			
		while (i < game->ray->number_of_rays)
		// while (i < 1)
		{
			draw_bresenham_ray(game, game->camera.pos, game->ray->ray_end[i]);
			i++;
		}
		draw_player(game);
		//printf ("player angle %f\n", game->player.angle);
		draw_player_direction(game, (t_pos){game->camera.pos.x, game->camera.pos.y}, game->player.angle);


		// print_stats(game);
		
	}
}



int	main(int argc, char *argv[])
{
	t_data	*data;
	t_game	*game;
	
	(void)argc;
	(void)argv;
	int width, height;

	data = NULL;
	init_parsed_data_struct(&data, argc, argv);
	parse_file(data, argv[1]);
	game = data->game;
	init_game_struct(data, game);
	// printf ("main: player angle is %f\n", data->player.angle);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Ray caster", true);
	if (!data->game->mlx)
		return (EXIT_FAILURE);
	mlx_get_monitor_size(0, &width, &height);
	//printf ("width is %d, height is %d\n", width, height);
	
	data->game->scene = mlx_new_image(data->game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->game->scene || (mlx_image_to_window(data->game->mlx, data->game->scene, X_START, Y_START ) < 0))
		return (EXIT_FAILURE);
	if(data->game->is_mmap)
		print_stats(data->game);
	mlx_loop_hook(data->game->mlx, draw_all, data->game);
	mlx_key_hook(data->game->mlx, key_hook, data->game);
	
	mlx_loop(data->game->mlx);
	clean_nicely(data->game);
	return(EXIT_SUCCESS);
}
