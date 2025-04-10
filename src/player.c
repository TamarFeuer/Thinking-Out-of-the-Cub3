#include "../inc/game.h"

void draw_player_direction(t_game *game, t_pos start, double angle)
{
	
	double end_x = start.x;
	double end_y = start.y;
	double step_size = .1;
	double distance = 0.0;
	while (1)
	{
		end_x += cos(angle) * step_size;
		end_y -= sin(angle) * step_size;
		distance += step_size;
		// if (game->mapdata[get_block_index(&(t_pos){end_x, end_y})] == '1')
		if (game->data->map[get_block_index(game, &(t_pos){end_x, end_y}, 999)] == '1' || distance > MAX_RAY_DISTANCE)
			return;
		mlx_put_pixel(game->mini, (int)end_x, (int)end_y, distance_to_color(distance, 1));
	}
}

void draw_player(t_game *game)
{
	int size = PLAYER_SIZE * CONST; // Player is PLAYER_SIZE x PLAYER_SIZE pixels
	int x = round(game->player.pos.x);
	int y = round(game->player.pos.y);

	// mlx_image_to_window(game->mlx, game->mini, X_START, Y_START);
	int i = 0;
	while (i < size)
	{
		int j = 0;
		while (j < size)
		{
			mlx_put_pixel(game->mini, x + i, y + j, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}
