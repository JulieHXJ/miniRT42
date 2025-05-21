/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:58:58 by junjun            #+#    #+#             */
/*   Updated: 2025/05/21 19:21:01 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Initialize camera with default values
 */
static void	camera_init(t_scene *scene, t_gc_object **list)
{
	scene->camera = gc_alloc(sizeof(t_camera), list);
	if (!scene->camera)
	{
		print_error("Camera allocation failed", list);
		return ;
	}
	scene->camera.position = new_vector(0, 0, 0);
	scene->camera.direction = new_vector(0, 0, -1);
	scene->camera.cam_orient = new_vector(0, 1, 0);
	scene->camera.fov = 70.0;
	scene->camera.width = WIN_WIDTH;
	scene->camera.height = WIN_HEIGHT;
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
static t_scene	*scene_init(t_gc_object **list)
{
	t_scene	*scene;

	scene = gc_alloc(sizeof(t_scene), list);
	if (!scene)
		return (NULL);
	scene->light = NULL;
	scene->light_num = 0;
	scene->obj = NULL;
	// (*scene)->amb_light = gc_alloc(sizeof(t_amb_light), gc_list);
	// if (!(*scene)->amb_light)
	// 	return (print_error("Ambient light allocation failed", gc_list), false);
	scene->amb_light.intensity = 0.0;
	scene->amb_light.color = (t_color){0, 0, 0};
	camera_init(scene, list);
	mlx_related_init(scene);
	return (scene);
}

int	main(int ac, char **av)
{
	t_gc_object	*gc_list;
	t_scene		*scene;

	gc_list = NULL;
	if (!valid_file(ac, av))
		return (1);
	scene = scene_init(&gc_list);
	if (!scene)
		return (gc_free(&gc_list), 1);
	if (!parser(av[1], scene, &gc_list)) 
		return (gc_free(&gc_list), 1);
	// for checking the parser
	// print_obj(scene);
	// todo
	if (!render(scene, &gc_list))
		return (gc_free(&gc_list), 1);
	// finish and clean up
	gc_free(&gc_list);
	return (0);
}
