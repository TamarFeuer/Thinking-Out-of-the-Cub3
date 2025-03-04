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

void init_game_struct(t_game *game)
{
	game->is_mmap = true;
	game->is_mouse_active = false;
	game->ray->is_vertical_first = -1;
	game->ray->wall_met= false;
	game->scene = NULL;
	game->stats = NULL;
	game->player.p_pos.x = round(X_START + (game->player.p_pos.x + .5) * game->cell_size - CONST/2);
	game->player.p_pos.y = round(Y_START + (game->player.p_pos.y + .5) * game->cell_size - CONST/2);
	printf ("player  is %f %f\n", game->player.p_pos.x, game->player.p_pos.y);
	printf ("in init game struct: game->player.angle is %f\n", game->player.angle);

	game->ray->intersect.x = 0;
	game->ray->intersect.y = 0;
	game->camera.pos.x = round(game->player.p_pos.x + (PLAYER_SIZE + CONST) /2);
	game->camera.pos.y = round(game->player.p_pos.y + (PLAYER_SIZE + CONST) /2);
	printf ("in init game struct: game->camera.pos.x %f\n", game->camera.pos.x);
	game->camera.frustum_plane_distance = SCREEN_WIDTH / 2 * (tan(FOV * DEG_TO_RAD/ 2));
	//game->camera.frustum_plane_distance = SCREEN_WIDTH / 2 / tan(FOV * DEG_TO_RAD / 2);
	//MINIMAP struct init
	game->data->minimap_data.width = game->data->map_data.cols * game->cell_size;
	printf ("in parsing: game->data->minimap_data.width %d\n", game->data->minimap_data.width);
	game->data->minimap_data.height = game->data->map_data.rows * game->cell_size;
	game->data->minimap_data.x_start = 0;
	game->data->minimap_data.x_end = game->data->minimap_data.x_start + game->data->minimap_data.width;
	game->data->minimap_data.y_start = 0;
	game->data->minimap_data.y_end = game->data->minimap_data.y_start + game->data->minimap_data.height;
	load_textures(game);
}
