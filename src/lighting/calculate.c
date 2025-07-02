/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:10:44 by xhuang            #+#    #+#             */
/*   Updated: 2025/07/02 12:49:08 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define SAMPLES 2

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

t_color	antialiasing(t_scene *scene, uint32_t x, uint32_t y)
{
	t_ray	ray;
	t_hit	hit;
	t_color	color;
	int		i;
	int		j;

	color = (t_color){0, 0, 0};
	i = -1;
	while (++i < SAMPLES)
	{
		j = -1;
		while (++j < SAMPLES)
		{
			ray = ray_to_vp(scene, x + (i + 0.5f) / SAMPLES, y + (i + 0.5f) / SAMPLES);
			if (if_hit(scene, ray, &hit))
			{
				if (is_lighted_pixel(*scene, hit))
					color = color_add(color, lighted_pixel(*scene, hit));
				else
					color = color_add(color, unlighted_pixel(*scene, hit));
			}
			else
				color = color_add(color, checkered_background(x + (i + 0.5f) / SAMPLES, y + (i + 0.5f) / SAMPLES));
		}
	}
	return (clamp_color(color_scale(color, 1.0f / (SAMPLES * SAMPLES))));
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
