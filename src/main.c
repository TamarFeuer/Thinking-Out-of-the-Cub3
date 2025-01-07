
#include "../inc/game.h"

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_game *game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	game->map = NULL;
	game->rays = NULL;
	game->player.x = X_START + 48 + ((PIXELS_PER_BLOCK /2) - 1) * CONST + 4;
	game->player.y = Y_START + 48 + ((PIXELS_PER_BLOCK /2) - 1) * CONST + 4;
	
	game->player.angle = 0;
	game->mlx = mlx_init(1024, 512, "Mini Map", true);
	if (!game->mlx)
		return (EXIT_FAILURE);
	
	if (game->map)
		mlx_delete_image(game->mlx, game->map);
	game->map = mlx_new_image(game->mlx, 1024, 512);
	if (!game->map|| (mlx_image_to_window(game->mlx, game->map, 0, 0) < 0))
		return (EXIT_FAILURE);
	
	game->rays = mlx_new_image(game->mlx, 1024, 512);
	if (!game->rays|| (mlx_image_to_window(game->mlx, game->rays, 0, 0) < 0))
		return (EXIT_FAILURE);
	
	draw_grid(game, ROWS, COLS);
	draw_player(game);
	cast_rays(game);
	print_stats(game);

	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);


}
