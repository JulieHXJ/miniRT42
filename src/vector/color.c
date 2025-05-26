/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:22:35 by junjun            #+#    #+#             */
/*   Updated: 2025/05/26 15:24:26 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

// t_color	new_color(int r, int g, int b)
// {
// 	t_color	c;

// 	c.r = r;
// 	c.g = g;
// 	c.b = b;
// 	return (c);
// }

/**
 * @brief Multiples a color's coordinates by a scale factor.
 * 
 * @note What happens if the result is > 255?? Should it be handled explicitly?
 */
t_color	color_scale(t_color c, double factor)
{
	t_color	result;

	result.r = (int)(c.r * factor);
	result.g = (int)(c.g * factor);
	result.b = (int)(c.b * factor);
	return (result);
}

/**
 * @brief Create a new color from the addition of two others.
 * 
 * @returns The new color.
 * 
 * @note If the sum of any color coordinate is > 255, then it returns 255.
 */
t_color	color_add(t_color c1, t_color c2)
{
	t_color	result;

	if (c1.r + c2.r > 255)
		result.r = 255;
	else
		result.r = c1.r + c2.r;
	if (c1.g + c2.g > 255)
		result.g = 255;
	else
		result.g = c1.g + c2.g;
	if (c1.b + c2.b > 255)
		result.b = 255;
	else
		result.b = c1.b + c2.b;
	return (result);
}


// Helper function to convert t_color to mlx color format
int	convert_color(t_color color)
{
	return (((color.r & 0xff) << 16) + ((color.g & 0xff) << 8)
		+ (color.b & 0xff));
}
