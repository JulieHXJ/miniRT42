/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:23:10 by junjun            #+#    #+#             */
/*   Updated: 2025/06/22 19:48:37 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static void	key_hook_move(t_scene *scene, mlx_key_data_t keydata)
// {
// 	if (keydata.key == MLX_KEY_UP)
// 		translate_vertical(scene, 0.1);
// 	else if (keydata.key == MLX_KEY_DOWN)
// 		translate_vertical(scene, -0.1);
// 	else if (keydata.key == MLX_KEY_LEFT)
// 		translate_horizontal(scene, -0.1);
// 	else if (keydata.key == MLX_KEY_RIGHT)
// 		translate_horizontal(scene, 0.1);
// 	else if (keydata.key == MLX_KEY_C)
// 		translate_forward(scene, 10);
// 	else if (keydata.key == MLX_KEY_F)
// 		translate_forward(scene, -10);
// }

void	key_hook_rotate(t_scene *scene, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_A)
		rotate_camera(scene, 0.0, -0.1); // left
	else if (keydata.key == MLX_KEY_D)
		rotate_camera(scene, 0.0, 0.1); // right
	else if (keydata.key == MLX_KEY_W)
		rotate_camera(scene, 0.1, 0.0); // up
	else if (keydata.key == MLX_KEY_X)
		rotate_camera(scene, -0.1, 0.0); // down
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
			scene->camera.origin = new_vector(0, 0, 0);
			scene->camera.direction = vec_normalize(new_vector(0, -1, 0));
			scene->camera.fov = 60.0;
			set_viewport(&scene->camera.viewport, &scene->camera);
			draw_img(scene);
		}
		if (keydata.key == MLX_KEY_UP)
			translate_vertical(scene, 1.0);
		else if (keydata.key == MLX_KEY_DOWN)
			translate_vertical(scene, -1.0);
		else if (keydata.key == MLX_KEY_LEFT)
			translate_horizontal(scene, -1.0);
		else if (keydata.key == MLX_KEY_RIGHT)
			translate_horizontal(scene, 1.0);
		else if (keydata.key == MLX_KEY_C)
			translate_forward(scene, 5.0);
		else if (keydata.key == MLX_KEY_F)
			translate_forward(scene, -5.0);
		else
		{
			// key_hook_move(scene, keydata);
			key_hook_rotate(scene, keydata);
		}


	}
}
