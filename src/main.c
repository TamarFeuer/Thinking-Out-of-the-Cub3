
#include "../inc/game.h"

void init_game_struct(t_game *game)
{
	game->ray = ft_calloc(1, sizeof(t_ray));
	if (!game->ray) //error
		return;
	game->ray->found_vertical_first = -1;
	game->ray->wall_met= false;
	game->screen = NULL;
	game->rays = NULL;
	game->player.p_pos.x = X_START + 48 + 24 - 3;
	game->player.p_pos.y = Y_START + 48 + 24 - 3;
	printf ("player  is %f %f\n", game->player.p_pos.x, game->player.p_pos.y);
	game->player.angle = 0;
	game->player.angle_quad = 1;
	game->camera.x = game->player.p_pos.x + CONST /2;
	game->camera.y = game->player.p_pos.y + CONST /2;
	init_map(game);
	
	
}

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	int width, height;
	
	
	
	//mlx_set_setting(MLX_STRETCH_IMAGE, true);
	t_game *game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	init_game_struct(game);
	
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Ray caster", true);
	if (!game->mlx)
		return (EXIT_FAILURE);
	mlx_get_monitor_size(0, &width, &height);
	printf ("width is %d, height is %d\n", width, height);
	
	// if (game->screen)
	// 	mlx_delete_image(game->mlx, game->screen);
	
	game->screen = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->screen|| (mlx_image_to_window(game->mlx, game->screen, 0, 0) < 0))
		return (EXIT_FAILURE);
	
	game->rays = mlx_new_image(game->mlx, MMAP_WIDTH+ 100, MMAP_HEIGHT+100);
	// if (!game->rays|| (mlx_image_to_window(game->mlx, game->rays, X_START, Y_START ) < 0))
	if (!game->rays|| (mlx_image_to_window(game->mlx, game->rays, X_START, Y_START ) < 0))
		return (EXIT_FAILURE);
		
	// game->scene = mlx_new_image(game->mlx, 1024, 512);
	// if (!game->scene|| (mlx_image_to_window(game->mlx, game->scene, 0, 0) < 0))
	// 	return (EXIT_FAILURE);
	
	draw_grid(game, ROWS, COLS);
	
	draw_player(game);
	
	cast_rays(game);
	print_stats(game);
	

	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);


}
