/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfeuer <tfeuer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:14:27 by tfeuer            #+#    #+#             */
/*   Updated: 2025/04/17 18:14:28 by tfeuer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	draw_player_direction(t_game *game, t_vec2 start, double angle)
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
		if (game->data->map[get_block_index(game, &(t_vec2){end_x, end_y}, \
			INTERSECT_NONE)] == '1' || distance > MAX_RAY_DISTANCE)
			return ;
		put_pixel_mmap(game, (int)end_x, (int)end_y, \
		distance_to_color(distance, PLAYER_DIRECTION));
	}
}

void	draw_player(t_game *game)
{
	int	i;
	int	j;
	int	size;
	int	x;
	int	y;

	size = PLAYER_SIZE;
	x = round(game->player.pos.x);
	y = round(game->player.pos.y);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_mmap(game, x + i, y + j, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}
