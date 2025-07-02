/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:54:04 by xhuang            #+#    #+#             */
/*   Updated: 2025/07/02 12:26:56 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	translate_horizontal(t_scene *scene, float step)
{
	t_vec3	translation;

	translation = vec_scale(scene->camera.viewport.right, step);
	scene->camera.origin = vec_add(scene->camera.origin, translation);
	set_viewport(&scene->camera.viewport, &scene->camera);
}

void	translate_vertical(t_scene *scene, float step)
{
	t_vec3	translation;

	translation = vec_scale(scene->camera.viewport.up, step);
	scene->camera.origin = vec_add(scene->camera.origin, translation);
	set_viewport(&scene->camera.viewport, &scene->camera);
}

// Rodrigues' rotation: Rotate a vector around an axis by angle
t_vec3	rotate_axis(t_vec3 v, t_vec3 axis, float angle)
{
	t_vec3	term1;
	t_vec3	term2;
	t_vec3	term3;

	term1 = vec_scale(v, cos(angle));
	term2 = vec_scale(vec_cross(axis, v), sin(angle));
	term3 = vec_scale(axis, vec_dot(axis, v) * (1 - cos(angle)));
	return (vec_add(vec_add(term1, term2), term3));
}

/**
 * @brief Rotate cam view around the x-axis and z-axis
 */
void	rotate_camera(t_scene *scene, float pitch, float yaw)
{
	t_vec3		dir;
	t_viewport	*vp;

	vp = &scene->camera.viewport;
	dir = scene->camera.direction;
	if (pitch != 0.0)
		dir = rotate_axis(dir, vp->right, pitch);
	if (yaw != 0.0)
		dir = rotate_axis(dir, vp->up, yaw);
	scene->camera.direction = vec_normal(dir);
	set_viewport(&scene->camera.viewport, &scene->camera);
}
