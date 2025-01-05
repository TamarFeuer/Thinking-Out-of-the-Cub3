
#include "../inc/game.h"

void cast_rays(t_game *game)
{
    float ray_angle;
    float start_angle = game->player.angle - (FOV / 2) * DEG_TO_RAD;
    float end_angle = game->player.angle + (FOV / 2) * DEG_TO_RAD;
    float step = FOV * DEG_TO_RAD / RAY_COUNT;

	mlx_delete_image(game->mlx, game->map);
    game->map = mlx_new_image(game->mlx, 1024, 512);
    if (!game->map || mlx_image_to_window(game->mlx, game->map, 0, 0) < 0)
		return;

	// Loop through the angles from start to end
	ray_angle = start_angle;
    while (ray_angle <= end_angle)
    {
        // Calculate ray direction using trigonometry
        float dx = cos(ray_angle);
        float dy = sin(ray_angle);

        // Starting point of the ray (player position)
        float start_x = game->player.x;
        float start_y = game->player.y;

        // Ending point of the ray (after a fixed length or until collision)
        float end_x = start_x + dx * 300;  // Ray length 300 pixels
        float end_y = start_y + dy * 300;

        // Use Bresenham's line algorithm to cast the ray
        int ver1[2] = {start_x, start_y}; 
        int ver2[2] = {end_x, end_y}; 

        bresenham_line(game, ver1, ver2);
		ray_angle += step;
    }
}

void draw_player(t_game *game)
{
    int size = 2 * CONST;  // Player is 2x2 pixels
    int x = game->player.x;
    int y = game->player.y;

    if (game->player.player_img)
        mlx_delete_image(game->mlx, game->player.player_img);

    game->player.player_img = mlx_new_image(game->mlx, size, size);
    if (!game->player.player_img)
    {
        printf("Failed to create player image.\n");
        return;
    }

	int i = 0;
    while (i < size)
    {
		int j = 0;
        while (j < size)
        {
            mlx_put_pixel(game->player.player_img, i, j, 0xF38080FF);
			j++;
        }
		i++;
    }

    mlx_image_to_window(game->mlx, game->player.player_img, x, y);
}


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
		cast_rays(game);
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
		cast_rays(game);
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
		// exit_nicely(game, NULL);
		exit (EXIT_SUCCESS);
	}
	check_keys_for_movement(game, keydata);
	draw_player(game);
}


void draw_grid(t_game *game, int rows, int cols)
{
    int x, y;

    if (rows <= 0 || cols <= 0)
        return;

    // Drawing horizontal lines
    for (y = 0; y <= rows * 8 * CONST; y += 8 * CONST)
    {
        int x_start = X_START;
        int x_end = X_START + cols * 8 * CONST;
        for (x = x_start; x <= x_end; x++)
            mlx_put_pixel(game->map, x, Y_START + y, 0xFF0000FF);  // Red color
    }

    // Drawing vertical lines
    for (x = 0; x <= cols * 8 * CONST; x += 8 * CONST)
    {
        int y_start = Y_START;
        int y_end = Y_START + rows * 8 * CONST;
        for (y = y_start; y <= y_end; y++)
            mlx_put_pixel(game->map, X_START + x, y, 0xFF0000FF);  // Red color
    }
}





int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_game *game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	game->player.x = X_START;
	game->player.y = Y_START;
	game->mlx = mlx_init(1024, 512, "Pretty grid", true);
	if (!game->mlx)
		return (EXIT_FAILURE);
	
	if (game->map)
		mlx_delete_image(game->mlx, game->map);
	game->map = mlx_new_image(game->mlx, 1024, 512);
	if (!game->map|| (mlx_image_to_window(game->mlx, game->map, 0, 0) < 0))
		return (EXIT_FAILURE);
	
	draw_grid(game, ROWS, COLS);

	draw_player(game);
	cast_rays(game);

	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);

}
