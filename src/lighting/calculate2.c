/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:26:36 by dchrysov          #+#    #+#             */
/*   Updated: 2025/06/24 15:38:13 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define TILE_SIZE 100

t_color	checkered_background(uint32_t x, uint32_t y)
{
	int	tile_x;
	int	tile_y;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	if ((tile_x + tile_y) % 2 == 0)
		return ((t_color){130, 130, 130});
	else
		return ((t_color){75, 75, 75});
}

t_color	unlighted_pixel(t_scene scene, t_hit hit)
{
	t_object	obj;
	t_amb_light	ambient;

	ambient.color = color_scale(scene.amb_light.color, scene.amb_light.ratio);
	obj.color = color_mult(hit.object->color, ambient.color);
	return (clamp_color(obj.color));
}
