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
	game->is_mmap = false;
	game->is_mouse_active = false;
	game->ray->is_vertical_first = -1;
	game->ray->wall_met = false;
	game->player.pos.x = round((game->player.pos.x + .5) * \
		game->cell_size - PLAYER_SIZE / 2);
	game->player.pos.y = round((game->player.pos.y + .5) * \
		game->cell_size - PLAYER_SIZE / 2);
	game->pplane = SCREEN_WIDTH / (2.0 * tan(FOV * DEG_TO_RAD / 2.0));
	game->camera_pos.x = round(game->player.pos.x) + CAMERA_OFFSET_X;
	game->camera_pos.y = round(game->player.pos.y) + CAMERA_OFFSET_Y;
	game->data->minimap_data.width = \
		game->data->map_data.cols * game->cell_size;
	game->data->minimap_data.height = \
		game->data->map_data.rows * game->cell_size;
	game->data->minimap_data.x_start = 0;
	game->data->minimap_data.x_end = \
		game->data->minimap_data.x_start + game->data->minimap_data.width;
	game->data->minimap_data.y_start = 0;
	game->data->minimap_data.y_end = \
		game->data->minimap_data.y_start + game->data->minimap_data.height;
	load_textures(game);
}
