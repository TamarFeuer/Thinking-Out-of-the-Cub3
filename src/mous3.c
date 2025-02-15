#include "../inc/game.h"


// /**
//  * Callback function used to handle raw mouse movement.
//  * 
//  * @param[in] xpos The mouse x position.
//  * @param[in] ypos The mouse y position.
//  * @param[in] param Additional parameter to pass on to the function.
//  */
// typedef void (*mlx_cursorfunc)(double xpos, double ypos, void* param);

// /**
//  * Checks whether a mouse button is pressed or not.
//  * 
//  * @param[in] mlx The MLX instance handle. 
//  * @param[in] key A specific mouse key. e.g MLX_MOUSE_BUTTON_0
//  * @returns True or false if the mouse key is down or not.
//  */
// bool mlx_is_mouse_down(mlx_t* mlx, mouse_key_t key);


// /**
//  * Returns the current, relative, mouse cursor position on the window, starting
//  * from the top left corner.
//  * 
//  * Negative values or values greater than window width or height 
//  * indicate that it is outside the window.
//  * 
//  * @param[in] mlx The MLX instance handle. 
//  * @param[out] x The position.
//  * @param[out] y The position.
//  */
// void mlx_get_mouse_pos(mlx_t* mlx, int32_t* x, int32_t* y);

// /**
//  * Sets the mouse position.
//  * 
//  * @param[in] mlx The MLX instance handle. 
//  * @param[in] pos The position.
//  */
// void mlx_set_mouse_pos(mlx_t* mlx, int32_t x, int32_t y);

// /**
//  * This function sets the cursor callback, which is called when the
//  * mouse position changes. Position is relative to the window.
//  * 
//  * @param[in] mlx The MLX instance handle.
//  * @param[in] func The cursor callback function.
//  * @param[in] param An additional optional parameter.
//  */
// void mlx_cursor_hook(mlx_t* mlx, mlx_cursorfunc func, void* param);


void mouse_hook(double xpos, double ypos, void* param)
{
	t_game *game;
	static float last_x = -1;
	static float last_y = -1;
	double new_angle;
	double angle_size = 2 * M_PI / 100;

	game = (t_game *)param;
	new_angle = game->player.angle;
	if (last_x != -1 && last_y != -1 && last_x != xpos)
	{
		//mlx_get_mouse_pos(game->mlx, x, y);
		// mlx_set_mouse_pos(game->mlx, x, y);
		printf ("x moved is %f and y moved %f\n", xpos - last_x, ypos - last_y);
		if ((xpos - last_x) > 0)
			new_angle += angle_size/10;   //radians per frame
		else
		new_angle -= angle_size/10; 
		normalize_angle_to_2pi(&new_angle);
		if (new_angle != game->player.angle)
		{
			determine_quad(new_angle, &game->player.angle_quad);
			game->player.angle = new_angle;
			mlx_delete_image(game->mlx, game->stats);
			if (game->is_mmap)
				print_stats(game);
		}
	}
	last_x = xpos;
	last_y = ypos;
}