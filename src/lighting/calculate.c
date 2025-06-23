/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:10:44 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/23 17:21:35 by dchrysov         ###   ########.fr       */
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

/**
 * @brief Restricts the value between the range [0, 255].
 */
static int	clamp_color(float value)
{
	if (value < 0.0f)
		return (0);
	if (value > 255.0f)
		return (255);
	return ((int)(value + 0.5f));
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

t_color	lighted_pixel(t_scene scene, t_hit hit)
{
	t_vec3		light_v;
	t_light		light;
	t_amb_light	ambient;
	t_color		obj_clr;
	t_color		result;

	light_v = vec_sub(scene.light->position, hit.point);
	ambient = scene.amb_light;
	light = *scene.light;
	obj_clr = hit.object->color;
	result.r = clamp_color(obj_clr.r / 255.0f * (ambient.color.r * ambient.ratio
				+ light.color.r * light.ratio
				* fallout(light.ratio, vec_length(light_v))
				* fmaxf(vec_dot(hit.normal, light_v), 0.0f)));
	result.g = clamp_color(obj_clr.g / 255.0f * (ambient.color.g * ambient.ratio
				+ light.color.g * light.ratio
				* fallout(light.ratio, vec_length(light_v))
				* fmaxf(vec_dot(hit.normal, light_v), 0.0f)));
	result.b = clamp_color(obj_clr.b / 255.0f * (ambient.color.b * ambient.ratio
				+ light.color.b * light.ratio
				* fallout(light.ratio, vec_length(light_v))
				* fmaxf(vec_dot(hit.normal, light_v), 0.0f)));
	return (result);
}

t_color	unlighted_pixel(t_scene scene, t_hit hit)
{
	t_amb_light	ambient;
	t_color		obj_clr;
	t_color		result;

	ambient = scene.amb_light;
	obj_clr = hit.object->color;
	obj_clr.r *= (ambient.color.r * ambient.ratio) / 255.0f;
	obj_clr.g *= (ambient.color.g * ambient.ratio) / 255.0f;
	obj_clr.b *= (ambient.color.b * ambient.ratio) / 255.0f;
	result.r = clamp_color(obj_clr.r);
	result.g = clamp_color(obj_clr.g);
	result.b = clamp_color(obj_clr.b);
	return (result);
}
