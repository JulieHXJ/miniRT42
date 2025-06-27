/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:10:44 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/27 14:38:35 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Calculates light's intensity fallout according to the distance from
 * the source.
 */
static float	fallout(float base_intensity, float distance)
{
	float	k_c;
	float	k_l;
	float	k_q;
	float	denominator;

	k_c = 1.0f;
	k_l = 0.09f;
	k_q = 0.032f;
	denominator = k_c + k_l * distance + k_q * distance * distance;
	return (base_intensity / denominator);
}

static t_color	indirect_light(t_amb_light ambient)
{
	return (color_scale(ambient.color, ambient.ratio));
}

static t_color	direct_light(t_light light, t_vec3 light_vec, t_hit hit)
{
	float	angle;
	float	diffuse_fallout;
	t_color	diffuse_color;
	t_color	result;

	angle = fmaxf(vec_dot(hit.normal, light_vec), 0.0f);
	diffuse_fallout = fallout(light.ratio, vec_length(light_vec));
	diffuse_color = color_scale(light.color, light.ratio);
	result = color_scale(diffuse_color, angle * diffuse_fallout);
	return (result);
}

/**
 * @brief Color the pixels on the light side of the object.
 * @param hit The lighted pixel.
 */
t_color	lighted_pixel(t_scene scene, t_hit hit)
{
	t_vec3		l;
	t_light		light;
	t_amb_light	ambient;
	t_object	obj;
	t_color		result;

	ambient = scene.amb_light;
	light = *scene.light;
	obj = *hit.object;
	if (is_in_shadow(scene, hit))
		return (clamp_color(color_mult(obj.color, indirect_light(ambient))));
	l = vec_sub(light.position, hit.point);
	result = color_add(indirect_light(ambient), direct_light(light, l, hit));
	return (clamp_color(color_mult(obj.color, result)));
}

/**
 * @brief Determines if the hit point should be colored or not.
 */
bool	is_lighted_pixel(t_scene scene, t_hit hit)
{
	double	angle;
	t_vec3	light_vec;

	light_vec = vec_sub(scene.light->position, hit.point);
	angle = vec_dot(light_vec, hit.normal) / (vec_length(light_vec));
	if (angle >= 0 && angle <= 1)
		return (true);
	return (false);
}
