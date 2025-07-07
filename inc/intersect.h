/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 22:42:17 by junjun            #+#    #+#             */
/*   Updated: 2025/07/07 15:50:19 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include <stdbool.h>

# include "objects.h"
# include "vector.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}			t_ray;

typedef struct s_hit
{
	float		t;
	t_vec3		point;
	t_vec3		normal;
	t_object	*object;
}				t_hit;

t_vec3	ray_point_at(t_ray ray, float t);
bool	check_height(t_vec3 point, t_cylinder cylinder);
float	solve_quadratic(float a, float b, float c);
bool	hit_sphere(t_ray ray, t_sphere sphere, t_hit *hit);
bool	hit_plane(t_ray ray, t_plane plane, t_hit *hit);
bool	hit_cylinder(t_ray ray, t_cylinder cylinder, t_hit *hit);
bool	hit_object(t_object *obj, t_ray ray, t_hit *hit);

#endif