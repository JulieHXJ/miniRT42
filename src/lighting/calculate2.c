/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:26:36 by dchrysov          #+#    #+#             */
/*   Updated: 2025/06/27 19:49:23 by dchrysov         ###   ########.fr       */
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

/**
 * @brief Checks if the hit point is blocked by another object's shadow.
 * 
 * @param shadow The shadow ray casted from the hit point to the light source.
 * @param limit The distance between the hit point and the light source.
 * 
 * @note Normally the shadow is launched from the hit point towards
 * the direction of the light source. This initial point is offsetted
 * by a small factor (1e-4) to avoid self shadowing, due to random rounding
 * of float numbers.
 */
bool	is_in_shadow(t_scene scene, t_hit hit)
{
	t_ray		shadow_ray;
	t_light		light;
	t_hit		temp_hit;
	float		limit;

	light = *scene.light;
	shadow_ray.origin = light.position;
	shadow_ray.direction = vec_normal(vec_sub(vec_add(hit.point, vec_scale(hit.normal, 0.01)), shadow_ray.origin));
	limit = vec_length(ray_point_at(shadow_ray, vec_length(vec_sub(light.position, shadow_ray.origin))));
	while (scene.obj)
	{
		if (scene.obj != hit.object && hit_object(scene.obj, shadow_ray, &temp_hit)
			&& temp_hit.t <= limit)
			return (true);
		scene.obj = scene.obj->next;
	}
	return (false);
}
