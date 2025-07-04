/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:47:13 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/04 13:49:15 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "vector.h"
# include "intersect.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

/**
 * @note orient range: [-1.0, 1.0]
 * @note fov range: [0, 180], vp_width is calculated based on fov
 * @note screen_up and screen_right are used for camera rotation
 */
typedef struct s_camera
{
	t_vec3		origin;
	t_vec3		direction;
	float		fov;
	int			cam_num;
	t_viewport	viewport;
}				t_camera;

/**
 * @note ratio range: [0.0, 1.0]
 * @note RGB range: [0, 255]
 */
typedef struct s_amb_light
{
	float	ratio;
	t_color	color;
	int		amb_num;
}			t_amb_light;

/**
 * @note brightness range: [0.0, 1.0]
 */
typedef struct s_light
{
	int		id;
	t_vec3	position;
	float	ratio;
	t_color	color;
}			t_light;

typedef struct s_render
{
	t_color			**color;
	unsigned int	i;
}					t_render;

typedef struct s_scene
{
	t_camera	camera;
	t_camera	cam_restore;
	t_amb_light	amb_light;
	t_light		*light;
	t_object	*obj;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_render	render;
}				t_scene;

#endif