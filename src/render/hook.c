/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:23:10 by junjun            #+#    #+#             */
/*   Updated: 2025/05/19 17:39:37 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// mlx_key_hook(scene.mlx, key_hook, &scene);//todo
// mlx_close_hook(scene.mlx, close_hook, &scene);//todo

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_scene *scene;
    
    scene = (t_scene *)param;

    if (mlx_is_key_down(scene->mlx, MLX_KEY_ESCAPE))
    {
        mlx_close_window(scene->mlx);
    }

    // handle other keys here: left, right, up, down as rotation.
    if (mlx_is_key_down(scene->mlx, MLX_KEY_UP))
		rotate_vertical(scene, 1.0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_DOWN))
		rotate_vertical(scene, -1.0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT))
		rotate_horizontal(scene, 1.0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT))
		rotate_horizontal(scene, -1.0);
}

void mouse_hook(void *param)
{
    (void)param; // To avoid unused warning
    // Any cleanup needed before exit
}

/**
 * @brief Set up MLX hooks for keyboard and close events
 * 
 * @param mlx MLX instance
 * @param key_hook Function to handle key events
 * @param close_hook Function to handle close events
 * @param param Parameter to pass to hook functions
 */
void hook_setup(mlx_t *mlx, mlx_keyfunc key_hook, mlx_closefunc close_hook, void *param)
{
    if (mlx)
    {
        mlx_key_hook(mlx, key_hook, param);
        mlx_close_hook(mlx, close_hook, param);
    }
}
