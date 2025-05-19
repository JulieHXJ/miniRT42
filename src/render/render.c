/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:25:33 by junjun            #+#    #+#             */
/*   Updated: 2025/05/19 17:31:19 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void 


// void render(t_scene *scene, mlx_image_t *img, t_gc_object **gc_list)
// {
//     int x, y;
//     t_color color;

//     for (y = 0; y < img->height; y++)
//     {
//         for (x = 0; x < img->width; x++)
//         {
//             // Calculate the color for each pixel
//             color = new_color(x % 256, y % 256, (x + y) % 256);
//             mlx_put_pixel(img, x, y, convert_color(color));
//         }
//     }
// }

bool graphic(t_scene *scene, t_gc_object **gc_list)
{

    // Initialize MLX and create a new image
    scene->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "miniRT", true);
    if (!scene->mlx)
        return (false);
    scene->img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!scene->img)
    {
        mlx_terminate(scene->mlx);
        return (false);
    }
    // Render the scene here. is it necessary to pass gc_list? i think we are not creating anything here
    if (!render(scene, scene->img, gc_list))
    {
        mlx_terminate(scene->mlx);
        return (false);
    }

    mlx_image_to_window(scene->mlx, scene->img, 0, 0);
    mlx_loop_hook(scene->mlx, &hook_setup, scene);//todo
	mlx_loop(scene->mlx);
	mlx_terminate(scene->mlx);
    return (true);
}
