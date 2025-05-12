/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:37:03 by junjun            #+#    #+#             */
/*   Updated: 2025/05/11 19:01:10 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

/**
 * @brief structure for vectors and points
 * @note used for 3d points, direction vectors, color values and normal vectors
 */
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

t_vec3	new_vector(double x, double y, double z);
t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_sub(t_vec3 a, t_vec3 b);
t_vec3	vec_scale(t_vec3 v, double s);
double	vec_dot(t_vec3 a, t_vec3 b);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
double	vec_length(t_vec3 v);
t_vec3	vec_normalize(t_vec3 v);
t_vec3  vec3_reflect(t_vec3 v, t_vec3 normal);


t_color	color_init(int r, int g, int b);
t_color	color_scale(t_color c, double factor);
t_color	color_add(t_color c1, t_color c2);

#endif