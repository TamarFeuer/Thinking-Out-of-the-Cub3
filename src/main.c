
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
	if (game->is_mmap)
		draw_player(game);

	cast_rays(game);
	
	if (game->is_mmap)
		draw_player_direction(game, (t_pos){game->camera.pos.x, game->camera.pos.y}, game->player.angle);
	
}

int draw_static_components(t_game *game)
{
	if (game->is_mmap)
	{
		printf ("drawing static\n");
		game->grid = mlx_new_image(game->mlx, MMAP_WIDTH, MMAP_HEIGHT);
		if (!game->grid|| (mlx_image_to_window(game->mlx, game->grid, X_START, Y_START ) < 0))
			return (EXIT_FAILURE);
		draw_grid(game, ROWS, COLS);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	int width, height;
	
	// mlx_set_setting(MLX_STRETCH_IMAGE, true);
	t_game *game = (t_game *)ft_calloc(1, sizeof(t_game));
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
		
	draw_static_components(game);
	
	mlx_loop_hook(game->mlx, draw_all, game);
	mlx_key_hook(game->mlx, key_hook, game);
	if (game->is_mmap)
		print_stats(game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
