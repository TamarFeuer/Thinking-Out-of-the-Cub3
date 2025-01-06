#include "../inc/game.h"

static void check_keys_for_movement(t_game *game, mlx_key_data_t keydata)
{
    int new_x = game->player.x;
    int new_y = game->player.y;
	float new_angle = game->player.angle;

    if ((keydata.key == MLX_KEY_W)
        && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        new_y += -2 * CONST;
    if ((keydata.key == MLX_KEY_S)
        && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        new_y += 2 * CONST;
    if ((keydata.key == MLX_KEY_A)
        && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        new_x += -2 * CONST;
    if ((keydata.key == MLX_KEY_D)
        && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        new_x += 2 * CONST;

	 // Boundary check for player movement    
    if (new_x >= X_START && new_x <= X_START + MAP_WIDTH - CONST  &&
        new_y >= Y_START && new_y <= Y_START + MAP_HEIGHT - CONST )
    {
        game->player.x = new_x;
        game->player.y = new_y;
		draw_player(game);
		cast_rays(game);
        print_stats(game);
    }	

    if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        new_angle -= 0.05;  // Rotate counterclockwise (left)
    if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        new_angle += 0.05;  // Rotate clockwise (right)

    // Ensure angle stays within [0, 2 * PI]
    if (new_angle < 0)
        new_angle += 2 * M_PI;  // Wrap around to 2 * PI if below 0
    if (new_angle >= 2 * M_PI)
		new_angle -= 2 * M_PI;  // Wrap around to 0 if 2 * PI or greater

	if (new_angle != game->player.angle)
	{
		game->player.angle = new_angle;
		draw_player(game);
		cast_rays(game);
        print_stats(game);
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		printf("Player pressed ESC. Closing the game...\n"); //change printf

		mlx_close_window(game->mlx);
		clean_nicely(game);
		exit (EXIT_SUCCESS);
	}
	check_keys_for_movement(game, keydata);
	
}