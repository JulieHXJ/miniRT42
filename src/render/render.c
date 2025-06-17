/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:25:33 by junjun            #+#    #+#             */
/*   Updated: 2025/06/17 16:26:31 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Draw each pixel of the scene to the image
 */
static void	draw_img(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_hit	hit;
	t_color	color;

	// For each pixel in the viewport
	for (y = 0; y < scene->img->height; y++)
	{
		for (x = 0; x < scene->img->width; x++)
		{
			// Generate ray from camera through this pixel
			ray = ray_to_vp(scene, x, y);
			if (if_hit(scene, ray, &hit))
				color = calculate_lighting(scene, &hit);
			else
				color = (t_color){0, 0, 0}; // todo: set background color
			// Set pixel color
			mlx_put_pixel(scene->img, x, y, convert_color(color));
		}
	}
}

// update: using threads to render the objects
bool	render(t_scene *scene, t_gc_object **gc_list)
{
	t_ray	ray;
	t_hit	*hit;
	t_color	color;

	scene->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "miniRT", true);
	if (!scene->mlx)
		return (print_error("Failed to initialize MLX42", *gc_list), false);
	scene->img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!scene->img)
		return (print_error("Failed to create image", *gc_list), false);
	// draw the image here
	draw_img(scene);


	
	if (mlx_image_to_window(scene->mlx, scene->img, 0, 0) < 0)
		return (print_error("Failed to attach image to window", *gc_list),
			false);
	mlx_put_string(scene->mlx, "Hello, miniRT!", 10, 10);
	// Set up hooks
	// mlx_loop_hook(scene->mlx, &hook_setup, scene);//todo
	// mlx_key_hook(scene->mlx, key_hook, scene);
	// mlx_close_hook(scene->mlx, close_hook, scene);
	mlx_loop(scene->mlx);
	return (true);
}
