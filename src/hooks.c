#include "../inc/game.h"

bool	is_colliding(t_game *game, t_pos new, t_intersection_flag flag)
{
	t_pos	new_tl;
	t_pos	new_tr;
	t_pos	new_bl;
	t_pos	new_br;

	new_tl = new;
	new_tr.x = new.x + PLAYER_SIZE;
	new_tr.y = new.y;
	new_bl.x = new.x;
	new_bl.y = new.y + PLAYER_SIZE;
	new_br.x = new.x + PLAYER_SIZE;
	new_br.y = new.y + PLAYER_SIZE;
	if (is_wall_hit (game, new_tl, flag)
		|| is_wall_hit (game, new_tr, flag)
		|| is_wall_hit (game, new_bl, flag)
		|| is_wall_hit (game, new_br, flag))
		return (true);
	else
		return (false);
}

void	check_collision(t_game *game, t_pos old_pos, t_pos new_pos)
{
	t_pos	temp_pos1;
	t_pos	temp_pos2;

	if (is_colliding(game, new_pos, INTERSECT_NONE))
	{
		temp_pos1.x = new_pos.x;
		temp_pos1.y = old_pos.y;
		temp_pos2.x = old_pos.x;
		temp_pos2.y = new_pos.y;
		if (is_wall_hit(game, temp_pos1, INTERSECT_NONE) && is_wall_hit(game, temp_pos2, INTERSECT_NONE))
			return ;
		if (!is_colliding(game, temp_pos1, INTERSECT_NONE))
		{
			game->player.pos.x = temp_pos1.x;
			game->camera_pos.x = game->player.pos.x + PLAYER_SIZE / 2 - 1;
			return ;
		}
		if (!is_colliding(game, temp_pos2, INTERSECT_NONE))
		{
			game->player.pos.y = temp_pos2.y;
			game->camera_pos.y = game->player.pos.y + PLAYER_SIZE / 2 - 1;
			return ;
		}
	}
	else
	{
		game->player.pos = new_pos;
		game->camera_pos.x = game->player.pos.x + PLAYER_SIZE / 2 - 1;
		game->camera_pos.y = game->player.pos.y + PLAYER_SIZE / 2 - 1;
	}
}

static void	check_keys_for_movement(t_game *game, mlx_key_data_t keydata)
{
	t_pos	new;
	double	new_angle;
	double	angle_size;

	new.x = game->player.pos.x;
	new.y = game->player.pos.y;
	new_angle = game->player.angle;
	angle_size = M_PI / 100;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x += (cos(game->player.angle) * DISTANCE_PER_TURN);
		new.y -= (sin(game->player.angle) * DISTANCE_PER_TURN);
	}
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x -= (cos(game->player.angle) * DISTANCE_PER_TURN);
		new.y += (sin(game->player.angle) * DISTANCE_PER_TURN);
	}
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x -= (sin(game->player.angle) * DISTANCE_PER_TURN);
		new.y -= (cos(game->player.angle) * DISTANCE_PER_TURN);
	}
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x += (sin(game->player.angle) * DISTANCE_PER_TURN);
		new.y += (cos(game->player.angle) * DISTANCE_PER_TURN);
	}
	if (new.x != game->player.pos.x || new.y != game->player.pos.y)
	{
		if (new.x < 0)
			new.x = 0;
		if (new.y < 0)
			new.y = 0;
		if (new.x > game->data->minimap_data.width)
			new.x = game->data->minimap_data.width;
		if (new.y > game->data->minimap_data.height)
			new.y = game->data->minimap_data.height;
		check_collision(game, game->player.pos, new);
	}
	if (game->is_mouse_active == false && (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
		new_angle -= angle_size;
	if (game->is_mouse_active == false && (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
		new_angle += angle_size;
	normalize_angle_to_2pi(&new_angle);
	if (new_angle != game->player.angle)
	{
		determine_quad(new_angle, &game->player.angle_quad);
		game->player.angle = new_angle;
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		printf("Player pressed ESC. Closing the game...\n");
		mlx_close_window(game->mlx);
		clean_nicely(game, NULL);
	}
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		printf("Player pressed M. toggling mmap...\n");
		game->is_mmap ^= 1;
		if (game->is_mmap == false)
		{
			game->mini->enabled = false;
			game->stats->enabled = false;
		}
		else
		{
			draw_mmap(game);
			game->mini->enabled = true;
		}
	}
	check_keys_for_movement(game, keydata);
}
