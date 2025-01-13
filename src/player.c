#include "../inc/game.h"

void draw_player_direction(t_game *game, t_pos start, double angle)
{
	// if (game->rays)
	// 	mlx_delete_image(game->mlx, game->rays);

	// game->rays = mlx_new_image(game->mlx, MMAP_WIDTH, MMAP_HEIGHT);  //+ 100
	// if (!game->rays|| (mlx_image_to_window(game->mlx, game->rays ,X_START, Y_START) < 0))
	// 	return; //error msg
	double end_x = start.x;
	double end_y = start.y;
	double step_size = .1;
	double distance = 0.0;
	while (distance < PLAYER_DIRECTION_SIZE)
	{
		end_x += cos(angle) * step_size;
		end_y -= sin(angle) * step_size;
		distance += step_size;
		if (game->mapdata[get_block_index(&(t_pos){end_x, end_y})] == 1)
			return;
		mlx_put_pixel(game->rays, (int)end_x - X_START, (int)end_y - Y_START, 0xFF0000FF);
	}
}

void draw_player(t_game *game)
{
	int size = PLAYER_SIZE * CONST; // Player is PLAYER_SIZE x PLAYER_SIZE pixels
	int x = round(game->player.p_pos.x);
	int y = round(game->player.p_pos.y);
	printf ("y is %d\n", y);

	if (game->rays)
		mlx_delete_image(game->mlx, game->rays);

	game->rays = mlx_new_image(game->mlx, MMAP_WIDTH, MMAP_HEIGHT);
	if (!game->rays)
	{
		printf("Failed to create player image.\n");
		return;
	}
	mlx_image_to_window(game->mlx, game->rays, X_START, Y_START);
	int i = 0;
	while (i < size)
	{
		printf ("dsfsdf\n");
		int j = 0;
		while (j < size)
		{
			//mlx_put_pixel(game->rays, i + x - X_START, j + y - Y_START, 0xC8A2C8FF);
			mlx_put_pixel(game->rays, (x - X_START) + i, (y - Y_START) + j, 0xC8A2C8FF);
			j++;
		}
		i++;
	}
}