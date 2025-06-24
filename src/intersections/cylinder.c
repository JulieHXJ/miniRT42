/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:37:22 by junjun            #+#    #+#             */
/*   Updated: 2025/06/24 14:07:15 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Ray-Cylinder Intersection Implementation
 *
 * Standard formula for infinite cylinder:
 * |(P(t) - C) - proj_V(P(t) - C)|² = r²
 * (point to the cylinder axis equals to the radius.)
 *
 * P(t) = O + t * D (ray equation)
 Where:
 * X = O - C (vector from cylinder center to ray origin)
 * D_perp = D - dot(D, V) * V (ray direction perpendicular to cylinder axis)
 * X_perp = X - dot(X, V) * V (displacement perpendicular to cylinder axis)
 * a = dot(D_perp, D_perp)
 * b = 2 * dot(D_perp, X_perp)
 * c = dot(X_perp, X_perp) - r²
 *
2. limit the height:
height = dot(P - C, V)
height < 0 || height > cylinder.height*/

static double	get_t_side(t_vec3 x, t_vec3 ray_dir, t_cylinder cylinder)
{
	t_vec3	d_perp;
	t_vec3	x_perp;
	double	a;
	double	b;
	double	c;

	d_perp = vec_sub(ray_dir, vec_scale(cylinder.direction, vec_dot(ray_dir,
					cylinder.direction)));
	x_perp = vec_sub(x, vec_scale(cylinder.direction, vec_dot(x,
					cylinder.direction)));
	a = vec_dot(d_perp, d_perp);
	b = 2.0 * vec_dot(d_perp, x_perp);
	c = vec_dot(x_perp, x_perp) - cylinder.radius * cylinder.radius;
	return (solve_quadratic(a, b, c));
}

static void	update_cy_hit(t_hit *hit, t_cylinder cylinder, t_vec3 point,
		t_vec3 normal)
{
	hit->point = point;
	hit->normal = vec_normalize(normal);
	hit->color = cylinder.color;
	hit->specular = cylinder.specular;
	hit->reflective = cylinder.reflective;
}

static bool	check_sides(t_ray ray, t_cylinder cylinder, t_hit *hit)
{
	double	t;
	t_vec3	point;
	t_vec3	normal;
	t_vec3	axis_to_point;
	double	projection_length;

	t = get_t_side(vec_sub(ray.origin, cylinder.bottom_center), ray.direction,
			cylinder);
	if (t < 0.0 || t > hit->t)
		return (false);
	point = ray_point_at(ray, t);
	if (!check_height(point, cylinder))
		return (false);
	axis_to_point = vec_sub(point, cylinder.center);
	projection_length = vec_dot(axis_to_point, cylinder.direction);
	normal = vec_sub(point, vec_add(cylinder.center,
				vec_scale(cylinder.direction, projection_length)));
	update_cy_hit(hit, cylinder, point, normal);
	hit->t = t;
	return (true);
}

static bool	check_cap(t_ray ray, t_cylinder cylinder, t_vec3 center,
		double *t_out)
{
	t_vec3	point;
	double	denom;
	double	t;

	denom = vec_dot(ray.direction, cylinder.direction);
	if (fabs(denom) < 1e-6)
		return (false);
	t = vec_dot(vec_sub(center, ray.origin), cylinder.direction) / denom;
	if (t < 0)
		return (false);
	point = ray_point_at(ray, t);
	if (vec_length(vec_sub(point, center)) > cylinder.radius)
		return (false);
	*t_out = t;
	return (true);
}

bool	hit_cylinder(t_ray ray, t_cylinder cylinder, t_hit *hit)
{
	bool	hit_any;
	double	t_bottom;
	double	t_top;
	double	t_min;
	t_hit	hit_side;

	t_min = hit->t;
	hit_any = false;
	hit_side.t = hit->t;
	if (check_sides(ray, cylinder, &hit_side) && hit_side.t < hit->t)
	{
		*hit = hit_side;
		t_min = hit->t;
		hit_any = true;
	}
	if (check_cap(ray, cylinder, cylinder.bottom_center, &t_bottom)
		&& t_bottom < t_min && t_bottom > 0)
	{
		update_cy_hit(hit, cylinder, ray_point_at(ray, t_bottom),
			vec_scale(cylinder.direction, -1));
		hit->t = t_bottom;
		t_min = t_bottom;
		hit_any = true;
	}
	if (check_cap(ray, cylinder, cylinder.top_center, &t_top) && t_top < t_min
		&& t_top > 0)
	{
		update_cy_hit(hit, cylinder, ray_point_at(ray, t_top),
			cylinder.direction);
		hit->t = t_top;
		t_min = t_top;
		hit_any = true;
	}
	return (hit_any);
}
