/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:57:47 by junjun            #+#    #+#             */
/*   Updated: 2025/07/03 18:09:14 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/getnextline/inc/get_next_line.h"
# include "../lib/libft/inc/libft.h"
# include "intersect.h"
# include "material.h"
# include "vector.h"
// # include "../bonus/inc/minirt_bonus.h"

/* ************************************************************************** */
/* ENUMS & DEFINES                                                            */
/* ************************************************************************** */

# define USAGE_MSG "Usage: ./minirt scenes/<file_name>.rt"
# define HOOK "arrow keys to move, A/D/W/X to rotate, R to reset camera"
# define RED "\033[31m"
# define RST "\033[0m"

# define WIN_WIDTH 1000
# define WIN_HEIGHT 700

# define ORIENT_MIN -1.0
# define ORIENT_MAX 1.0

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	LIGHT,
	CONE,
}	t_obj_type;

/* ************************************************************************** */
/* CORE MATH STRUCTURES                                                       */
/* ************************************************************************** */

typedef struct s_vec3	t_vec3;
typedef struct s_color	t_color;

/* ************************************************************************** */
/* MEMORY GARBAGE COLLECTOR OBJECT                                            */
/* ************************************************************************** */

typedef struct s_gc_object
{
	void				*ptr;
	bool				marked;
	struct s_gc_object	*next;
}						t_gc_object;

/* ************************************************************************** */
/* BASICS                                                                     */
/* ************************************************************************** */

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

/* ************************************************************************** */
/* OBJECTS                                                                    */
/* ************************************************************************** */

/**
 * @note rgb range: [0, 255]
 */
typedef struct s_sphere
{
	t_vec3	center;
	float	diam;
}			t_sphere;

/**
 * @note normal range: [-1.0, 1.0]
 * @note rgb range: [0, 255]
 */
typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
}			t_plane;

/**
 * @note normal range: [-1.0, 1.0]
 * @note rgb range: [0, 255]
 */
typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	direction;
	float	radius;
	float	height;
	t_vec3	top_center;
	t_vec3	bottom_center;
}			t_cylinder;

/* ************************************************************************** */
/* Generic object structure                                                   */
/* ************************************************************************** */

typedef struct s_object
{
	int				id;
	t_obj_type		type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	} u_data;
	t_color			color;
	t_material		material;
	void			*bonus;
	struct s_object	*next;
}					t_object;

/* ************************************************************************** */
/* RENDERING STRUCTURE                                                        */
/* ************************************************************************** */

typedef struct s_render
{
	t_color			**color;
	unsigned int	i;
}					t_render;

/* ************************************************************************** */
/* SCENE STRUCTURE                                                            */
/* ************************************************************************** */

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

/* ************************************************************************** */
/* FUNCTION PROTOTYPES                                                        */
/* ************************************************************************** */

// Utils
void	free_array(char ***arr);
size_t	array_size(char **arr);
void	print_error(char *str, t_gc_object *gc_list);
float	ft_atod(const char *str);
float	frand(void);

// Check
bool	in_range_int(int value, int min, int max);
bool	in_range_float(float value, float min, float max);
bool	valid_color(t_color color);
bool	valid_ratio(float ratio);
bool	valid_normal(t_vec3 normal);

// Parser
bool	assign_color(char *color, t_color *c, t_gc_object **gc_list);
bool	assign_vector(char *coordinates, t_vec3 *v, t_gc_object **gc_list);
bool	assign_normal(char *normal, t_vec3 *v, t_gc_object **gc_list);
bool	assign_positive_num(char *num, float *value);
bool	create_environment(char *line, t_scene **scene, t_gc_object **gc_list);
bool	create_objects(char *line, t_scene **scene, t_gc_object **gc_list);
bool	parser(int fd, t_scene **scene, t_gc_object **gc_list);
void	get_cylinder_ends(t_cylinder *c);

// Intersections
void	set_viewport(t_viewport *vp, t_camera *camera);
t_ray	ray_to_vp(t_scene *scene, float x, float y);
float	solve_quadratic(float a, float b, float c);
bool	hit_sphere(t_ray ray, t_sphere sphere, t_hit *hit);
bool	hit_plane(t_ray ray, t_plane plane, t_hit *hit);
bool	check_height(t_vec3 point, t_cylinder cylinder);
bool	hit_cylinder(t_ray ray, t_cylinder cylinder, t_hit *hit);
bool	hit_object(t_object *obj, t_ray ray, t_hit *hit);
bool	if_hit(t_scene *scene, t_ray ray, t_hit *hit);

// Lighting
bool	is_lighted_pixel(t_scene scene, t_hit hit);
bool	is_in_shadow(t_scene scene, t_hit hit);
t_color	lighted_pixel(t_scene scene, t_hit hit);
t_color	unlighted_pixel(t_scene scene, t_hit hit);
t_color	checkered_background(uint32_t x, uint32_t y);
t_color	antialiasing(t_scene *scene, uint32_t x, uint32_t y);

// Render
void					translate_horizontal(t_scene *scene, float step);
void					translate_vertical(t_scene *scene, float step);
void					rotate_camera(t_scene *scene, float pitch, float yaw);
// void					draw_img(t_scene *scene);
void					zooming(double xdelta, double ydelta, void *param);
void					key_hook(mlx_key_data_t keydata, void *param);
// void loop_hook(void *param);
// bool					render(t_scene *scene, t_gc_object **gc_list);

void	render(void *arg);

bool	prepare_for_render(t_scene *scene, t_gc_object **gc_list);

// GC
void	*gc_alloc(size_t size, t_gc_object **gc_list);
void	gc_free(t_gc_object *gc_list);
char	**gc_split(const char *s, char c, t_gc_object **gc_list);

// debugging
void	print_scene_info(t_scene *scene);

// Bonus
void	assign_material(char **tokens, t_material *material);

#endif
