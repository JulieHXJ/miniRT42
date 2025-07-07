/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:57:47 by junjun            #+#    #+#             */
/*   Updated: 2025/07/07 15:56:20 by xhuang           ###   ########.fr       */
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
# include "vector.h"
# include "objects.h"
# include "env.h"
# include "gc.h"
# include "../bonus/inc/minirt_bonus.h"

# define MODE "SIMPLE"

# define USAGE_MSG "Usage: ./minirt scenes/<file_name>.rt"
# define HOOK "arrow keys to move, A/D/W/X to rotate, R to reset camera"
# define RED "\033[31m"
# define RST "\033[0m"

# define WIN_WIDTH 1000
# define WIN_HEIGHT 700

# define ORIENT_MIN -1.0
# define ORIENT_MAX 1.0

// Utils
size_t	array_size(char **arr);
void	free_color_buffer(t_color **buffer, int height);
float	ft_atod(const char *str);
float	frand(void);

// Check
bool	in_range_int(int value, int min, int max);
bool	in_range_float(float value, float min, float max);
bool	valid_color(t_color color);
bool	valid_ratio(float ratio);

// Parser
bool	assign_positive_num(char *num, float *value);
bool	create_environment(char *line, t_scene **scene, t_gc_object **gc_list);
bool	create_objects(char *line, t_scene **scene, t_gc_object **gc);
bool	parser(int fd, t_scene **scene, t_gc_object **gc_list);

// Intersections
t_ray	ray_to_vp(t_scene *scene, float x, float y);
float	solve_quadratic(float a, float b, float c);
bool	if_hit(t_scene *scene, t_ray ray, t_hit *hit);

// Render
bool	is_lighted_pixel(t_hit hit, t_light light);
bool	is_in_shadow(t_scene scene, t_hit hit, t_light *light);
t_color	lighted_pixel(t_scene scene, t_hit hit, t_light *light, t_color obj_c);
t_color	checkered_background(uint32_t x, uint32_t y);
t_color	color_pixel(t_scene *scene, uint32_t x, uint32_t y);
t_color	base_color_mode(t_hit *hit);

// Debugging
void	print_vec3(t_vec3 v, char *label);
void	print_camera(t_camera *camera);
void	print_object(t_object *obj);
// void	print_scene_info(t_scene *scene);

#endif
