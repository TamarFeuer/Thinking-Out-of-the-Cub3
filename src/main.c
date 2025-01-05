
#include "../inc/game.h"

//mini map
#define X_START 0
#define Y_START 0
#define CONST 6
#define ROWS 8
#define COLS 10

#define FOV 60.0           // Field of View in degrees
#define RAY_COUNT 120      // Number of rays to cast (adjust for resolution)
#define M_PI 3.14159265358979323846
#define DEG_TO_RAD (M_PI / 180.0)

#define MAX_RAY_LENGTH 300


void cast_rays(t_game *game)
{
    float ray_angle;
    float start_angle = game->player.angle - (FOV / 2) * DEG_TO_RAD;
    float end_angle = game->player.angle + (FOV / 2) * DEG_TO_RAD;
    float step = FOV * DEG_TO_RAD / RAY_COUNT;

    // Loop through the angles from start to end
    for (ray_angle = start_angle; ray_angle <= end_angle; ray_angle += step)
    {
        // Example: Calculate ray direction using trigonometry
        float dx = cos(ray_angle);
        float dy = sin(ray_angle);

        // Traverse and draw the ray
        float x = game->player.x;
        float y = game->player.y;
        
        float ray_length = 0;
        float max_ray_length = 300;  // Maximum ray length in pixels
        float step_size = 1.0;  // How much the ray steps per iteration

        while (ray_length < max_ray_length)  // Limit the ray's length
        {
            // Check for bounds or collisions here (if required)
            // if (collision_detected(x, y)) break;

            mlx_put_pixel(game->map, (int)x, (int)y, 0xFFFFFF00);  // Draw ray in yellow
            x += dx * step_size;  // Move ray in x direction
            y += dy * step_size;  // Move ray in y direction

            ray_length += step_size;  // Increment ray length
        }
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


static void	check_keys_for_movement(t_game *game, mlx_key_data_t keydata)
{
    int new_x = game->player.x;
    int new_y = game->player.y;

    if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
        && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        new_y += -2 * CONST;
    if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
        && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        new_y += 2 * CONST;
    if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
        && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        new_x += -2 * CONST;
    if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
        && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        new_x += 2 * CONST;

    // Check boundaries
    int grid_width = COLS * 8 * CONST;
    int grid_height = ROWS * 8 * CONST;
    
    if (new_x >= X_START && new_x <= X_START + grid_width - CONST  &&
        new_y >= Y_START && new_y <= Y_START + grid_height - CONST )
    {
        game->player.x = new_x;
        game->player.y = new_y;
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
	// cast_rays(game);

	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);

}
