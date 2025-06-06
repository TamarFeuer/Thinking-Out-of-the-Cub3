/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfeuer <tfeuer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:15:05 by tfeuer            #+#    #+#             */
/*   Updated: 2025/04/20 15:03:15 by tfeuer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static void	load_textures(t_game *game)
{
	enum e_dir	dir;
	char		log[LOG];

	dir = E;
	while (dir <= S)
	{
		game->textures[dir]
			= mlx_load_png(game->data->map_data.texture_files[dir]);
		if (!game->textures[dir])
		{
			ft_snprintf(log, LOG, "Unable to load .png texture `%s\'",
				game->data->map_data.texture_files[dir]);
			clean_nicely(game, log);
		}
		dir++;
	}
}

void	init_game_struct(t_game *game)
{
	game->is_mmap = game->is_debug;
	game->is_mouse_active = false;
	game->ray->wall_met = false;
	game->player.pos.x = round((game->player.pos.x + .5) * \
		game->cell_size - PLAYER_SIZE / 2);
	game->player.pos.y = round((game->player.pos.y + .5) * \
		game->cell_size - PLAYER_SIZE / 2);
	game->pplane = SCREEN_WIDTH / (2.0 * tan(FOV * DEG_TO_RAD / 2.0));
	game->camera_pos.x = round(game->player.pos.x) + (PLAYER_SIZE - 1) / 2;
	game->camera_pos.y = round(game->player.pos.y) + (PLAYER_SIZE - 1) / 2;
	if (game->is_debug == false)
		game->number_of_rays = SCREEN_WIDTH;
	else
		game->number_of_rays = 1;
	load_textures(game);
}
