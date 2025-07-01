/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/07/01 14:59:54 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	in_range_int(int value, int min, int max)
{
	return (value >= min && value <= max);
}

bool	in_range_float(float value, float min, float max)
{
	return (value >= min && value <= max);
}

/**
 * @brief Check color range (0-255)
 */
bool	valid_color(t_color color)
{
	return (in_range_int(color.r, 0, 255) && in_range_int(color.g, 0, 255)
		&& in_range_int(color.b, 0, 255));
}

/**
 * @brief Check ratio range (0.0-1.0)
 */
bool	valid_ratio(float ratio)
{
	return (in_range_float(ratio, 0.0, 1.0));
}

/**
 * @brief Check normal vector range (-1.0 - 1.0)
 */
bool	valid_normal(t_vec3 normal)
{
	if (normal.x == 0 && normal.y == 0 && normal.z == 0)
		return (print_error("Normal vector cannot be zero", NULL), false);
	return (in_range_float(normal.x, -1.0, 1.0) && in_range_float(normal.y,
			-1.0, 1.0) && in_range_float(normal.z, -1.0, 1.0));
}
