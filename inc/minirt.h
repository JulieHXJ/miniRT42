/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:57:47 by junjun            #+#    #+#             */
/*   Updated: 2025/07/07 13:02:12 by dchrysov         ###   ########.fr       */
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
void	add_object(t_scene **scene, t_object **new_obj);
float	ft_atod(const char *str);
float	frand(void);

// Check
bool	in_range_int(int value, int min, int max);
bool	in_range_float(float value, float min, float max);
bool	valid_color(t_color color);
bool	valid_ratio(float ratio);

// Parser
bool	assign_positive_num(char *num, float *value);

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



#endif
