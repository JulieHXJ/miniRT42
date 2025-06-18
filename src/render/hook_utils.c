/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:54:04 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/18 17:06:42 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	translate_horizontal(t_scene *scene, double step)
{
	t_vec3	translation;

	translation = vec_scale(scene->camera.viewport.right, step);
	scene->camera.origin = vec_add(scene->camera.origin, translation);
	set_viewport(&scene->camera.viewport, &scene->camera);
	draw_img(scene);
}

void	translate_vertical(t_scene *scene, double step)
{
	t_vec3	translation;

	translation = vec_scale(scene->camera.viewport.up, step);
	scene->camera.origin = vec_add(scene->camera.origin, translation);
	set_viewport(&scene->camera.viewport, &scene->camera);
	draw_img(scene);
}

void	translate_forward(t_scene *scene, double step)
{
	t_vec3	translation;

	translation = vec_scale(scene->camera.viewport.normal, step);
	scene->camera.origin = vec_add(scene->camera.origin, translation);
	set_viewport(&scene->camera.viewport, &scene->camera);
	draw_img(scene);
}