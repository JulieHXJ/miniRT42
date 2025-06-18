/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:37:22 by junjun            #+#    #+#             */
/*   Updated: 2025/06/18 13:22:50 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/** if hit on caps (top or bottom):
Center C of cylinder
Direction V (normalized) of cylinder (points from bottom to top)
Ray: P(t) = O + t * D
Bottom center  Cb = C
Top center  Ct = C + h * V
Radius r
Height h
Solve plane-ray intersection:
dot((P - C_plane), N) = 0
Where:
C_plane = cap center (Cb or Ct)
N = normal (V or -V)
Solve t:
t = -dot(O - C_plane, N) / dot(D, N)

Important:
If	dot(D, N) == 0, the ray is parallel to the cap and doesn't intersect.

Check if the hit point is inside the circle (within radius):
P_hit = O + t * D
Check: length(P_hit - C_plane) <= r
If true → hit is inside the cap ✅
If false → hit is outside ❌ */

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
	// check bottom cap
	if (check_cap(ray, cylinder, cylinder.bottom_center, &hit_record.t))
	{
		hit_record.point = ray_point_at(ray, hit_record.t);
		hit_record.normal = vec_scale(cylinder.direction, -1);
		hit_record.color = cylinder.color;
		hit_record.specular = cylinder.specular;
		hit_record.reflective = cylinder.reflective;
		*hit = hit_record;
		hit_any = true;
	}
	// check top cap
	hit_record.t = hit->t;
	if (check_cap(ray, cylinder, cylinder.top_center, &hit_record.t))
	{
		hit_record.point = ray_point_at(ray, hit_record.t);
		hit_record.normal = cylinder.direction;
		hit_record.color = cylinder.color;
		hit_record.specular = cylinder.specular;
		hit_record.reflective = cylinder.reflective;
		*hit = hit_record;
		hit_any = true;
	}
	return (hit_any);
}

// if hit on curve sides
// Formula: point to the cylinder axis equals to the radius.
// |(P(t) - C) - proj_V(P(t) - C)|² = r²
// Projection:
// Get possible values of t:
// p(t) = O + t * D
// Let: X = O - C (vector from cylinder base to ray origin)
// a = dot(D - dot(D, V) * V, D - dot(D, V) * V)
// b = 2 * dot(D - dot(D, V) * V, X - dot(X, V) * V)
// c = dot(X - dot(X, V) * V, X - dot(X, V) * V) - r²
// a*t² + b*t + c = 0

// projection:
t_vec3	proj_on_axis(t_vec3 point, t_vec3 axis)
{
	return (vec_scale(axis, vec_dot(point, axis)));
}

double	t_side(t_vec3 d_perp, t_vec3 x_perp, double r)
{
	double	a;
	double	b;
	double	c;

	a = vec_dot(d_perp, d_perp);
	b = 2.0 * vec_dot(d_perp, x_perp);
	c = vec_dot(x_perp, x_perp) - r * r;
	return (solve_quadratic(a, b, c));
}

bool	hit_sides(t_ray ray, t_cylinder cylinder, t_hit *hit)
{
	t_vec3	x;
	t_vec3	d_perp;
	t_vec3	x_perp;
	double	t;
	t_vec3	point;

	x = vec_sub(ray.origin, cylinder.center);
	d_perp = vec_sub(ray.direction, proj_on_axis(ray.direction,
				cylinder.direction));
	x_perp = vec_sub(x, proj_on_axis(x, cylinder.direction));
	t = t_side(d_perp, x_perp, cylinder.radius);
	if (t < 0)
		return (false);
	point = ray_point_at(ray, t);
    // Check if the point is within the cylinder's height  
	if (vec_dot(vec_sub(point, cylinder.center), cylinder.direction) < 0.0
		|| vec_dot(vec_sub(point, cylinder.center),
			cylinder.direction) > cylinder.height)
		return (false);
	hit->t = t;
	hit->point = point;
	hit->normal = vec_normalize(vec_sub(vec_sub(point, cylinder.bottom_center),
				proj_on_axis(vec_sub(point, cylinder.bottom_center),
					cylinder.direction)));
	hit->color = cylinder.color;
	hit->specular = cylinder.specular;
	hit->reflective = cylinder.reflective;
	return (true);
}

