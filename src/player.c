#include "../inc/game.h"

void draw_player_direction(t_game *game, t_vec2 start, double angle)
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
		if (game->data->map[get_block_index(game, &(t_vec2){end_x, end_y}, INTERSECT_NONE)] == '1' || distance > MAX_RAY_DISTANCE)
			return;
		put_pixel_mmap(game, (int)end_x, (int)end_y, distance_to_color(distance, PLAYER_DIRECTION));
	}
}

void draw_player(t_game *game)
{
	int size = PLAYER_SIZE;
	int x = round(game->player.pos.x);
	int y = round(game->player.pos.y);

	// mlx_image_to_window(game->mlx, game->mini, X_START, Y_START);
	int i = 0;
	while (i < size)
	{
		int j = 0;
		while (j < size)
		{
			put_pixel_mmap(game, x + i, y + j, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}
