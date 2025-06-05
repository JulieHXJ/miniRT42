/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:33:01 by junjun            #+#    #+#             */
/*   Updated: 2025/06/05 16:38:41 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @note Solve the quadratic equation
 * If Δ < 0 → no intersection
 * If Δ == 0 → tangential hit (1 point)
 * If Δ > 0 → 2 intersections (we pick the closest t > 1)
 */
static double	solve_quadratic(double a, double b, double c, double hit_t)
{
	double	discriminant;
	double	t0;
	double	t1;
	double	t;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (printf("No intersection (discriminant < 0)\n"), -1.0);
	t0 = (-b - sqrt(discriminant)) / (2.0 * a);
	t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	// Choose the closest positive intersection
	if (t0 > 0.001)
		t = t0;
	else if (t1 > 0.001)
		t = t1;
	else
		return (printf("Both intersections behind ray origin\n"), -1.0);
	// Check if we already have a closer hit
	if (hit_t > 0 && hit_t < t)
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
	double	a;
	double	b;
	double	c;
	double	t;

	t_vec3 oc; // from center to origin(camera)
	oc = vec_sub(ray.origin, sphere.center);
	a = vec_dot(ray.direction, ray.direction);
	b = 2.0 * vec_dot(ray.direction, oc);
	c = vec_dot(oc, oc) - (sphere.diam / 2.0) * (sphere.diam / 2.0);
	t = solve_quadratic(a, b, c, hit->t);
	if (t < 0)
		return (printf("No valid intersection found\n"), false);
	// Calculate intersection point and normal
	hit->t = t;
	hit->point = ray_point_at(ray, t);
	hit->normal = vec_normalize(vec_sub(hit->point, sphere.center));
	hit->color = sphere.color;
	hit->specular = sphere.specular;
	hit->reflective = sphere.reflective;
	return (true);
}
