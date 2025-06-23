/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:57:47 by junjun            #+#    #+#             */
/*   Updated: 2025/06/23 17:29:25 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/getnextline/inc/get_next_line.h"
# include "../lib/libft/inc/libft.h"
# include "intersect.h"
# include "render.h"
# include "vector.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

/* ************************************************************************** */
/* ENUMS & DEFINES                                                            */
/* ************************************************************************** */

# define USAGE_MSG "Usage: ./minirt scenes/<file_name>.rt"
# define RED "\033[31m"
# define RST "\033[0m"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define ORIENT_MIN -1.0
# define ORIENT_MAX 1.0

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	LIGHT,
	// Bonus
	CONE,
	HYPERBOLOID,
	PARABOLOID
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
	double		fov;
	t_viewport	viewport;
}				t_camera;

/**
 * @note ratio range: [0.0, 1.0]
 * @note RGB range: [0, 255]
 */
typedef struct s_amb_light
{
	double	ratio;
	t_color	color;
}			t_amb_light;

/**
 * @note brightness range: [0.0, 1.0]
 */
typedef struct s_light
{
	t_vec3	position;
	double	ratio;
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
	double	diam;
	double	specular;   // For bonus specular lighting
	double	reflective; // For bonus reflections
}			t_sphere;

/**
 * @note normal range: [-1.0, 1.0]
 * @note rgb range: [0, 255]
 */
typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	double	specular;   // For bonus specular lighting
	double	reflective; // For bonus reflections
}			t_plane;

/**
 * @note normal range: [-1.0, 1.0]
 * @note rgb range: [0, 255]
 */
typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	direction;
	double	radius; // Diameter / 2
	double	height;
	t_vec3	top_center;
	t_vec3	bottom_center;
	double 	specular;   // For bonus specular lighting
	double	reflective; // For bonus reflections
}						t_cylinder;

/* ************************************************************************** */
/* Generic object structure                                                   */
/* ************************************************************************** */

typedef struct s_object
{
	t_obj_type		type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	}	u_data;
	t_color			color;
	struct s_object	*next;
	struct s_object	*previous;
}					t_object;

/* ************************************************************************** */
/* SCENE STRUCTURE                                                            */
/* ************************************************************************** */

typedef struct s_scene
{
	t_camera	camera;
	t_amb_light	amb_light;
	t_light		*light;
	t_object	*obj;
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_scene;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES                                                        */
/* ************************************************************************** */

// Utils
void	free_array(char ***arr);
size_t	array_size(char **arr);
void	print_error(char *str, t_gc_object *gc_list);
double	ft_atod(const char *str);

// Check
bool	valid_file(int ac, char **av);
bool	in_range_int(int value, int min, int max);
bool	in_range_double(double value, double min, double max);
bool	valid_color(t_color color);
bool	valid_ratio(double ratio);
bool	valid_normal(t_vec3 normal);

// Parser
bool	assign_color(char *color, t_color *c,
			t_gc_object **gc_list);
bool	assign_vector(char *coordinates, t_vec3 *v,
			t_gc_object **gc_list);
bool	assign_normal(char *normal, t_vec3 *v,
			t_gc_object **gc_list);
bool	assign_positive_num(char *num, double *value);
void	get_cylinder_ends(t_cylinder c);
bool	create_environment(char *line, t_scene **scene,
			t_gc_object **gc_list);
bool	create_objects(char *line, t_scene **scene,
			t_gc_object **gc_list);
bool	parser(char *fname, t_scene **scene,
			t_gc_object **gc_list);

// Intersections
void	set_viewport(t_viewport *vp, t_camera *camera);
t_ray	ray_to_vp(t_scene *scene, double x, double y);
double	solve_quadratic(double a, double b, double c);
bool	hit_sphere(t_ray ray, t_object obj, t_hit *hit);
bool	hit_plane(t_ray ray, t_object obj, t_hit *hit);
bool	check_height(t_vec3 point, t_cylinder cylinder);
bool	hit_sides(t_ray ray, t_object obj, t_hit *hit);
bool	hit_caps(t_ray ray, t_object obj, t_hit *hit);
bool	hit_cylinder(t_ray ray, t_object obj, t_hit *hit);
bool	if_hit(t_scene *scene, t_ray ray, t_hit *hit);

// Lighting
bool	is_lighted_pixel(t_scene scene, t_hit hit);
t_color	lighted_pixel(t_scene scene, t_hit hit);
t_color	unlighted_pixel(t_scene scene, t_hit hit);
t_color	ambient_pixel(t_scene scene);

// Render
void	translate_horizontal(t_scene *scene, double step);
void	translate_vertical(t_scene *scene, double step);
void	translate_forward(t_scene *scene, double step);
// t_vec3	rotate_x(t_vec3 direction, double angle);
// t_vec3	rotate_z(t_vec3 direction, double angle);
void	rotate_camera(t_scene *scene, double pitch, double yaw);
void	key_hook(mlx_key_data_t keydata, void *param);
void	mouse_hook(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param);
void	hook_setup(mlx_t *mlx, mlx_keyfunc key_hook,
			mlx_mousefunc mouse_hook, void *param);
void	draw_img(t_scene *scene);
bool	render(t_scene *scene, t_gc_object **gc_list);

// GC
void	*gc_alloc(size_t size, t_gc_object **gc_list);
void	gc_mark(void *ptr, t_gc_object *gc_list);
void	gc_free(t_gc_object *gc_list);
char	**gc_split(const char *s, char c,
			t_gc_object **gc_list);

// debugging
void	print_object(t_object *obj);
void	print_camera(t_camera *cam);
void	print_ambient(t_amb_light *amb);
void	print_light(t_light *light);

#endif
