/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:22:35 by junjun            #+#    #+#             */
/*   Updated: 2025/06/11 19:47:44 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

// limited to 255
t_color	color_scale(t_color c, double factor)
{
	t_color	result;

	result.r = (int)fmin(c.r * factor, 255.0);
    result.g = (int)fmin(c.g * factor, 255.0);
    result.b = (int)fmin(c.b * factor, 255.0);
	return (result);
}

/**
 * @brief adding two light colors together(ambient + diffuse)
 */
t_color	color_add(t_color c1, t_color c2)
{
	t_color	result;

	result.r = (int)fmin(c1.r + c2.r, 255.0);
    result.g = (int)fmin(c1.g + c2.g, 255.0);
    result.b = (int)fmin(c1.b + c2.b, 255.0);
	return (result);
}

/**
 * @brief Blends two colors based on a ratio (surface material blending)
 */
t_color color_blend(t_color c1, t_color c2, double ratio)
{
	t_color	result;

	if (ratio < 0.0 || ratio > 1.0)
		return (c1); // Invalid ratio, return first color
	result.r = (int)fmin(c1.r * (1 - ratio) + c2.r * ratio, 255.0);
	result.g = (int)fmin(c1.g * (1 - ratio) + c2.g * ratio, 255.0);
	result.b = (int)fmin(c1.b * (1 - ratio) + c2.b * ratio, 255.0);
	return (result);
}


// /**
//  * @brief Converts a t_color to a 32-bit RGBA color for MLX42.
//  */
// static uint32_t	convert_color(t_color color)
// {
// 	return ((color.r << 24) | (color.g << 16) | (color.b << 8) | 0xFF);
// }
