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

# include <stdbool.h>

# include "vector.h"
# include "objects.h"
# include "gc.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_viewport
{
	float	fov;
	float	aspect_ratio;
	float	view_width;
	float	view_height;
	t_vec3	up;
	t_vec3	right;
	t_vec3	normal;
	t_vec3	up_left_corner;
}			t_viewport;

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
	int				id;
	t_vec3			position;
	float			ratio;
	t_color			color;
	struct s_light	*next;
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

bool	create_environment(char *line, t_scene **scene, t_gc_object **gc_list);
bool	create_objects(char *line, t_scene **scene, t_gc_object **gc_list);
bool	parser(int fd, t_scene **scene, t_gc_object **gc_list);
bool	prepare_render(t_scene *scene, t_gc_object **gc_list);
void	get_cylinder_ends(t_cylinder *c);
void	translate_horizontal(t_scene *scene, float step);
void	translate_vertical(t_scene *scene, float step);
void	rotate_camera(t_scene *scene, float pitch, float yaw);
void	zooming(double xdelta, double ydelta, void *param);
void	key_hook(mlx_key_data_t keydata, void *param);
void	render(void *arg);
void	set_viewport(t_viewport *vp, t_camera *camera);
void	print_scene_info(t_scene *scene);

#endif