#ifndef GAME_H
# define GAME_H

#include "MLX42.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../libs/libft/libft.h"


#define M_PI 3.14159265358979323846
#define DEG_TO_RAD (M_PI / 180.0)
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define MOUSE_SENSITIVITY 0.1f

//map
#define ROWS 8 //---> !
#define COLS 10 //---> !
#define EMPTY '0'
#define WALL '1'
#define SPACE ' '

//mini map
#define CONST 4
#define PIXELS_PER_BLOCK 8

#define MMAP_WIDTH COLS * PIXELS_PER_BLOCK * CONST
#define MMAP_HEIGHT ROWS * PIXELS_PER_BLOCK * CONST
#define X_START 0
#define Y_START 0
#define X_END (X_START + MMAP_WIDTH)
#define Y_END (Y_START + MMAP_HEIGHT)
#define MMAP_MAX_HEIGHT SCREEN_HEIGHT/4
#define MMAP_MAX_WIDTH SCREEN_WIDTH/4

//player
#define PLAYER_SIZE 2
#define PLAYER_DIRECTION_SIZE 50

//rays
#define FOV 60.0 // Field of View in degrees
#define NUMBER_OF_RAYS 640
#define MAX_RAY_LENGTH 400
#define MAX_RAY_DISTANCE 300
#define DISTANCE_PER_TURN 0.5 * CONST
#define OUT_OF_BOUNDS 1000000000

//scene
#define SCENE_BLOCK_SIZE 64
#define SCENE_WIDTH  1920
#define SCENE_HEIGHT 1080
#define BASE_FRUSTUM_DISTANCE 300.0f
#define MIN_RAY_DISTANCE 5.0f
#define FLOOR_COLOR 0xFF8000FF  //---> !

typedef enum e_direction 
{
	EAST,
	NORTH,
	WEST,
	SOUTH,
} t_direction;

typedef enum e_pos_id
{
	INVAL_ID = -1,
	NORTH_ID,
	SOUTH_ID,
	EAST_ID,
	WEST_ID,
	FLOOR_ID,
	CEILING_ID
} t_pos_id;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_player
{
	t_pos		p_pos;  // ---> !
	double		angle;  // in radians ---> !
	int			angle_quad;
}	t_player;

typedef struct s_camera
{
	t_pos		pos;
	float		angle;
	float		frustum_plane_distance;
}	t_camera;


typedef struct s_mmap
{
	int block_size;
	int height;
	int width;
} t_mmap;

typedef struct s_ray
{
	t_pos		end;
	t_pos		intersect;
	int			number_of_rays;
	int			ray_num;
	float		current_angle;
	int			angle_quad;
	bool		wall_met;
	int			is_vertical_first;
	float		distance;
	float		corrected_distance;
	t_pos		v_hit;
	t_pos		h_hit;
	t_pos		ray_start[SCREEN_WIDTH];
	t_pos		ray_end[SCREEN_WIDTH];
}	t_ray;

typedef struct s_mapdata
{
	char		*path;
	int			total_lines;
	char		**file_data;
	char		**map;
	int			rows;
	int			cols;
	u_int32_t	floor_color;
	u_int32_t	ceiling_color;
}	t_mapdata;

typedef struct s_minimap
{
	int width;
	int	height;
	int	x_start;
	int	x_end;
	int	y_start;
	int	y_end;
	int max_height;
	int	max_width;
}	t_minimap;

typedef struct s_data
{
	char			*scene_file;
	t_mapdata		map_data;
	char			**identifiers;
	t_player		player;
	t_minimap		minimap_data;
}	t_data;

typedef struct s_game
{
	t_data			*data;
	bool			is_debug;
	bool			is_mmap;
	bool			is_mouse_active;
	t_mmap			mmap;
	mlx_t			*mlx;
	char			*mapdata;
	mlx_image_t 	*scene;
	t_ray			*ray;
	mlx_image_t 	*stats;
	t_player		player;
	t_camera		camera;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
}	t_game;



void	draw_grid(t_game *game, int rows, int cols);
void	draw_player(t_game *game);
void	cast_rays(t_game *game);
void	key_hook(mlx_key_data_t keydata, void *param);
void	print_stats(t_game *game);
void	clean_nicely(t_game *game, char *error_message);
int		distance_to_color(int distance);
// void	DDA_ray(t_game *game, t_pos start, t_pos end);
void	DDA_ray(t_game *game, t_pos start, t_pos end, int color);
const char *get_direction(t_game *game);
void	draw_bresenham_ray(t_game *game, t_pos start, t_pos end);
double	get_distance(t_pos start, t_pos end);
int 	get_block_index(t_pos *grid_pos);
int 	get_block_index2(t_game *game, t_pos *grid_pos, int flag);
void	init_map(t_game *game);
void	reach_nearest_wall_by_plotting(t_game *game, float angle);
void 	reach_nearest_wall_by_intersections(t_game *game, float angle);
void 	draw_player_direction(t_game *game, t_pos start, double angle);
void 	draw_vertical_slice(t_game *game);
void	normalize_angle_to_2pi(double *angle);
void	safe_put_pixel(t_game *game, int x, int y, u_int32_t color);
int		convert_to_mlx42_endian(int c);
void 	determine_quad(double angle, int *quad);
void	absolute(int *d, int *i);
void	init_game_struct(t_game *game);
void	draw_all(void *param);
float	horiz_intersect(t_game *game, float angle);
float	vertical_intersect(t_game *game, float angle);
bool	is_out_of_bounds(t_game *game, t_pos position);
int		is_wall_hit(t_game *game, t_pos intersect, int flag);
int		draw_static_components(t_game *game);

// LIBFT
void	ft_free_2d(void ***arr);
int		ft_atoi(const char *nptr);
bool	ft_is_pos_identifier(char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(char const *str);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);
char	*ft_ftoa(float n, int precision);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
float	limit_decimal_places(float number, int decimal_places);
int		ft_isdigit(char c);
char	**ft_split(char const *s, char c);

// PARSING
char	*get_next_line(int fd);
void	init_data_struct(t_data **data);
void	parse_file(t_game *game, t_data *data, char *file_path);
int		count_lines(char *file_path);
void	copy_line_by_line(t_mapdata *mapinfo, int fd);
void 	parse_identifiers(t_data *data, int *i, int *j);
void 	parse_map(t_game *game, t_data *data, int *i, int *j);
bool	check_map_validity(t_data *data);
bool	is_surrounded_by_walls(t_data *data, char **map);

//PARSING UTILS
void	skip_whitespaces(char **arr, int i, int *j);
void	skip_nl_and_whitespaces(char **arr, int *i, int *j);
void	ft_print_arr(char **arr);


void 	cursor_hook(double xpos, double ypos, void* param);
void mouse_action (mouse_key_t button, action_t action, modifier_key_t mods, void* param);
#endif
