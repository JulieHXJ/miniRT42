/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:58:58 by junjun            #+#    #+#             */
/*   Updated: 2025/05/11 18:06:02 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Initialize camera with default values
 */
static void camera_init(t_scene *scene)
{
	scene->camera.position = new_vector(0, 0, 0);
	scene->camera.direction = new_vector(0, 0, -1);
	scene->camera.cam_orient = new_vector(0, 1, 0);
	scene->camera.fov = 70.0;
	scene->camera.width = WIN_WIDTH;
	scene->camera.height = WIN_HEIGHT;
}

static void mlx_related_init(t_scene *scene)
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
 * @brief Init scene with the NULL env parameters and allocates memory for one
 * obj node.
 */
void	scene_init(t_scene *scene, t_gc_object **list)
{
    scene->light = NULL;
    scene->light_num = 0;
    scene->obj = NULL;
    scene->amb_light.intensity = 0.0;
    scene->amb_light.color = color_init(0, 0, 0);
	camera_init(scene);
    mlx_related_init(scene);
}

int	main(int ac, char **av)
{
	t_gc_object		*gc_list;
	t_scene			scene;

	if (!valid_file(ac, av))
		return (1);
	gc_list = NULL;
	scene_init(&scene, &gc_list);//what if init fail
	parser(av[1], &scene, &gc_list);//what if parseing fail
	//for checking the parser
	// print_obj(scene);
	scene.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "miniRT", true);
	if (!scene.mlx)
		return(gc_free(&gc_list), 1);
	scene.img = mlx_new_image(scene.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!scene.img)
	{
		mlx_terminate(scene.mlx);
		gc_free(&gc_list);
		return (1);
	}
	render(&scene);//todo
	mlx_image_to_window(scene.mlx, scene.img, 0, 0);
	// Setup hooks
    
	hook_setup(scene.mlx, key_hook, close_hook, &scene);
    
    // Start the loop
    mlx_loop(scene.mlx);
	
	mlx_terminate(scene.mlx);
	gc_free(&gc_list);
	return (0);
}

