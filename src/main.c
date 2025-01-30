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
	
	mlx_delete_image(game->mlx, game->stats);
	cast_rays(game);
	if (game->is_mmap)
	{
		draw_grid(game, ROWS, COLS);
		
		int i =0;
		if (game->is_debug == false)
			game->ray->number_of_rays = NUMBER_OF_RAYS;
		else
			game->ray->number_of_rays = 1;
			
		while (i < game->ray->number_of_rays)
		// while (i < 1)
		{
			//printf ("i is %d\n", i);
			bresenham_ray(game, game->camera.pos, game->ray->ray_end[i]);
			i++;
		}
		
		draw_player(game);
		draw_player_direction(game, (t_pos){game->camera.pos.x, game->camera.pos.y}, game->player.angle);
		if (game->stats)
		{
			mlx_delete_image(game->mlx, game->stats);
			print_stats(game);   ///??????
		}
	}
}



int	main(int argc, char *argv[])
{
	t_game	*game;
	// t_data	*data;
	
	(void)argc;
	(void)argv;
	int width, height;
	
	// mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	
	init_game_struct(game);
	if (argc == 2 && ft_strncmp(argv[1], "-d", 3) == 0)
	{
		game->is_debug = true;
		game->is_mmap = true;
	}
	else
		game->is_debug = false;
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Ray caster", true);
	if (!game->mlx)
		return (EXIT_FAILURE);
	mlx_get_monitor_size(0, &width, &height);
	//printf ("width is %d, height is %d\n", width, height);
	
	game->scene = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->scene|| (mlx_image_to_window(game->mlx, game->scene, X_START, Y_START ) < 0))
		return (EXIT_FAILURE);
		
	mlx_loop_hook(game->mlx, draw_all, game);
	mlx_key_hook(game->mlx, key_hook, game);

	mlx_loop(game->mlx);
	clean_nicely(game);
	return(EXIT_SUCCESS);
}
