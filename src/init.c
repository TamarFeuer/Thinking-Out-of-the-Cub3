#include "../inc/game.h"

void	init_parsed_data_struct(t_data **data, int argc, char **argv)
{
	*data = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!*data)
		clean_and_exit(*data, ECODE_FAILURE);
	(*data)->game = (t_game *) ft_calloc(1, sizeof(t_game));
	if (!(*data)->game)
		clean_and_exit(*data, ECODE_FAILURE);
	(*data)->game->data = *data;
	if (argc == 2 && ft_strncmp(argv[1], "-d", 3) == 0)
	{
		(*data)->game->data->is_debug = true;
		(*data)->game->is_mmap = true;
	}
	else
		(*data)->game->data->is_debug = false;
}

t_ecode	init_minimap_struct(t_data *data)
{
	if (!data || !data->map_data.map)
		return (ECODE_FAILURE);
	if (data->map_data.rows == 0 || data->map_data.cols == 0)
		return (ECODE_FAILURE);
	data->minimap_data.width = data->map_data.cols * PIXELS_PER_BLOCK * CONST;
	data->minimap_data.height = data->map_data.rows * PIXELS_PER_BLOCK * CONST;
	data->minimap_data.x_start = 0;
	data->minimap_data.x_end = data->minimap_data.x_start + data->minimap_data.width;
	data->minimap_data.y_start = 0;
	data->minimap_data.y_end = data->minimap_data.y_start + data->minimap_data.height;
	data->minimap_data.max_height = SCREEN_HEIGHT/4;
	data->minimap_data.max_width = SCREEN_WIDTH/4;
	return (ECODE_SUCCESS);
}

void init_map(t_game *game)
{
	int	index;
	int	row;
	int	col;

	game->mapdata = malloc(game->data->map_data.rows * game->data->map_data.cols * sizeof(char) + 1);
	if (!game->mapdata)
	{
		exit(EXIT_FAILURE);
	}
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
	game->east = mlx_load_png("textures/Dirt_Road_64x64.png");  //add err check
	game->north = mlx_load_png("textures/Brick_Wall_64x64.png");
	game->west = mlx_load_png("textures/Brick_Wall_Cracked_64x64.png");
	game->south = mlx_load_png("textures/stone_64x64.png");
}

void init_game_struct(t_data *data, t_game *game)
{
	game->data = data;
	game->is_mmap = true;
	game->ray = ft_calloc(1, sizeof(t_ray));
	if (!game->ray) //error
		return;
	game->ray->is_vertical_first = -1;
	game->ray->wall_met= false;
	game->scene = NULL;
	game->stats = NULL;
	game->player.p_pos.x = X_START + (game->data->player.p_pos.x + .5) * PIXELS_PER_BLOCK * CONST - CONST/2;
	game->player.p_pos.y = Y_START + (game->data->player.p_pos.y + .5) * PIXELS_PER_BLOCK * CONST - CONST/2;
	//printf ("player  is %f %f\n", game->player.p_pos.x, game->player.p_pos.y);
	game->player.angle = game->data->player.angle;
	// game->player.angle_quad = 1;
	game->ray->angle_quad = game->data->player.angle_quad;
	game->ray->intersect.x = 0;
	game->ray->intersect.y = 0;
	game->camera.pos.x = game->player.p_pos.x + (PLAYER_SIZE + CONST) /2;
	game->camera.pos.y = game->player.p_pos.y + (PLAYER_SIZE + CONST) /2;
	game->camera.frustum_plane_distance = SCREEN_WIDTH / 2 * (tan(FOV * DEG_TO_RAD/ 2));
	//game->camera.frustum_plane_distance = SCREEN_WIDTH / 2 / tan(FOV * DEG_TO_RAD / 2);
	init_map(game);
	load_pngs(game);
}
