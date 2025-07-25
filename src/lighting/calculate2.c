/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:26:36 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/04 14:41:12 by xhuang           ###   ########.fr       */
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
bool	is_in_shadow(t_scene scene, t_hit hit, t_light *light)
{
	t_vec3	to_light;
	float	dist_to_light;
	t_ray	shadow_ray;
	t_hit	shadow_hit;

	to_light = vec_sub(light->position, hit.point);
	dist_to_light = vec_length(to_light);
	shadow_ray.origin = vec_add(hit.point, vec_scale(hit.normal, 1e-4));
	shadow_ray.direction = vec_normal(to_light);
	shadow_hit.t = dist_to_light;
	if (if_hit(&scene, shadow_ray, &shadow_hit) && shadow_hit.t < dist_to_light)
		return (true);
	return (false);
}

/**
 * @brief Determines if the hit point should be colored or not.
 */
bool	is_lighted_pixel(t_hit hit, t_light light)
{
	float	angle;
	t_vec3	light_vec;

	light_vec = vec_sub(light.position, hit.point);
	angle = vec_dot(light_vec, hit.normal) / (vec_length(light_vec));
	if (angle >= 0 && angle <= 1)
		return (true);
	return (false);
}

void	add_light(t_scene *scene, t_light *light)
{
	light->next = scene->lights;
	scene->lights = light;
}

t_color	base_color_mode(t_hit *hit)
{
	if (!ft_strcmp(MODE, "SIMPLE"))
		return (hit->object->color);
	else if (!ft_strcmp(MODE, "DISRUPTION"))
		return (color_disruption(*hit));
	else if (!ft_strcmp(MODE, "TEXTURE"))
		return (texture_object(hit));
	return (print_error("Incorrect mode", NULL), (t_color){255, 255, 255});
}
