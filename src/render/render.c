/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:25:33 by junjun            #+#    #+#             */
/*   Updated: 2025/06/23 18:18:46 by dchrysov         ###   ########.fr       */
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

	y = -1;
	while (++y < scene->img->height)
	{
		x = -1;
		while (++x < scene->img->width)
		{
			ray = ray_to_vp(scene, x, y);
			if (if_hit(scene, ray, &hit))
			{
				if (is_lighted_pixel(*scene, hit))
					color = lighted_pixel(*scene, hit);
				else
					color = unlighted_pixel(*scene, hit);
			}
			else
				color = ambient_pixel(x, y);
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
	// draw the image here
	draw_img(scene);
	if (mlx_image_to_window(scene->mlx, scene->img, 0, 0) < 0)
		return (print_error("Failed to attach image to window", *gc_list),
			false);
	mlx_put_string(scene->mlx, "Hello, miniRT!", 10, 10);
	// Set up hooks
	hook_setup(scene->mlx, key_hook, mouse_hook, scene);
	mlx_loop(scene->mlx);
	return (true);
}
