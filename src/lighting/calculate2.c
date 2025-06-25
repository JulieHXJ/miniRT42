/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:26:36 by dchrysov          #+#    #+#             */
/*   Updated: 2025/06/25 18:32:57 by dchrysov         ###   ########.fr       */
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

bool	is_shadowed_pixel(t_scene scene, t_hit hit)
{
	t_ray	light_ray;
	double	limit;
	t_hit	temp_hit;

	limit = hit.t;
	light_ray.origin = scene.light->position;
	light_ray.direction = vec_normal(vec_sub(hit.point, light_ray.origin));
	while (scene.obj)
	{
		if (scene.obj != hit.object && hit_object(scene.obj, light_ray, &temp_hit) && temp_hit.t < limit)
			return (true);
		scene.obj = scene.obj->next;
	}
	return (false);
}
