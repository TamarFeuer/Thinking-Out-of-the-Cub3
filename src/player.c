#include "../inc/game.h"

void	draw_player_direction(t_game *game, t_pos start, double angle)
{
	double	end_x;
	double	end_y;
	double	step_size;
	double	distance;

	end_x = start.x;
	end_y = start.y;
	step_size = .1;
	distance = 0.0;
	while (true)
	{
		end_x += cos(angle) * step_size;
		end_y -= sin(angle) * step_size;
		distance += step_size;
		if (game->data->map[get_block_index(game, &(t_pos){end_x, end_y}, 999)] == '1' || distance > MAX_RAY_DISTANCE)
			return ;
		safe_put_pixel(game, (int)end_x, (int)end_y, distance_to_color(distance, 1));
	}
}

void	draw_player(t_game *game)
{
	int	size;
	int	x;
	int	y;
	int	i;
	int	j;

	size = PLAYER_SIZE;
	x = round(game->player.pos.x);
	y = round(game->player.pos.y);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(game->mini, x + i, y + j, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}
