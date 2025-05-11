/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:23:10 by junjun            #+#    #+#             */
/*   Updated: 2025/05/11 13:53:48 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// mlx_key_hook(scene.mlx, key_hook, &scene);//todo
// mlx_close_hook(scene.mlx, close_hook, &scene);//todo

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_scene *scene;
    
    scene = (t_scene *)param;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(scene->mlx);
}

void close_hook(void *param)
{
    (void)param; // To avoid unused warning
    // Any cleanup needed before exit
}

void	hook_setup(mlx_t *mlx, void (*key_hook)(), void (*close_hook)(), t_scene *scene)
{
	mlx_key_hook(mlx, keyfunc, &param);//todo
    mlx_close_hook(mlx, close, &param);//todo
}