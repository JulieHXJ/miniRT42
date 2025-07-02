/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:25:33 by junjun            #+#    #+#             */
/*   Updated: 2025/07/02 17:39:59 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define THREAD_COUNT 8

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
			int i = 50;
			color = (t_color){0, 0, 0};
			while (i-- > 0)
				color = color_add(color, antialiasing(scene, x, y));
			color = color_scale(color, 1 / 50.0f);
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
	mlx_key_hook(scene->mlx, key_hook, scene);
	mlx_scroll_hook(scene->mlx, &zooming, scene);
	mlx_loop(scene->mlx);
	return (true);
}
