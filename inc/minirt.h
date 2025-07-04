/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:57:47 by junjun            #+#    #+#             */
/*   Updated: 2025/07/04 14:11:14 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

# include "../lib/getnextline/inc/get_next_line.h"
# include "../lib/libft/inc/libft.h"
# include "intersect.h"
# include "material.h"
# include "vector.h"
# include "../bonus/inc/minirt_bonus.h"

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

/* ************************************************************************** */
/* FUNCTION PROTOTYPES                                                        */
/* ************************************************************************** */

// Utils
void	free_array(char ***arr);
size_t	array_size(char **arr);
void	print_error(char *str, t_gc_object *gc_list);
float	ft_atod(const char *str);
float	frand(void);
void	connect_nodes(t_scene **scene, t_object **new_obj);

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
t_color	color_pixel(t_scene *scene, uint32_t x, uint32_t y);

// Render
void translate_horizontal(t_scene *scene, float step);
void translate_vertical(t_scene *scene, float step);
void rotate_camera(t_scene *scene, float pitch, float yaw);
void zooming(double xdelta, double ydelta, void *param);
void key_hook(mlx_key_data_t keydata, void *param);
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
