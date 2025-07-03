/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:23:10 by junjun            #+#    #+#             */
/*   Updated: 2025/07/03 18:05:02 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Reseting the color buffer every time the camera moves.
 */
static void	reset_color_buffer(t_scene *scene)
{
	uint32_t	x;
	uint32_t	y;

	scene->render.i = 0;
	y = -1;
	while (++y < scene->img->height)
	{
		x = -1;
		while (++x < scene->img->width)
			scene->render.color[y][x] = (t_color){0, 0, 0};
	}
}

/**
 * @brief Handle key events for camera movement
 * @note Arrow keys for moving up, down, left, right,
 * C for forward, F for backward
 */
static bool	camera_move(t_scene *scene, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_UP)
		return (translate_vertical(scene, 1.0), true);
	else if (keydata.key == MLX_KEY_DOWN)
		return (translate_vertical(scene, -1.0), true);
	else if (keydata.key == MLX_KEY_LEFT)
		return (translate_horizontal(scene, -1.0), true);
	else if (keydata.key == MLX_KEY_RIGHT)
		return (translate_horizontal(scene, 1.0), true);
	return (false);
}

/**
 * @brief Handle key events for camera rotation
 * @note A for rotate left, D for rotate right,
 * W for rotate up, X for rotate down
 */
static bool	camera_rotate(t_scene *scene, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_A)
		return (rotate_camera(scene, 0.0, -0.1), true);
	else if (keydata.key == MLX_KEY_D)
		return (rotate_camera(scene, 0.0, 0.1), true);
	else if (keydata.key == MLX_KEY_W)
		return (rotate_camera(scene, -0.1, 0.0), true);
	else if (keydata.key == MLX_KEY_X)
		return (rotate_camera(scene, 0.1, 0.0), true);
	return (false);
}

void	zooming(double xdelta, double ydelta, void *param)
{
	t_scene	*scene;
	t_vec3	translation;

	(void)xdelta;
	scene = (t_scene *)param;
	if (ydelta > 0)
	{
		translation = vec_scale(scene->camera.viewport.normal, 2.0);
		scene->camera.origin = vec_add(scene->camera.origin, translation);
		set_viewport(&scene->camera.viewport, &scene->camera);
	}
	else if (ydelta < 0)
	{
		translation = vec_scale(scene->camera.viewport.normal, -2.0);
		scene->camera.origin = vec_add(scene->camera.origin, translation);
		set_viewport(&scene->camera.viewport, &scene->camera);
	}
	reset_color_buffer(scene);
	render(param);
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
}

/**
 * @brief Handle key events for camera translation and rotation
 */
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(scene->mlx);
		else if (keydata.key == MLX_KEY_R)
		{
			scene->camera = scene->cam_restore;
			set_viewport(&scene->camera.viewport, &scene->camera);
			reset_color_buffer(scene);
			render(param);
		}
		else if (camera_move(scene, keydata) || camera_rotate(scene, keydata))
		{
			reset_color_buffer(scene);
			render(param);
		}
	}
}
