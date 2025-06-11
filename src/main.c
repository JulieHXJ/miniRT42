/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:58:58 by junjun            #+#    #+#             */
/*   Updated: 2025/06/11 19:19:02 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


// t_vec3	new_vector(double x, double y, double z)
// {
// 	t_vec3	v;

// 	v.x = x;
// 	v.y = y;
// 	v.z = z;
// 	return (v);
// }



static void	camera_init(t_scene *scene)
{
	double	fov_rad;
	double	aspect_ratio;
	
	scene->camera.origin = new_vector(0, 0, 0);
	scene->camera.direction = new_vector(0, 0, -1);
	scene->camera.fov = 70.0;
	//default camera facing down
	scene->camera.screen_up = new_vector(0, 1, 0);
	scene->camera.screen_right = new_vector(1, 0, 0);
	//calculate the size of the viewpoint
	fov_rad = scene->camera.fov * M_PI / 180.0;
	aspect_ratio = (double)WIN_WIDTH/ (double)WIN_HEIGHT;
	scene->camera.viewpoint_height = 2.0 * tan(fov_rad / 2.0);
	scene->camera.viewpoint_width = aspect_ratio * scene->camera.viewpoint_height;
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
	(void)ac;
	(void)av;

	gc_list = NULL;
	if (!valid_file(ac, av))
		return (1);
	scene = scene_init(&gc_list);
	if (!scene)
		return (gc_free(gc_list), 1);




	
	// if (!parser(av[1], &scene, &gc_list))
	// 	return (gc_free(gc_list), 1);
	// if (!render(scene, &gc_list))
	// {
	// 	if (scene->mlx)
	// 		mlx_terminate(scene->mlx);
	// 	gc_free(gc_list);
	// 	return (1);
	// }


	scene->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "miniRT", true);
    if (!scene->mlx)
        return (print_error("Failed to initialize MLX42", gc_list), false);
	
	scene->img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!scene->img)
		return (print_error("Failed to create image", gc_list), false);



	// render the image here 

	
	
	if (mlx_image_to_window(scene->mlx, scene->img, 0, 0) < 0)
    	return (print_error("Failed to attach image to window", gc_list), false);

	// mlx_put_string(scene->mlx, "Hello, miniRT!", 10, 10);

	// Set up hooks
	// mlx_loop_hook(scene->mlx, &hook_setup, scene);//todo
	// mlx_key_hook(scene->mlx, key_hook, scene);
	// mlx_close_hook(scene->mlx, close_hook, scene);
	// mlx_loop(scene->mlx);


	mlx_loop(scene->mlx);
	mlx_terminate(scene->mlx);
	gc_free(gc_list);
	return (0);
}
