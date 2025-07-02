/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:25:33 by junjun            #+#    #+#             */
/*   Updated: 2025/07/02 19:01:09 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define N_PIXELS_PER_FRAME 500
#define MAX_SAMPLES 100

void	progressive_render(void *param)
{
	t_scene *scene = (t_scene *)param;
	int x, y;
	t_color new_sample;

	for (int i = 0; i < N_PIXELS_PER_FRAME; i++)  // limit work per frame
	{
		x = (int)frand() * (*scene).img->width;
		y = (int)frand() * (*scene).img->height;
		if (scene->render.sample_count[y][x] >= MAX_SAMPLES)
			continue ;
		new_sample = antialiasing(scene, x, y);
		scene->render.accum_buffer[y][x] = color_add(scene->render.accum_buffer[y][x], new_sample);
		scene->render.sample_count[y][x]++;
		t_color avg = color_scale(scene->render.accum_buffer[y][x], 1 / scene->render.sample_count[y][x]);
		gamma_correction(&avg);
		mlx_put_pixel(scene->img, x, y, convert_color(avg));
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
	initial_render(scene);
	if (mlx_image_to_window(scene->mlx, scene->img, 0, 0) < 0)
		return (print_error("Failed to attach image to window", *gc_list),
			false);
	// mlx_loop_hook(scene->mlx, &progressive_render, scene);
	mlx_key_hook(scene->mlx, key_hook, scene);
	mlx_scroll_hook(scene->mlx, &zooming, scene);
	mlx_loop(scene->mlx);
	return (true);
}
