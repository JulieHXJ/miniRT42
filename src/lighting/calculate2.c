/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:26:36 by dchrysov          #+#    #+#             */
/*   Updated: 2025/06/25 14:35:42 by dchrysov         ###   ########.fr       */
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

static t_object	*target_object(t_object	*object, int id)
{
	while (object)
	{
		if (object->id == id)
			return (object);
		object = object->next;
	}
	return (NULL);
}

bool	is_shadowed_pixel(t_scene scene, t_hit hit)
{
	t_object	*target;
	t_ray		light_ray;
	bool		result;

	target = target_object(scene.obj, hit.object->id);
	light_ray.origin = scene.light->position;
	light_ray.direction = vec_normal(vec_sub(hit.point, light_ray.origin));
	// print_vec3("hit", light_ray.direction); pause();
	result = false;
	while (!result && scene.obj)
	{
		if (scene.obj != target)
		{
			// if (scene.obj->type == SPHERE)
			// 	result = hit_sphere(light_ray, *scene.obj, NULL);
			// else if (scene.obj->type == CYLINDER)
			// 	result = hit_cylinder(light_ray, *scene.obj, NULL);
			// else
			// 	result = hit_plane(light_ray, *scene.obj, NULL);
			result = if_hit(&scene, light_ray, NULL);
		}
		scene.obj = scene.obj->next;
	}
	// if (hit.object->id == 0 && !result) {
	// 	printf("Y\n");
	// 	pause();
	// }
	return (result);
}
