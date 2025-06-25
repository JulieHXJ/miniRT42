/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:25:33 by junjun            #+#    #+#             */
/*   Updated: 2025/06/25 18:51:42 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Draw each pixel of the scene to the image
 */
void	draw_img(t_scene *scene)
{
	uint32_t	x;
	uint32_t	y;
	t_ray		ray;
	t_hit		hit;
	t_color		color;

	// need to change to while loop
	for (y = 0; y < scene->img->height; y++)
	{
		for (x = 0; x < scene->img->width; x++)
		{
			ray = ray_to_vp(scene, x, y);
			if (if_hit(scene, ray, &hit))
			{
				color = hit.object->color; // todo: set color based on object
				// if (condition)
				// {
				// 	//part on surface lighted by the light
				// 	color = calculate_lighting(scene, &hit);
				// }
				// else
				// {
				// 	//shadow
				// 	color = scene->amb_light.color; // todo: set ambient color
				// }
			}
			else
				color = (t_color){0, 0, 0}; // todo: set ambient color
			// Set pixel color
			mlx_put_pixel(scene->img, x, y, convert_color(color));
		}
	}
}

// update: using threads to render the objects
bool	render(t_scene *scene, t_gc_object **gc_list)
{
	scene->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "miniRT", true);
	if (!scene->mlx)
		return (print_error("Failed to initialize MLX42", *gc_list), false);
	scene->img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!scene->img)
	{
		mlx_close_window(scene->mlx);
		return (print_error("Failed to create image", *gc_list), false);
	}
	draw_img(scene);
	if (mlx_image_to_window(scene->mlx, scene->img, 0, 0) < 0)
		return (print_error("Failed to attach image to window", *gc_list),
			false);
	mlx_key_hook(scene->mlx, key_hook, scene);
	mlx_scroll_hook(scene->mlx, zooming, scene);
	mlx_loop(scene->mlx);
	return (true);
}
