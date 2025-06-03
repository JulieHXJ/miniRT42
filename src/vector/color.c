/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:22:35 by junjun            #+#    #+#             */
/*   Updated: 2025/06/03 17:08:31 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_color	color_scale(t_color c, double factor)
{
	t_color	result;

	result.r = (int)(c.r * factor);
	result.g = (int)(c.g * factor);
	result.b = (int)(c.b * factor);

	// result.r = fmin(c.r * factor, 255);
    // result.g = fmin(c.g * factor, 255);
    // result.b = fmin(c.b * factor, 255);
	return (result);
}

// change to c style
t_color	color_add(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r + c2.r > 255 ? 255 : c1.r + c2.r;
	result.g = c1.g + c2.g > 255 ? 255 : c1.g + c2.g;
	result.b = c1.b + c2.b > 255 ? 255 : c1.b + c2.b;
	return (result);
}

/**
 * @brief Converts a t_color to a 32-bit RGBA color for MLX42.
 */
static uint32_t	convert_color(t_color color)
{
	return ((color.r << 24) | (color.g << 16) | (color.b << 8) | 0xFF);
}
