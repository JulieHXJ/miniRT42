/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:25:33 by junjun            #+#    #+#             */
/*   Updated: 2025/06/03 17:11:18 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// /**
//  * @brief Create a new ray with origin and direction
//  */
// t_ray	create_ray(t_vec3 camera, t_vec3 direction)
// {
// 	t_ray	ray;

// 	ray.origin = camera;
// 	ray.direction = vec_normalize(direction);
// 	return (ray);
// }

// /**
//  * @brief Generate a ray from camera through a specific pixel
//  */
// t_ray get_cam_ray()
// {
// }

/**
 * @brief Draw each pixel of the scene to the image
 */
static void	draw_pixel(mlx_image_t *img, int x, int y, t_color color)
{


	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return;
    ((uint32_t *)img->pixels)[y * img->width + x] = convert_color(color);

	
	// For each pixel in the viewport
	// for (y = 0; y < scene->camera; y++)
	// {
	// 	for (x = 0; x < scene->camera.width; x++)
	// 	{
	// 		// Generate ray from camera through this pixel
	// 		ray = get_camera_ray(scene, x, y);
	// 		// Initialize hit
	// 		hit.t = INFINITY;
	// 		hit.object = NULL;
	// 		// Cast ray into scene
	// 		if (ray_tracing(scene, ray, &hit))
	// 		{
	// 			// Ray hit something, calculate color based on lighting
	// 			color = calculate_lighting(scene, &hit);
	// 		}
	// 		else
	// 		{
	// 			// Ray didn't hit anything, use background color (gray)
	// 			color = (t_color){0, 0, 0};
	// 		}
	// 		// Set pixel color
	// 		mlx_put_pixel(scene->img, x, y, convert_color(color));
	// 	}
	// }
}

//update: using threads to render the objects
bool	render(t_scene *scene, t_gc_object **gc_list)
{
	int		x;
    int		y;
    t_color	background_color;
	
	// Initialize MLX42 and create a window
    scene->mlx = mlx_init(scene->camera.width, scene->camera.height, "miniRT", true);
    if (!scene->mlx)
        return (print_error("Failed to initialize MLX42", gc_list), false);
	
	scene->img = mlx_new_image(scene->mlx, scene->camera.width, scene->camera.height);
	if (!scene->img)
		return (print_error("Failed to create image", gc_list), false);

	if (mlx_image_to_window(scene->mlx, scene->img, 0, 0) < 0)
    	return (print_error("Failed to attach image to window", gc_list), false);

	
	printf("Starting render...\n");
    // Render multiple samples in parallel
    // while (condition)
    // {
    //     if (create_join_thread(scene, scene->img, gc_list))
    //     {
    //         return (false);
    //     }
    //     update_display(scene, scene->img);
    // }
	
    
    // Scale the ambient light color
    background_color = color_scale(scene->amb_light.color, scene->amb_light.ratio);


	// Draw the background
	for (y = 0; y < scene->camera.height; y++)
	{
		for (x = 0; x < scene->camera.width; x++)
		{
			draw_pixel(scene->img, x, y, background_color);
		}
	}

	// Set up hooks
	// mlx_loop_hook(scene->mlx, &hook_setup, scene);//todo
	// mlx_key_hook(scene->mlx, key_hook, scene);
	// mlx_close_hook(scene->mlx, close_hook, scene);
	mlx_loop(scene->mlx);
	return (true);
}
