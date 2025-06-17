/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:25:33 by junjun            #+#    #+#             */
/*   Updated: 2025/06/13 10:19:22 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// /**
//  * @brief Draw each pixel of the scene to the image
//  */
// static void	draw_pixel(mlx_image_t *img, int x, int y, t_color color)
// {

// 	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
//         return;
//     ((uint32_t *)img->pixels)[y * img->width + x] = convert_color(color);

	
// 	// For each pixel in the viewport
// 	// for (y = 0; y < scene->camera; y++)
// 	// {
// 	// 	for (x = 0; x < scene->camera.width; x++)
// 	// 	{
// 	// 		// Generate ray from camera through this pixel
// 	// 		ray = get_camera_ray(scene, x, y);
// 	// 		// Initialize hit
// 	// 		hit.t = INFINITY;
// 	// 		hit.object = NULL;
// 	// 		// Cast ray into scene
// 	// 		if (ray_tracing(scene, ray, &hit))
// 	// 		{
// 	// 			// Ray hit something, calculate color based on lighting
// 	// 			color = calculate_lighting(scene, &hit);
// 	// 		}
// 	// 		else
// 	// 		{
// 	// 			// Ray didn't hit anything, use background color (gray)
// 	// 			color = (t_color){0, 0, 0};
// 	// 		}
// 	// 		// Set pixel color
// 			mlx_put_pixel(scene->img, x, y, convert_color(color));
// 	// 	}
// 	// }
// }

//update: using threads to render the objects
bool	render(t_scene *scene, t_gc_object **gc_list)
{
	// int		x;
    // int		y;

	scene->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "miniRT", true);
    if (!scene->mlx)
        return (print_error("Failed to initialize MLX42", *gc_list), false);
	
	scene->img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!scene->img)
		return (print_error("Failed to create image", *gc_list), false);



	// render the image here 
	// ray_tracing(scene, gc_list);
	
	
	if (mlx_image_to_window(scene->mlx, scene->img, 0, 0) < 0)
    	return (print_error("Failed to attach image to window", *gc_list), false);

	mlx_put_string(scene->mlx, "Hello, miniRT!", 10, 10);

	// Set up hooks
	// mlx_loop_hook(scene->mlx, &hook_setup, scene);//todo
	// mlx_key_hook(scene->mlx, key_hook, scene);
	// mlx_close_hook(scene->mlx, close_hook, scene);


	mlx_loop(scene->mlx); 
	return (true);
}
