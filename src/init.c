#include "../inc/game.h"

void init_map(t_game *game)
{
	game->mapdata = malloc(ROWS * COLS * sizeof(char));
	if (!game->mapdata)
	{
		exit(EXIT_FAILURE);
	}
 
	int initial_map[ROWS][COLS] = 
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 1, 1, 0, 1, 0, 1},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 1, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	
	int i = 0;
	while (i < ROWS)
	{
		int j = 0;
		while (j < COLS)
		{
			game->mapdata[i * COLS + j] = initial_map[i][j];
			j++;
		}
		i++;
	}
}

void	load_pngs(t_game *game)
{
	
	game->east = mlx_load_png("textures/east.png");  //add err
	game->north = mlx_load_png("textures/north.png");
	game->west = mlx_load_png("textures/west.png");
	game->south = mlx_load_png("textures/south.png");
}

void init_game_struct(t_game *game)
{
	game->is_mmap = true;
	game->ray = ft_calloc(1, sizeof(t_ray));
	if (!game->ray) //error
		return;
	game->ray->found_vertical_first = -1;
	game->ray->wall_met= false;
	game->scene = NULL;
	game->stats = NULL;
	game->player.p_pos.x = X_START + 48 + 24 - 3;
	game->player.p_pos.y = Y_START + 48 + 24 - 3;
	printf ("player  is %f %f\n", game->player.p_pos.x, game->player.p_pos.y);
	game->player.angle = 0;
	game->player.angle_quad = 1;
	game->ray->angle_quad = 1;
	game->ray->inter.x = 0;
	game->ray->inter.y = 0;
	game->camera.pos.x = game->player.p_pos.x + CONST /2;
	game->camera.pos.y = game->player.p_pos.y + CONST /2;
	game->camera.plane_distance = SCREEN_WIDTH / 2 * (tan(FOV * DEG_TO_RAD/ 2)); //?
	init_map(game);
	load_pngs(game);
	
}