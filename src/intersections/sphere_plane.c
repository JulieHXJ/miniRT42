/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:33:01 by junjun            #+#    #+#             */
/*   Updated: 2025/07/07 12:52:37 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @note Solve the quadratic equation
 * If Δ < 0 → no intersection
 * If Δ == 0 → tangential hit (1 point)
 * If Δ > 0 → 2 intersections (we pick the closest t > 1)
 */
float	solve_quadratic(float a, float b, float c)
{
	float	discriminant;
	float	t0;
	float	t1;
	float	t;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	t0 = (-b - sqrt(discriminant)) / (2.0 * a);
	t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t0 > 0.001)
		t = t0;
	else if (t1 > 0.001)
		t = t1;
	else
		return (-1.0);
	return (t);
}

/**
 * @brief Check if a ray intersects with a sphere
 * @note reserves the hit points and calculate normals
 * Sphere equation: |P - C|² = r²
 * Substituting: |O + t*D - C|² = r²
 * (D·D)*t² + 2*(oc·D)*t + (oc·oc - r²) = 0
 * a = dot(D, D)
 * b = 2 * dot(D, O - C)
 * c = dot(O - C, O - C) - r²
 * t = (-b ± sqrt(b² - 4ac)) / (2a)
 */
bool	hit_sphere(t_ray ray, t_sphere sphere, t_hit *hit)
{
	float	a;
	float	b;
	float	c;
	float	t;
	t_vec3	oc;

	oc = vec_sub(ray.origin, sphere.center);
	a = vec_dot(ray.direction, ray.direction);
	b = 2.0 * vec_dot(ray.direction, oc);
	c = vec_dot(oc, oc) - (sphere.diam * 0.5) * (sphere.diam * 0.5);
	t = solve_quadratic(a, b, c);
	if (t < 0)
		return (false);
	if (hit)
	{
		hit->t = t;
		hit->point = ray_point_at(ray, t);
		hit->normal = vec_normal(vec_sub(hit->point, sphere.center));
	}
	return (true);
}

/**
 * Plane equation: dot(P - A, N) = 0
 * Where:
 * P = point on plane
 * A = known point on plane
 * N = plane normal (normalized)
 *
 * Ray equation: P(t) = O + t * D
 * Substitute: dot((O + t*D) - A, N) = 0
 * Expand: dot(O - A, N) + t * dot(D, N) = 0
 * Solve for t: t = -dot(O - A, N) / dot(D, N)
 */
bool	hit_plane(t_ray ray, t_plane plane, t_hit *hit)
{
	t_vec3	oa;
	float	denom;
	float	numerator;
	float	t;

	oa = vec_sub(ray.origin, plane.point);
	numerator = vec_dot(oa, plane.normal);
	denom = vec_dot(ray.direction, plane.normal);
	if (fabs(denom) < 0.0001)
		return (false);
	t = -numerator / denom;
	if (t < 0.001 || (hit->t > 0 && hit->t < t))
		return (false);
	hit->t = t;
	hit->point = ray_point_at(ray, t);
	if (denom < 0)
		hit->normal = plane.normal;
	else
		hit->normal = vec_scale(plane.normal, -1);
	return (true);
}
