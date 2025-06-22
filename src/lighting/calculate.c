/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:10:44 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/22 19:28:00 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Determines if the hit point should be colored or not.
 */
bool	is_colored_pixel(t_scene scene, t_hit hit)
{
	double	magnitude;

	magnitude = vec_dot(scene.light->position, hit.normal);
	if (magnitude >= 0 && magnitude <= 1)
		return (true);
	return (false);
}

t_color	color_pixel(t_scene *scene, t_hit *hit)
{
	t_vec3	light_dir;
	double	diffuse;
	t_color	final_color;

	light_dir = vec_normalize(vec_sub((*scene).light->position, (*hit).point));
	if (vec_dot((*hit).normal, light_dir) > 0)
		diffuse = vec_dot((*hit).normal, light_dir);
	else
		diffuse = 0.0;
	final_color.r = (*hit).object->color.r * (*scene).light->color.r * diffuse ;
	final_color.r += (*scene).amb_light.color.r * (*scene).amb_light.ratio;
	final_color.g = (*hit).object->color.g * (*scene).light->color.g * diffuse ;
	final_color.g += (*scene).amb_light.color.g * (*scene).amb_light.ratio;
	final_color.b = (*hit).object->color.b * (*scene).light->color.b * diffuse ;
	final_color.b += (*scene).amb_light.color.b * (*scene).amb_light.ratio;
	return (final_color);
}
