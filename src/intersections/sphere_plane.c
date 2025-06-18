/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:33:01 by junjun            #+#    #+#             */
/*   Updated: 2025/06/18 15:24:18 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @note Solve the quadratic equation
 * If Δ < 0 → no intersection
 * If Δ == 0 → tangential hit (1 point)
 * If Δ > 0 → 2 intersections (we pick the closest t > 1)
 */
double	solve_quadratic(double a, double b, double c)
{
	double	discriminant;
	double	t0;
	double	t1;
	double	t;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	t0 = (-b - sqrt(discriminant)) / (2.0 * a);
	t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	// Choose the closest positive intersection
	if (t0 > 0.001)
		t = t0;
	else if (t1 > 0.001)
		t = t1;
	else
		return (printf("Both intersections are behind camera\n"), -1.0);
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
	double	a;
	double	b;
	double	c;
	double	t;

	t_vec3 oc; // from center to origin(camera)
	oc = vec_sub(ray.origin, sphere.center);
	a = vec_dot(ray.direction, ray.direction);
	b = 2.0 * vec_dot(ray.direction, oc);
	c = vec_dot(oc, oc) - (sphere.diam * 0.5) * (sphere.diam * 0.5);
	t = solve_quadratic(a, b, c);
	if (t < 0)
		return (false);
	// Calculate intersection point and normal
	hit->t = t;
	hit->point = ray_point_at(ray, t);
	hit->normal = vec_normalize(vec_sub(hit->point, sphere.center));
	hit->color = sphere.color;
	hit->specular = sphere.specular;
	hit->reflective = sphere.reflective;
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
	double	denom;
	double	numerator;
	double	t;

	oa = vec_sub(ray.origin, plane.point);
	numerator = vec_dot(oa, plane.normal);
	denom = vec_dot(ray.direction, plane.normal);
	// Ray is parallel to the plane, no intersection
	if (fabs(denom) < 0.0001)
		return (false);
	t = -numerator / denom;
	// Check if intersection is behind the ray origin or closer than existing hit
	if (t < 0.001 || (hit->t > 0 && hit->t < t))
		return (false);
	hit->t = t;
	hit->point = ray_point_at(ray, t);
	if (denom < 0)
		hit->normal = plane.normal;
	else
		hit->normal = vec_scale(plane.normal, -1); // Flip normal
	hit->color = plane.color;
	hit->specular = plane.specular;
	hit->reflective = plane.reflective;
	return (true);
}


bool	hit_cylinder(t_ray ray, t_cylinder cylinder, t_hit *hit)
{
	bool	hit_any;
	t_hit	temp_hit;

	hit_any = false;
	temp_hit.t = hit->t;
	if (hit_sides(ray, cylinder, &temp_hit) && temp_hit.t < hit->t)
	{
		*hit = temp_hit;
		hit_any = true;
	}
	temp_hit.t = hit->t;
	if (hit_caps(ray, cylinder, &temp_hit) && temp_hit.t < hit->t)
	{
		*hit = temp_hit;
		hit_any = true;
	}
	return (hit_any);
}
