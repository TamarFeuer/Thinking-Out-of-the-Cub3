#include "../inc/game.h"

uint32_t	color_abgr_to_rgba(uint32_t c)
{
	uint32_t	c1;

	c1 = 0;
	c1 |= (c & 0x000000FF) << 24;
	c1 |= (c & 0x0000FF00) << 8;
	c1 |= (c & 0x00FF0000) >> 8;
	c1 |= (c & 0xFF000000) >> 24;
	return (c1);
}

int	atoi_limit_255(int *dst, char *str)
{
	*dst = 0;
	while (*str && *dst <= 255)
		*dst = 10 * *dst + *str++ - '0';
	return (*dst > 255);
}

// int distance_to_color(int distance)
// {
// 	int max_color_value = 255;
// 	// Normalize the distance (between 0 and 1)
// 	float normalized_distance = (float)distance / MAX_RAY_DISTANCE;
// 	if (normalized_distance > 1.0f) normalized_distance = 1.0f;

// 	int red = (int)((1.0f - normalized_distance) * max_color_value );
// 	int blue = (int)((1.0f -normalized_distance) * max_color_value );
// 	int alpha = (1.0f - normalized_distance) * 255;

// 	// ARGB color (Alpha << 24 | Red << 16 | Green << 8 | Blue)
// 	return (alpha << 24) | (red << 16) | (255 << 8) | blue;
// }

//Reverse the color for MLX42
int	distance_to_color(int distance, int flag)
{
	int		red;
	int		blue;
	int		green;
	int		alpha;
	float	normalized_distance;

	normalized_distance = (float)distance / MAX_RAY_DISTANCE;
	if (normalized_distance > 1.0f)
		normalized_distance = 1.0f;
	red = 0xFF;
	blue = 0x00;
	if (flag == 0)
		green = 00;
	else
		green = 0xFF;
	alpha = (1.0f - normalized_distance) * 255;
	return ((blue << 24) | (green << 16) | (red << 8) | alpha);
}
