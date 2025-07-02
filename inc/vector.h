/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:37:03 by junjun            #+#    #+#             */
/*   Updated: 2025/07/02 13:14:12 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <stdint.h>
# include <stdio.h>

/**
 * @brief structure for vectors and points
 * @note used for 3d points, direction vectors, color values and normal vectors
 */
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}			t_vec3;

typedef struct s_color
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
}			t_color;

// vector functions
t_vec3		new_vector(float x, float y, float z);
t_vec3		vec_add(t_vec3 a, t_vec3 b);
t_vec3		vec_sub(t_vec3 a, t_vec3 b);
t_vec3		vec_scale(t_vec3 v, float s);
float		vec_dot(t_vec3 a, t_vec3 b);
t_vec3		vec_cross(t_vec3 a, t_vec3 b);
float		vec_length(t_vec3 v);
t_vec3		vec_normal(t_vec3 v);
t_vec3		vec3_reflect(t_vec3 v, t_vec3 normal);

// color functions
t_color		color_scale(t_color c, float factor);
t_color		color_add(t_color c1, t_color c2);
t_color		color_mult(t_color c1, t_color c2);
uint32_t	convert_color(t_color color);
t_color		clamp_color(t_color c);

#endif