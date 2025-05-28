/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:35:30 by dchrysov          #+#    #+#             */
/*   Updated: 2025/05/28 17:13:16 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/**
 * @brief Initialize camera with default values
 */
static void	camera_init(t_scene **scene, t_gc_object **list)
{
	(*scene)->camera = gc_alloc(sizeof(t_camera), list);
	if (!(*scene)->camera)
		return (print_error("Camera allocation failed", *list));
	(*scene)->camera->position = new_vector(0, 0, 0);
	(*scene)->camera->direction = new_vector(0, 0, -1);
	(*scene)->camera->fov = 70.0;
	// (*scene)->camera->cam_orient = new_vector(0, 1, 0);
	// (*scene)->camera->width = WIN_WIDTH;
	// (*scene)->camera->height = WIN_HEIGHT;
}

/**
 * @brief Initializes ambient light with default values
 */
static void	ambient_light_init(t_scene **scene, t_gc_object **gc_list)
{
	(*scene)->amb_light = gc_alloc(sizeof(t_amb_light), gc_list);
	if (!(*scene)->amb_light)
		return ((void)print_error("Ambient light alloc failed", *gc_list));
	(*scene)->amb_light->ratio = 0.0;
	(*scene)->amb_light->color = (t_color){0, 0, 0};
}

/**
 * @brief Initializes light with default values
 */
static void	light_init(t_scene **scene, t_gc_object **gc_list)
{
	(*scene)->light = gc_alloc(sizeof(t_amb_light), gc_list);
	if (!(*scene)->light)
		return ((void)print_error("Light alloc failed", *gc_list));
	(*scene)->light->color = (t_color){0, 0, 0};
	(*scene)->light->position = (t_vec3){0.0, 0.0, 0.0};
	(*scene)->light->brightness = 0.0;
	(*scene)->light->next = NULL;
}

/**
 * @brief Initialize mlx-related fields to NULL or 0
 */
static void	mlx_related_init(t_scene *scene)
{
	scene->mlx = NULL;
	scene->win = NULL;
	scene->img = NULL;
	scene->addr = NULL;
	scene->bits_per_pixel = 0;
	scene->line_length = 0;
	scene->endian = 0;
}

/**
 * @brief Allocates and initializes a new scene
 *
 * @param list Garbage collector list for tracking mallocs
 * @return t_scene* Pointer to the initialized scene,
	or NULL if allocation fails
 */
t_scene	*scene_init(t_gc_object **gc_list)
{
	t_scene	*scene;

	scene = gc_alloc(sizeof(t_scene), gc_list);
	if (!scene)
		return (print_error("Scene alloc failed", *gc_list), NULL);
	scene->obj = NULL;
	light_init(&scene, gc_list);
	ambient_light_init(&scene, gc_list);
	camera_init(&scene, gc_list);
	mlx_related_init(scene);
	return (scene);
}
