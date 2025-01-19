#include "../inc/game.h"

int	convert_to_mlx42_endian(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
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

int distance_to_color(int distance)
{
    int max_color_value = 255;
    // Normalize the distance (between 0 and 1)
    float normalized_distance = (float)distance / MAX_RAY_DISTANCE;
    if (normalized_distance > 1.0f) normalized_distance = 1.0f;

    int red = (int)((1.0f - normalized_distance) * max_color_value);
    int blue = (int)((1.0f - normalized_distance) * max_color_value);
    int alpha = (1.0f - normalized_distance) * 255;

    // Reverse the color for MLX42 (Blue << 24 | Green << 16 | Red << 8 | Alpha)
    return (blue << 24) | (255 << 16) | (red << 8) | alpha;
}
