/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:23:10 by junjun            #+#    #+#             */
/*   Updated: 2025/06/18 17:07:09 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(scene->mlx);
		else if (keydata.key == MLX_KEY_UP)
			translate_vertical(scene, 0.1);
		else if (keydata.key == MLX_KEY_DOWN)
			translate_vertical(scene, -0.1);
		else if (keydata.key == MLX_KEY_LEFT)
			translate_horizontal(scene, 0.1);
		else if (keydata.key == MLX_KEY_RIGHT)
			translate_horizontal(scene, -0.1);
		else if (keydata.key == MLX_KEY_W)
			translate_forward(scene, 0.1);
		else if (keydata.key == MLX_KEY_S)
			translate_forward(scene, -0.1);
	}
}

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_scene	*scene;
	int32_t	x;
	int32_t	y;

	(void)mods;
	scene = (t_scene *)param;
	// handle translation here: mouse drag to move camera
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(scene->mlx, &x, &y);
		printf("Mouse clicked at (%d, %d)\n", x, y);
		// rotation functions.
	}
}

/**
 * @brief Set up MLX hooks for keyboard and close events
 *
 * @param mlx MLX instance
 * @param key_hook Function to handle key events
 * @param close_hook Function to handle close events
 * @param param Parameter to pass to hook functions
 */
void	hook_setup(mlx_t *mlx, mlx_keyfunc key_hook, mlx_mousefunc mouse_hook,
		void *param)
{
	if (mlx)
	{
		mlx_key_hook(mlx, key_hook, param);
		mlx_mouse_hook(mlx, mouse_hook, param);
	}
}
