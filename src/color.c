/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfeuer <tfeuer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:15:33 by tfeuer            #+#    #+#             */
/*   Updated: 2025/04/17 18:15:34 by tfeuer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/**
 * @brief Calculates a color with distance-based fog/shading based on ray type.
 * @details Determines a base color based on `ray_sort` (Red for player,
 *          Magenta for casted rays). Calculates a normalized distance and uses
 *          it to compute an alpha value (0-255) for fog/shading. The final
 *          color is formatted as an integer suitable for MLX42 (BGRA).
 *
 * @param distance The raw distance value (e.g., from raycasting).
 * @param ray_sort The type of ray (`t_ray_sort`: PLAYER_DIRECTION or
 *                 CASTED_RAYS) determining the base color.
 *
 * @return int An integer representing the final color, formatted for MLX42.
 *         MLX42 expects colors in a 32-bit integer. The bytes typically
 *         represent Blue, Green, Red, and Alpha components (BGRA order).
 *         This function constructs this integer as follows:
 *         Each 8-bit color component is shifted to its correct byte position
 *         using the left-shift operator (`<<`). They are then combined using
 *         the bitwise OR operator (`|`).
 *         - `(Blue << 24)` : Blue component in bits 31-24.
 *         - `(Green << 16)`: Green component in bits 23-16.
 *         - `(Red << 8)`  : Red component in bits 15-8.
 *         - `Alpha`       : Alpha component in bits 7-0.
 *         The final structure is: `(B << 24 | G << 16 | R << 8 | A)`.
 *         The Alpha component creates a fog effect: 0 means fully transparent
 *         (max fog, far distance), while 255 means fully opaque (no fog,
 *         near distance).
 */
int	distance_to_color(int distance, t_ray_sort ray_sort)
{
	int		blue;
	int		green;
	int		red;
	int		alpha;
	float	normalized_distance;

	normalized_distance = (float)distance / MAX_RAY_DISTANCE;
	if (normalized_distance > 1.0f)
		normalized_distance = 1.0f;
	red = 0xFF;
	blue = 0x00;
	if (ray_sort == PLAYER_DIRECTION)
		green = 0xFF;
	else
		green = 00;
	alpha = (1.0f - normalized_distance) * 255;
	return ((blue << 24) | (green << 16) | (red << 8) | alpha);
}
