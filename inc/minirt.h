/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:57:47 by junjun            #+#    #+#             */
/*   Updated: 2025/06/05 16:39:43 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/getnextline/inc/get_next_line.h"
# include "../lib/libft/inc/libft.h"
# include "intersect.h"
# include "vector.h"
# include "render.h"
# include "matrix.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

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
}						t_obj_type;

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
 * @note fov range: [0, 180]
 */
typedef struct s_camera
{
	t_vec3				position;
	t_vec3				direction;
	double fov; // Field of view in degrees
	int    width;      // Viewport width
	int    height;     // Viewport height
}						t_camera;

/**
 * @note ratio range: [0.0, 1.0]
 * @note RGB range: [0, 255]
 */
typedef struct s_amb_light
{
	double				ratio;
	t_color				color;
}						t_amb_light;

/**
 * @note brightness range: [0.0, 1.0]
 * @note better to use linked list cuz we will have more lights later
 */
typedef struct s_light
{
	t_vec3				position;
	double				brightness;
	t_color				color;
	struct s_light		*next;
}						t_light;

/* ************************************************************************** */
/* OBJECTS                                                                    */
/* ************************************************************************** */

/**
 * @note rgb range: [0, 255]
 */
typedef struct s_sphere
{
	t_vec3				center;
	t_color				color;
	double				diam;
	// t_matrix			transform; // For bonus transformations
	double specular;   // For bonus specular lighting
	double reflective; // For bonus reflections
}						t_sphere;

/**
 * @note normal range: [-1.0, 1.0]
 * @note rgb range: [0, 255]
 */
typedef struct s_plane
{
	// double		normal[3];
	t_vec3				point;
	t_vec3				normal;
	t_color				color;
	double specular;   // For bonus specular lighting
	double reflective; // For bonus reflections
}						t_plane;

/**
 * @note normal range: [-1.0, 1.0]
 * @note rgb range: [0, 255]
 */
typedef struct s_cylinder
{
	// double		normal[3];
	t_vec3				center;
	t_vec3				direction;
	double				diam;
	double				height;
	t_color				color;
	double specular;   // For bonus specular lighting
	double reflective; // For bonus reflections
}						t_cylinder;

/* ************************************************************************** */
/* Generic object structure                                                   */
/* ************************************************************************** */

typedef struct s_object
{
	t_obj_type			type;
	union
	{
		t_sphere		sphere;
		t_plane			plane;
		t_cylinder		cylinder;
		// more objects
	} data;
	void *content; // added
	struct s_object		*next;
	struct s_object		*previous;
}						t_object;

/* ************************************************************************** */
/* SCENE STRUCTURE                                                            */
/* ************************************************************************** */

typedef struct s_scene
{
	t_camera			camera;
	t_amb_light			amb_light;
	t_light *light; // linked list
	int					light_num;
	t_object			*obj;

	void *mlx;  // MLX pointer
	void *win;  // MLX window pointer
	void *img;  // MLX image pointer
	char *addr; // Image data address
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_scene;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES                                                        */
/* ************************************************************************** */

// Utils
void					free_array(char ***arr);
size_t					array_size(char **arr);
void					print_error(char *str, t_gc_object *gc_list);
double					ft_atod(const char *str);

// Check
bool					valid_file(int ac, char **av);
bool					in_range_int(int value, int min, int max);
bool					in_range_double(double value, double min, double max);
bool					valid_color(t_color color);
bool					valid_ratio(double ratio);
bool					valid_normal(t_vec3 normal);

// Parser
bool					assign_color(char *color, t_color c,
							t_gc_object **gc_list);
bool					assign_vector(char *coordinates, t_vec3 v,
							t_gc_object **gc_list);
bool					assign_normal(char *normal, t_vec3 v,
							t_gc_object **gc_list);
bool					assign_positive_num(char *num, double value);
bool					create_environment(char *line, t_scene **scene,
							t_gc_object **gc_list);
bool					create_objects(char *line, t_scene **scene,
							t_gc_object **gc_list);
bool					parser(char *fname, t_scene **scene,
							t_gc_object **gc_list);

// Intersections
bool	if_hit(t_scene *scene, t_ray ray, t_hit *hit);

// t_vec3					ray_point_at(t_ray ray, double t);
// bool					ray_tracing(t_scene *scene, t_ray ray, t_hit *hit);

// bool hit_sphere(t_ray ray, t_sphere sphere, t_hit *hit);
// bool hit_plane(t_ray ray, t_plane plane, t_hit *hit);
// bool hit_cylinder(t_ray ray, t_cylinder cylinder, t_hit *hit);
// void					rgb_range_check(t_object **obj, char *rgb);
// void					normal_vector_range_check(t_object **obj,
// 							t_obj_type type, char *vec);
// void					center_point_assign(t_object **obj, char *point);

// Functions for color difusion and lighting
// t_ray					create_ray(t_vec3 camera, t_vec3 direction);




//Render
bool					render(t_scene *scene, t_gc_object **gc_list);

// GC
void					*gc_alloc(size_t size, t_gc_object **gc_list);
void					gc_mark(void *ptr, t_gc_object *gc_list);
void					gc_free(t_gc_object *gc_list);
char					**gc_split(const char *s, char c,
							t_gc_object **gc_list);

#endif
