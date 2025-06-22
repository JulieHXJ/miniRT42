/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:37:22 by junjun            #+#    #+#             */
/*   Updated: 2025/06/20 16:58:10 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/** 1. standard formula for infinite cylinder:
|(P(t) - C) - proj_V(P(t) - C)|² = r²
(point to the cylinder axis equals to the radius.)
Get values of t:
p(t) = O + t * D
Let: X = O - C (vector from cylinder base to ray origin)
a = dot(D - dot(D, V) * V, D - dot(D, V) * V)
b = 2 * dot(D - dot(D, V) * V, X - dot(X, V) * V)
c = dot(X - dot(X, V) * V, X - dot(X, V) * V) - r²
a*t² + b*t + c = 0
2. limit the height:
height = dot(P - C, V)
height < 0 || height > cylinder.height*/

/**
 * @brief Project a point onto an axis
 */
// static t_vec3	proj_on_axis(t_vec3 point, t_vec3 axis)
// {
// 	return (vec_scale(axis, vec_dot(point, axis)));
// }

static double	get_t_side(t_vec3 x, t_vec3 v, t_cylinder cylinder)
{
	t_vec3	d_perp;
	t_vec3	x_perp;
	double	a;
	double	b;
	double	c;

	// Project x onto the cylinder axis
	d_perp = vec_sub(x, vec_scale(v, vec_dot(x, v)));
	// Project ray direction onto the cylinder axis
	x_perp = vec_sub(v, vec_scale(cylinder.direction, vec_dot(v,
					cylinder.direction)));
	a = vec_dot(d_perp, d_perp);
	b = 2.0 * vec_dot(d_perp, x_perp);
	c = vec_dot(x_perp, x_perp) - cylinder.radius * cylinder.radius;
	return (solve_quadratic(a, b, c));
}

void	update_cy_hit(t_hit *hit, t_cylinder cylinder, t_vec3 point,
		t_vec3 normal)
{
	hit->point = point;
	hit->normal = vec_normalize(normal);
	hit->color = cylinder.color;
	hit->specular = cylinder.specular;
	hit->reflective = cylinder.reflective;
}

bool	hit_sides(t_ray ray, t_cylinder cylinder, t_hit *hit)
{
	t_vec3	x;
	double	t;
	t_vec3	point;
	t_vec3	normal;

	x = vec_sub(ray.origin, cylinder.center);
	t = get_t_side(x, ray.direction, cylinder);
	if (t < 0.0 || t > hit->t)
		return (false);
	point = ray_point_at(ray, t);
	// Check if the point is within the cylinder's height
	if (!check_height(point, cylinder))
		return (false);
	normal = vec_sub(point, cylinder.bottom_center);
	normal = vec_sub(normal, vec_scale(cylinder.direction, vec_dot(normal,
					cylinder.direction)));
	update_cy_hit(hit, cylinder, point, normal);
	hit->t = t;
	return (true);
}

/**
 * if the point to cap center is less than the radius, hit
 */
static bool	check_cap(t_ray ray, t_cylinder cylinder, t_vec3 center,
		double *t_out)
{
	t_vec3	dir;
	t_vec3	point;
	double	r;
	double	denom;
	double	t;

	dir = cylinder.direction;
	r = cylinder.radius;
	denom = vec_dot(ray.direction, dir);
	if (fabs(denom) < 1e-6)
		return (false);
	t = vec_dot(vec_sub(center, ray.origin), dir) / denom;
	if (t < 0)
		return (false);
	point = ray_point_at(ray, t);
	if (vec_length(vec_sub(point, center)) > r)
		return (false);
	*t_out = t;
	return (true);
}

/**
 * @brief Check if the ray hits the cylinder caps (top and bottom)
 * @note if both caps are hitten, the one with the smaller t will be returned.
 */
bool	hit_caps(t_ray ray, t_cylinder cylinder, t_hit *hit)
{
	t_hit	hit_record;
	bool	hit_any;

	hit_any = false;
	hit_record.t = hit->t;
	if (check_cap(ray, cylinder, cylinder.bottom_center, &hit_record.t)
		&& hit_record.t < hit->t)
	{
		update_cy_hit(hit, cylinder, ray_point_at(ray, hit_record.t),
			vec_scale(cylinder.direction, -1));
		hit->t = hit_record.t;
		hit_any = true;
	}
	hit_record.t = hit->t;
	if (check_cap(ray, cylinder, cylinder.top_center, &hit_record.t)
		&& hit_record.t < hit->t)
	{
		update_cy_hit(hit, cylinder, ray_point_at(ray, hit_record.t),
			cylinder.direction);
		hit->t = hit_record.t;
		hit_any = true;
	}
	return (hit_any);
}
