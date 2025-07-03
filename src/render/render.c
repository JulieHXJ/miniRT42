/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:17:55 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/03 11:04:56 by dchrysov         ###   ########.fr       */
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
 * @param buff It stores the sum of the colors over all iterations so far.
 * 
 * @note buff is divided by the number of iterations before it gets printed
 * to output the average color.
 */
static void	render(void *arg)
{
	t_scene		*scene;
	t_color		**buff;
	uint32_t	x;
	uint32_t	y;
	t_color		res;

	scene = (t_scene *)arg;
	buff = scene->render.color;
	scene->render.i++;
	y = -1;
	while (++y < scene->img->height)
	{
		x = -1;
		while (++x < scene->img->width)
		{
			buff[y][x] = color_add(buff[y][x], antialiasing(scene, x, y));
			res = color_scale(buff[y][x], 1.0f / scene->render.i);
			gamma_correction(&res);
			mlx_put_pixel(scene->img, x, y, convert_color(res));
		}
	}
}

bool	prepare_for_render(t_scene *scene, t_gc_object **gc_list)
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
	render(scene);
	if (mlx_image_to_window(scene->mlx, scene->img, 0, 0) < 0)
		return (print_error("Failed to attach image to window", *gc_list),
			false);
	mlx_loop_hook(scene->mlx, &render, scene);
	mlx_key_hook(scene->mlx, key_hook, scene);
	mlx_scroll_hook(scene->mlx, &zooming, scene);
	mlx_loop(scene->mlx);
	return (true);
}
