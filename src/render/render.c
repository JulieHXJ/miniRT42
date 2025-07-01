/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:25:33 by junjun            #+#    #+#             */
/*   Updated: 2025/07/01 18:15:15 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	gamma_correction(t_color *color)
{
	const float	gamma = 2.2f;
	float		r;
	float		g;
	float		b;

	r = color->r / 255.0f;
	g = color->g / 255.0f;
	b = color->b / 255.0f;
	r = powf(r, 1.0f / gamma);
	g = powf(g, 1.0f / gamma);
	b = powf(b, 1.0f / gamma);
	color->r = (int)(fminf(fmaxf(r, 0.0f), 1.0f) * 255.0f);
	color->g = (int)(fminf(fmaxf(g, 0.0f), 1.0f) * 255.0f);
	color->b = (int)(fminf(fmaxf(b, 0.0f), 1.0f) * 255.0f);
}

/**
 * @brief Draw each pixel of the scene to the image
 * 
 * @note Shoots a ray in a (x,y) pair of coordinates. If the ray hits an object
 * it stores the appropriate info into the hit struct. If not the structure
 * remains empty, except for the .t field where is init as INFINITY
 */
void	draw_img(t_scene *scene)
{
	uint32_t	x;
	uint32_t	y;
	t_color		color;

	y = -1;
	while (++y < scene->img->height)
	{
		x = -1;
		while (++x < scene->img->width)
		{
			color = antialiasing(scene, x, y);
			gamma_correction(&color);
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
	mlx_put_string(scene->mlx, "Hello, miniRT!", 10, 10);
	mlx_key_hook(scene->mlx, key_hook, scene);
	mlx_loop(scene->mlx);
	return (true);
}
