/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:54:04 by xhuang            #+#    #+#             */
/*   Updated: 2025/07/01 14:59:54 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	translate_horizontal(t_scene *scene, float step)
{
	t_vec3	translation;

	translation = vec_scale(scene->camera.viewport.right, step);
	scene->camera.origin = vec_add(scene->camera.origin, translation);
	set_viewport(&scene->camera.viewport, &scene->camera);
	draw_img(scene);
}

void	translate_vertical(t_scene *scene, float step)
{
	t_vec3	translation;

	translation = vec_scale(scene->camera.viewport.up, step);
	scene->camera.origin = vec_add(scene->camera.origin, translation);
	set_viewport(&scene->camera.viewport, &scene->camera);
	draw_img(scene);
}

void	translate_forward(t_scene *scene, float step)
{
	t_vec3	translation;

	translation = vec_scale(scene->camera.viewport.normal, step);
	scene->camera.origin = vec_add(scene->camera.origin, translation);
	set_viewport(&scene->camera.viewport, &scene->camera);
	draw_img(scene);
}

// t_vec3	rotate_x(t_vec3 direction, float angle)
// {
// 	t_vec3	new;

// 	printf("rotate_x before: %f %f %f\n", direction.x, direction.y,
// 		direction.z);
// 	new.x = direction.x;
// 	new.y = direction.y * cos(angle) - direction.z * sin(angle);
// 	new.z = direction.y * sin(angle) + direction.z * cos(angle);
// 	printf("rotate_x after: %f %f %f\n", new.x, new.y, new.z);
// 	return (new);
// }

// t_vec3	rotate_z(t_vec3 direction, float angle)
// {
// 	t_vec3	new;

// 	printf("rotate_z before: %f %f %f\n", direction.x, direction.y,
// 		direction.z);
// 	new.x = direction.x * cos(angle) - direction.y * sin(angle);
// 	new.y = direction.x * sin(angle) + direction.y * cos(angle);
// 	new.z = direction.z;
// 	printf("rotate_z after: %f %f %f\n", new.x, new.y, new.z);
// 	return (new);
// }

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
	t_vec3 dir;
	t_viewport *vp;

	vp = &scene->camera.viewport;
	dir = scene->camera.direction;

	// Rotate around local right vector (up/down)
	if (pitch != 0.0)
		dir = rotate_axis(dir, vp->right, pitch);

	// Rotate around local up vector (left/right)
	if (yaw != 0.0)
		dir = rotate_axis(dir, vp->up, yaw);

	scene->camera.direction = vec_normal(dir);

	// Apply pitch (x-axis), then yaw (z-axis)
	// scene->camera.direction = rotate_x(scene->camera.direction, pitch);
	// scene->camera.direction = rotate_z(scene->camera.direction, yaw);
	// scene->camera.direction = vec_normal(scene->camera.direction);

	set_viewport(&scene->camera.viewport, &scene->camera);
	draw_img(scene);
}
