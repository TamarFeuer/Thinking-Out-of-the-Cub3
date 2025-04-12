#include "../inc/game.h"

static void	clear_image(mlx_image_t *image, uint32_t npixels)
{
	uint8_t	*pixel;

	pixel = image->pixels;
	while (pixel - image->pixels < npixels)
		*pixel++ &= 0xFFFFFF00;
}

void	draw_mmap(void *param)
{
	t_game *const	game = (t_game *)param;
	int				i;

	cast_rays(game);
	if (game->is_mmap)
	{
		clear_image(game->mini,
			(uint32_t)((game->mini->width) * (game->mini->height) * CONST));
		i = 0;
		if (game->is_debug == false)
			game->ray->number_of_rays = SCREEN_WIDTH;
		else
			game->ray->number_of_rays = 1;
		while (i < game->ray->number_of_rays)
		{
			draw_bresenham_ray(game, game->camera_pos, game->ray->ray_end[i]);
			i++;
		}
		draw_player(game);
		draw_grid(game, game->data->map_data.rows, game->data->map_data.cols);
		draw_player_direction(game, (t_pos){game->camera_pos.x, game->camera_pos.y}, game->player.angle);
		mlx_delete_image(game->mlx, game->stats);
		print_stats(game);
	}
}

static void	allocate_structures(t_game **pgame)
{
	*pgame = malloc(sizeof(t_game));
	if (*pgame)
	{
		(*pgame)->data = malloc(sizeof(t_data));
		if ((*pgame)->data)
		{
			(*pgame)->data->tokens = NULL;
			(*pgame)->data->map = NULL;
		}
		(*pgame)->ray = ft_calloc(1, sizeof(t_ray));
		(*pgame)->mlx = NULL;
		(*pgame)->stats = NULL;
		(*pgame)->mini = NULL;
		(*pgame)->scene = NULL;
		(*pgame)->textures[E] = NULL;
		(*pgame)->textures[N] = NULL;
		(*pgame)->textures[W] = NULL;
		(*pgame)->textures[S] = NULL;
		if ((*pgame)->data && (*pgame)->ray)
			return ;
	}
	clean_nicely(*pgame, "Out of memory");
}

static void	check_arguments(t_game *game, int argc, char *argv[])
{
	char	*extension;
	char	log[LOG];

	if (argc >= 2)
		game->is_debug = !ft_strncmp(*++argv, "-d", 3);
	if (game->is_debug)
	{
		argc--;
		argv++;
	}
	if (argc < 2)
		clean_nicely(game, "Missing scene description file");
	if (argc > 2)
		clean_nicely(game, "Too many arguments");
	extension = ft_strrchr(*argv, '.');
	if (!extension)
		clean_nicely(game, "Expected `.cub\' extension");
	if (ft_strncmp(extension, ".cub", 5))
	{
		ft_snprintf(log, LOG, "Unknown format `.%s\'. Expected `.cub\' "
			"extension", extension);
		clean_nicely(game, log);
	}
	game->data->cub_file = *argv;
}

int	main(int argc, char *argv[])
{
	t_game	*game;
	int		temp_width;
	int		temp_height;

	allocate_structures(&game);
	check_arguments(game, argc, argv);
	lexer(game);
	parser(game);
	flood_fill_map(game, ft_strdup(game->data->map));
	temp_width = (SCREEN_WIDTH / 2) / game->data->map_data.cols;
	temp_height = (SCREEN_HEIGHT / 2) / game->data->map_data.rows;
	if (temp_width > temp_height)
		game->cell_size = temp_height;
	else
		game->cell_size = temp_width;
	if (game->cell_size < 2 * PLAYER_SIZE)
		clean_nicely(game, "The map is too large for the screen resolution");
	init_game_struct(game);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Thinking Out of the Cub3", true);
	if (!game->mlx)
		clean_nicely(game, "Failed to initialize MLX42");
	game->scene = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->scene || (mlx_image_to_window(game->mlx, game->scene, 0, 0) < 0))
		clean_nicely(game, "Failed to create/copy an MLX42 image");
	game->mini = mlx_new_image(game->mlx, game->data->map_data.cols * game->cell_size + 1, game->data->map_data.rows * game->cell_size + 1);
	if (!game->mini || (mlx_image_to_window(game->mlx, game->mini, 0, 0) < 0))
		clean_nicely(game, "Failed to create/copy an MLX42 image");
	mlx_loop_hook(game->mlx, draw_mmap, game);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_cursor_hook(game->mlx, cursor_hook, game);
	mlx_mouse_hook(game->mlx, mouse_action, game);
	mlx_loop(game->mlx);
	clean_nicely(game, NULL);
}
