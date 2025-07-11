/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:22:35 by junjun            #+#    #+#             */
/*   Updated: 2025/07/11 15:17:40 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_color	color_scale(t_color c, float factor)
{
	t_color	result;

	result.r = c.r * factor;
	result.g = c.g * factor;
	result.b = c.b * factor;
	return (result);
}

/**
 * @brief adding two light colors together(ambient + diffuse)
 */
t_color	color_add(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r + c2.r;
	result.g = c1.g + c2.g;
	result.b = c1.b + c2.b;
	return (result);
}

t_color	color_mult(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r * c2.r / 255.0f;
	result.g = c1.g * c2.g / 255.0f;
	result.b = c1.b * c2.b / 255.0f;
	return (result);
}

/**
 * @brief Converts a t_color to a 32-bit RGBA color for MLX42.
 */
uint32_t	convert_color(t_color color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | 0xFF);
}

/**
 * @brief Restricts the value between the range [0, 255].
 */
t_color	clamp_color(t_color c)
{
	t_color	result;

	result.r = fminf(fmaxf(c.r, 0.0f), 255.0f);
	result.g = fminf(fmaxf(c.g, 0.0f), 255.0f);
	result.b = fminf(fmaxf(c.b, 0.0f), 255.0f);
	return (result);
}
