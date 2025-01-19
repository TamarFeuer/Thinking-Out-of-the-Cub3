
#include "../inc/game.h"

void draw_all(void *param)
{
	t_game *game;
	game = (t_game *)param;
	if (game->rays)
	{
		mlx_delete_image(game->mlx, game->rays);
		game->rays = mlx_new_image(game->mlx, MMAP_WIDTH, MMAP_HEIGHT);
		if (!game->rays|| (mlx_image_to_window(game->mlx, game->rays, X_START, Y_START ) < 0))
			return; //error msg
	}
	// if (game->stats)
	// {
	// 	mlx_delete_image(game->mlx, game->stats);
	// 	game->stats = NULL;
	// }

	draw_player(game);
	cast_rays(game);
	draw_player_direction(game, (t_pos){game->camera.x, game->camera.y}, game->player.angle);
}

int draw_static_components(t_game *game)
{
	if (game->is_mmap)
	{
		printf ("drawing static\n");
		game->grid = mlx_new_image(game->mlx, MMAP_WIDTH, MMAP_HEIGHT);  //!! + 100????
		if (!game->grid|| (mlx_image_to_window(game->mlx, game->grid, X_START, Y_START ) < 0))
			return (EXIT_FAILURE);
		draw_grid(game, ROWS, COLS);
		printf ("count of fill %ld\n", game->fill->count);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	int width, height;
	
	//mlx_set_setting(MLX_STRETCH_IMAGE, true);
	t_game *game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	if (argc == 2 && ft_strncmp(argv[1], "-d", 3) == 0)
		game->debug = true;
	else
		game->debug = false;
	init_game_struct(game);
	
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Ray caster", true);
	if (!game->mlx)
		return (EXIT_FAILURE);
	mlx_get_monitor_size(0, &width, &height);
	//printf ("width is %d, height is %d\n", width, height);
	
	game->rays = mlx_new_image(game->mlx, MMAP_WIDTH, MMAP_HEIGHT);
	if (!game->rays|| (mlx_image_to_window(game->mlx, game->rays, X_START, Y_START ) < 0))
		return (EXIT_FAILURE);
		
	game->scene = mlx_new_image(game->mlx, SCREEN_WIDTH - X_END, SCREEN_HEIGHT - Y_END);
	if (!game->scene|| (mlx_image_to_window(game->mlx, game->scene, X_END, Y_END) < 0))
		return (EXIT_FAILURE);
	

	draw_static_components(game);
	
	mlx_loop_hook(game->mlx, draw_all, game);
	mlx_key_hook(game->mlx, key_hook, game);
	print_stats(game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
