#include "../inc/game.h"

void init_map(t_game *game)
{
	int	j;
	game->mapdata = malloc(game->data->map_data.rows * game->data->map_data.cols * sizeof(char) + 1);
	if (!game->mapdata)
	{
		exit(EXIT_FAILURE);
	}
 
	// char initial_map[game->data->map_data.rows][game->data->map_data.cols] = 
	// {
	// 	//10 x 8
	// 	{"1111111111"},
	// 	{"1000110101"},
	// 	{"1000110101"},
	// 	{"1001110101"},
	// 	{"1000111101"},
	// 	{"1000110101"},
	// 	{"1000000001"},
	// 	{"1111111111"}
		
	// 	//10 x 8
	// 	// {"1111111111"},
	// 	// {"1000000001"},
	// 	// {"1000000001"},
	// 	// {"1000100001"},
	// 	// {"1000000001"},
	// 	// {"1000000001"},
	// 	// {"1000000001"},
	// 	// {"1111111111"}
	
	// //6 x 15
	// // {"111111111111111"},
	// // {"100000100010001"},
	// // {"100000100010001"},
	// // {"100000100010001"},
	// // {"100000111100001"},
	// // {"111111111111111"}
	// };
	
	int i = 0;
	while (i < game->data->map_data.rows)
	{
		j = 0;
		while (j < game->data->map_data.cols)
		{
			game->mapdata[i * game->data->map_data.cols + j] = game->data->map_data.map[i][j];
			j++;
		}
		i++;
	}
	game->mapdata[i * game->data->map_data.cols + j] = '\0';
}

void	load_pngs(t_game *game)
{
	
	game->east = mlx_load_png("textures/Dirt_Road_64x64.png");  //add err check
	game->north = mlx_load_png("textures/Brick_Wall_64x64.png");
	game->west = mlx_load_png("textures/Brick_Wall_Cracked_64x64.png");
	game->south = mlx_load_png("textures/stone_64x64.png");
}

void init_game_struct(t_game *game, t_data *data)
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
