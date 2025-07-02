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

static int	**init_sample_count(mlx_image_t img)
{
	int			**count;
	uint32_t	x;
	uint32_t	y;

	count = malloc(sizeof(int *) * img.height);
	if (!count)
		return (NULL);
	y = -1;
	while (++y < img.height)
	{
		count[y] = malloc(sizeof(int) * img.width);
		if (!count[y])
			return (NULL);
		x = -1;
		while (++x < img.width)
			count[y][x] = 0;
	}
	return (count);
}


void	gamma_correction(t_color *color)
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
void	initial_render(t_scene *scene)
{
	uint32_t	x;
	uint32_t	y;
	t_color		**color;
	int			i;

	color = scene->render.accum_buffer;
	color = init_color_buffer(*scene->img);
	scene->render.sample_count = init_sample_count(*scene->img);
	y = -1;
	while (++y < scene->img->height)
	{
		x = -1;
		while (++x < scene->img->width)
		{
			i = 15;
			while (i-- > 0)
				color[y][x] = color_add(color[y][x], antialiasing(scene, x, y));
			color[y][x] = color_scale(color[y][x], 1 / 15.0f);
			scene->render.sample_count[y][x] = 15;
			gamma_correction(&color[y][x]);
			mlx_put_pixel(scene->img, x, y, convert_color(color[y][x]));
		}
	}
}
