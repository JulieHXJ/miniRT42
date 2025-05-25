/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:25:33 by junjun            #+#    #+#             */
/*   Updated: 2025/05/25 21:01:06 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Create a new ray with origin and direction
 */
t_ray	create_ray(t_vec3 camera, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = camera;
	ray.direction = vec_normalize(direction);
	return (ray);
}

/**
 * @brief Generate a ray from camera through a specific pixel
 */
t_ray get_cam_ray()
{
    
}

/**
 * @brief Draw each pixel of the scene to the image
 */
void	draw_pixel()
{
	t_color	color;

	int x, y;
	// For each pixel in the viewport
	for (y = 0; y < scene->camera.height; y++)
	{
		for (x = 0; x < scene->camera.width; x++)
		{
			// Generate ray from camera through this pixel
			ray = get_camera_ray(scene, x, y);
			// Initialize hit
			hit.t = INFINITY;
			hit.object = NULL;
			// Cast ray into scene
			if (ray_tracing(scene, ray, &hit))
			{
				// Ray hit something, calculate color based on lighting
				color = calculate_lighting(scene, &hit);
			}
			else
			{
				// Ray didn't hit anything, use background color (gray)
				color = (t_color){0, 0, 0};
			}
			// Set pixel color
			mlx_put_pixel(scene->img, x, y, convert_color(color));
		}
	}
}

//update: using threads to render the objects
bool	render(t_scene *scene, t_gc_object **gc_list)
{
	// Initialize MLX and create a new image
	scene->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "miniRT", true);
	if (!scene->mlx)
		return (false);
	scene->img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!scene->img)
		return (mlx_terminate(scene->mlx), false);

	printf("Starting render...\n");
    // if (!draw_pixel(scene, scene->img, gc_list))
	// {
	// 	mlx_terminate(scene->mlx);
	// 	return (false);
	// }
    
    
    // Render multiple samples
    //todo
    while (condition)
    {
        if (create_join_thread(scene, scene->img, gc_list))
        {
            return (false);
        }
        update_display(scene, scene->img);
    }
    
    
    
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
	// Set up hooks
	// mlx_loop_hook(scene->mlx, &hook_setup, scene);//todo
	mlx_key_hook(scene->mlx, key_hook, scene);
	mlx_close_hook(scene->mlx, close_hook, scene);
	mlx_loop(scene->mlx);
	// mlx_terminate(scene->mlx);
	return (true);
}
