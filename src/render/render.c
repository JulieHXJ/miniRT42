/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:25:33 by junjun            #+#    #+#             */
/*   Updated: 2025/07/02 16:33:35 by xhuang           ###   ########.fr       */
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

// void	*thread_draw(void *arg)
// {
// 	t_thread_data	*d = (t_thread_data *)arg;
// 	uint32_t		x, y;
// 	// t_ray			ray;
// 	// t_hit			hit;
// 	t_color			color;

// 	uint32_t start_y = (d->scene->img->height / d->thread_count) * d->id;
// 	uint32_t end_y = (d->id == d->thread_count - 1)
// 		? d->scene->img->height
// 		: (d->scene->img->height / d->thread_count) * (d->id + 1);

// 	y = start_y - 1;
// 	while (++y < end_y)
// 	{
// 		x = -1;
// 		while (++x < d->scene->img->width)
// 		{
// 			color = antialiasing(d->scene, x, y);
// 			gamma_correction(&color);
// 			mlx_put_pixel(d->scene->img, x, y, convert_color(color));
// 			// ray = ray_to_vp(d->scene, x, y);
// 			// if (if_hit(d->scene, ray, &hit))
// 			// {
// 			// 	if (is_lighted_pixel(*d->scene, hit))
// 			// 		color = lighted_pixel(*d->scene, hit);
// 			// 	else
// 			// 		color = unlighted_pixel(*d->scene, hit);
// 			// }
// 			// else
// 			// 	color = checkered_background(x, y);
// 			// mlx_put_pixel(d->scene->img, x, y, convert_color(color));
// 		}
// 	}
// 	return NULL;
// }


// void	draw_img(t_scene *scene)
// {
// 	pthread_t		threads[THREAD_COUNT];
// 	t_thread_data	*thread_data;
// 	int i;

// 	i = 0;
// 	thread_data = malloc(sizeof(t_thread_data) * THREAD_COUNT);
// 	if (!thread_data)
// 		return ;

// 	while (i < THREAD_COUNT)
// 	{
// 		thread_data[i].id = i;
// 		thread_data[i].thread_count = THREAD_COUNT;
// 		thread_data[i].scene = scene;
// 		if (pthread_create(&threads[i], NULL, thread_draw, &thread_data[i]) != 0)
// 		{
// 			perror("Thread creation failed");
//             free(thread_data);
//             return;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < THREAD_COUNT)
// 	{
// 		pthread_join(threads[i], NULL);
// 		i++;
// 	}
// 	free(thread_data);
// }



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
	mlx_key_hook(scene->mlx, key_hook, scene);
	mlx_scroll_hook(scene->mlx, &zooming, scene);//todo
	// mlx_loop_hook(scene->mlx, loop_hook, scene);
	mlx_loop(scene->mlx);
	return (true);
}
