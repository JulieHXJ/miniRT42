/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:17:55 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/02 19:03:02 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static t_color	**init_color_buffer(mlx_image_t img)
{
	t_color		**result;
	uint32_t	x;
	uint32_t	y;

	result = malloc(sizeof(t_color *) * img.height);
	if (!result)
		return (NULL); 			// ---------> gclist
	y = -1;
	while (++y < img.height)
	{
		result[y] = malloc(sizeof(t_color) * img.width);
		if (!result[y])
			return (NULL); 			// Handle or free earlier allocations
		x = -1;
		while (++x < img.width)
			result[y][x] = (t_color){0, 0, 0};
	}
	return (result);
}

// static int	**init_sample_count(mlx_image_t img)
// {
// 	int			**count;
// 	uint32_t	x;
// 	uint32_t	y;

// 	count = malloc(sizeof(int *) * img.height);
// 	if (!count)
// 		return (NULL);
// 	y = -1;
// 	while (++y < img.height)
// 	{
// 		count[y] = malloc(sizeof(int) * img.width);
// 		if (!count[y])
// 			return (NULL);
// 		x = -1;
// 		while (++x < img.width)
// 			count[y][x] = 0;
// 	}
// 	return (count);
// }


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
static void	initial_render(void *arg)
{
	t_scene		*scene;
	t_render	render;
	t_color		new_color;
	uint32_t	x;
	uint32_t	y;

	scene = (t_scene *)arg;
	render = scene->render;
	render.i++;
	y = -1;
	while (++y < scene->img->height)
	{
		x = -1;
		while (++x < scene->img->width)
		{
			new_color = antialiasing(scene, x, y);
			render.color[y][x] = color_scale(render.color[y][x], (render.i - 1) / render.i);
			render.color[y][x] = color_add(render.color[y][x], color_scale(new_color, 1 / render.i));
			gamma_correction(&render.color[y][x]);
			mlx_put_pixel(scene->img, x, y, convert_color(render.color[y][x]));
		}
	}
}

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
	scene->render.color = init_color_buffer(*scene->img);
	scene->render.i = 0;
	initial_render(scene);
	if (mlx_image_to_window(scene->mlx, scene->img, 0, 0) < 0)
		return (print_error("Failed to attach image to window", *gc_list),
			false);
	mlx_loop_hook(scene->mlx, &initial_render, scene);
	// mlx_key_hook(scene->mlx, key_hook, scene);
	// mlx_scroll_hook(scene->mlx, &zooming, scene);
	mlx_loop(scene->mlx);
	return (true);
}
