/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:26:36 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/02 10:12:24 by dchrysov         ###   ########.fr       */
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
 * @param temp_hit If there is an object in between, it saves its hit point.
 * @param vec The vec from the light source to the hit point.
 * 
 * @note Normally the shadow is launched from the hit point towards
 * the direction of the light source. This initial point is offsetted
 * by a small factor (1e-4) to avoid self shadowing, due to random rounding
 * of float numbers.
 */
bool	is_in_shadow(t_scene scene, t_hit hit)
{
	t_ray	ray;
	t_hit	temp_hit;
	t_vec3	vec;

	ray.origin = scene.light->position;
	vec = vec_sub(vec_add(hit.point, vec_scale(hit.normal, 5e-4)), ray.origin);
	ray.direction = vec_normal(vec);
	while (scene.obj)
	{
		if (scene.obj != hit.object && hit_object(scene.obj, ray, &temp_hit)
			&& temp_hit.t > 0 && temp_hit.t < vec_length(vec))
			return (true);
		scene.obj = scene.obj->next;
	}
	return (false);
}

/**
 * @brief Determines if the hit point should be colored or not.
 */
bool	is_lighted_pixel(t_scene scene, t_hit hit)
{
	float	angle;
	t_vec3	light_vec;

	light_vec = vec_sub(scene.light->position, hit.point);
	angle = vec_dot(light_vec, hit.normal) / (vec_length(light_vec));
	if (angle >= 0 && angle <= 1)
		return (true);
	return (false);
}
