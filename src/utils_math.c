/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfeuer <tfeuer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:14:05 by tfeuer            #+#    #+#             */
/*   Updated: 2025/04/20 15:47:00 by tfeuer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	determine_quad(double angle, int *quad)
{
	double	sin_a;
	double	cos_a;

	sin_a = sin(angle);
	cos_a = cos(angle);
	if (cos_a > 0 && sin_a > 0)
		*quad = 1;
	else if (cos_a < 0 && sin_a > 0)
		*quad = 2;
	else if (cos_a < 0 && sin_a < 0)
		*quad = 3;
	else if (cos_a > 0 && sin_a < 0)
		*quad = 4;
	else if (cos_a == 1 && sin_a == 0)
		*quad = 1;
	else if (cos_a == 0 && sin_a == 1)
		*quad = 2;
	else if (cos_a == -1 && sin_a == 0)
		*quad = 3;
	else if (cos_a == 0 && sin_a == -1)
		*quad = 4;
}

void	normalize_angle_to_2pi(double *angle)
{
	*angle = fmod(*angle, 2.0 * PI);
	if (*angle < 0.0)
		*angle += (2.0 * PI);
}

double	get_distance(t_vec2 start, t_vec2 end)
{
	double	dx;
	double	dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	return (sqrt(dx * dx + dy * dy));
}
