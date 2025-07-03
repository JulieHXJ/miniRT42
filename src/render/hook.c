/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:23:10 by junjun            #+#    #+#             */
/*   Updated: 2025/07/03 15:02:46 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Handle key events for camera movement
 * @note Arrow keys for moving up, down, left, right,
 * C for forward, F for backward
 */
static bool	key_hook_move(t_scene *scene, mlx_key_data_t keydata)
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
static bool	key_hook_rotate(t_scene *scene, mlx_key_data_t keydata)
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
	// draw_img(scene);
	// mlx_image_to_window(scene->mlx, scene->img, 0, 0);
	scene->if_update = true;
}

/**
 * @brief Handle key events for camera translation and rotation
 */
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_scene	*scene;
	bool	update;

	update = false;
	scene = (t_scene *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(scene->mlx);
		else if (keydata.key == MLX_KEY_R)
		{
			scene->camera.origin = new_vector(0, 0, 0);
			scene->camera.direction = vec_normal(new_vector(0, -1, 0));
			scene->camera.fov = 60.0;
			set_viewport(&scene->camera.viewport, &scene->camera);
			// draw_img(scene);
			scene->if_update = true;
		}
		else
		{
			if (key_hook_move(scene, keydata) || key_hook_rotate(scene, keydata))
				scene->if_update = true;
		}
	}
}

void loop_hook(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (scene->if_update)
	{
		draw_img(scene);
		scene->if_update = false;
	}
}
