#include "../inc/game.h"

void init_map(t_game *game)
{
	int	index;
	int	row;
	int	col;

	game->mapdata = malloc(game->data->map_data.rows * game->data->map_data.cols * sizeof(char) + 1);
	if (!game->mapdata)
		clean_nicely(game, "Out of memory");
	index = 0;
	row = 0;
	while (row < game->data->map_data.rows)
	{
		col = 0;
		while (col < game->data->map_data.cols)
		{
			if (game->data->map_data.map[row][col] != '\0' && game->data->map_data.map[row][col] != '\n')
				game->mapdata[index++] = game->data->map_data.map[row][col];
			col++;
		}
		row++;
	}
	game->mapdata[index] = '\0';
	printf("%s\n", game->mapdata);
}

void	load_pngs(t_game *game)
{
	game->east = mlx_load_png("textures/Tile/Tile_11-128x128.png");  //add err check
	game->north = mlx_load_png("textures/Tile/Tile_16-128x128.png");
	game->west = mlx_load_png("textures/Wood/Wood_17-128x128.png");
	game->south = mlx_load_png("textures/Bricks/Bricks_05-128x128.png");
}

void init_game_struct(t_game *game)
{
	game->is_mmap = true;
	game->is_mouse_active = false;
	game->ray->is_vertical_first = -1;
	game->ray->wall_met= false;
	game->scene = NULL;
	game->stats = NULL;
	game->player.p_pos.x = round(X_START + (game->data->player.p_pos.x + .5) * game->cell_size - CONST/2);
	game->player.p_pos.y = round(Y_START + (game->data->player.p_pos.y + .5) * game->cell_size - CONST/2);
	printf ("player  is %f %f\n", game->player.p_pos.x, game->player.p_pos.y);
	game->player.angle = game->data->player.angle;
	printf ("in init game struct: game->player.angle is %f\n", game->player.angle);

	determine_quad(game->player.angle, &game->player.angle_quad);
	

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
	init_map(game);
	load_pngs(game);
}
