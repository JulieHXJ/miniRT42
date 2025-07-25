/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:10:44 by xhuang            #+#    #+#             */
/*   Updated: 2025/07/04 14:41:04 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../../bonus/inc/minirt_bonus.h"

#define SPECULAR 1.0f   // Specular strength [0.0 - 1.0]
#define SHININESS 32.0f // Shininess factor [8.0 - 256]

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

static t_color	specular_color(t_vec3 light_dir, t_camera cam, t_hit hit,
		t_light light)
{
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	t_vec3	i;
	float	spec_angle;
	float	spec_factor;

	view_dir = vec_normal(vec_sub(cam.origin, hit.point));
	i = vec_scale(light_dir, -1.0f);
	reflect_dir = vec_sub(i, vec_scale(hit.normal, 2.0f * vec_dot(i,
					hit.normal)));
	spec_angle = fmaxf(vec_dot(view_dir, reflect_dir), 0.0f);
	spec_factor = powf(spec_angle, SHININESS);
	return (color_scale(light.color, SPECULAR * spec_factor));
}

t_color	color_pixel(t_scene *scene, uint32_t x, uint32_t y)	// **gc_list
{
	t_hit	hit;
	t_color	color;
	t_light	*light;
	t_color	base_color;
	t_color	final;

	if (!if_hit(scene, ray_to_vp(scene, x, y), &hit))
		return (clamp_color(checkered_background(x, y)));
	base_color = base_color_mode(&hit);
	final = color_scale(scene->amb_light.color, scene->amb_light.ratio);
	final = color_mult(base_color, final);
	light = scene->lights;
	while (light)
	{
		if (is_lighted_pixel(hit, *light))
			color = lighted_pixel(*scene, hit, light, base_color);
		else
			color = (t_color){0, 0, 0};
		final = color_add(final, color);
		light = light->next;
	}
	return (clamp_color(final));
}

/**
 * @brief Color the pixels on the light side of the object.
 * @param hit The lighted pixel.
 */
t_color	lighted_pixel(t_scene scene, t_hit hit, t_light *light, t_color obj_c)
{
	t_color	result;
	t_vec3	light_dir;
	t_color	spec_color;

	result = (t_color){0, 0, 0};
	light_dir = vec_sub(scene.lights->position, hit.point);
	if (!is_in_shadow(scene, hit, light))
	{
		result = direct_light(*light, light_dir, hit);
		spec_color = specular_color(vec_normal(light_dir), scene.camera, hit,
				*light);
		result = color_add(result, spec_color);
	}
	return (clamp_color(color_mult(obj_c, result)));
}
