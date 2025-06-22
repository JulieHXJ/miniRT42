/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:58:58 by junjun            #+#    #+#             */
/*   Updated: 2025/06/20 14:41:47 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	viewport_init(t_viewport *vp)
{
	vp->fov = 60.0 * M_PI / 180.0;
	vp->aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	// vp->focal_len = 1.0; // Default distance from camera to viewport
	vp->view_width = 0.0;
	vp->view_height = 0.0;
	vp->up = new_vector(0, 0, 0);
	vp->right = new_vector(0, 0, 0);
	vp->normal = new_vector(0, 0, 0);
	vp->up_left_corner = new_vector(0, 0, 0);
}

static void	camera_init(t_scene *scene)
{
	scene->camera.origin = new_vector(0, 0, 0);
	scene->camera.direction = vec_normalize(new_vector(0, -1, 0));
	scene->camera.fov = 60.0;
	viewport_init(&scene->camera.viewport);
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
	scene->amb_light.ratio = 0.0;
	scene->amb_light.color = (t_color){0, 0, 0};
	scene->light = NULL;
	scene->obj = NULL;
	scene->mlx = NULL;
	scene->img = NULL;
	camera_init(scene);
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
		return (gc_free(gc_list), 1);
	if (!parser(av[1], &scene, &gc_list))
		return (gc_free(gc_list), 1);
	


	printf("============ Scene ============\n");
	print_camera(&scene->camera);
	print_ambient(&scene->amb_light);
	print_light(scene->light);
	print_object(scene->obj);
	printf("================================\n");

	
	if (!render(scene, &gc_list))
	{
		if (scene->mlx)
			mlx_terminate(scene->mlx);
		gc_free(gc_list);
		return (1);
	}
	mlx_terminate(scene->mlx);
	gc_free(gc_list);
	return (0);
}
