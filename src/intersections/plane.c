/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:37:26 by junjun            #+#    #+#             */
/*   Updated: 2025/05/25 21:28:27 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"

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
	numer = vec_dot(oa, plane.normal); // dot(O - A, N)
	// dot(D, N)
	denom = vec_dot(ray.direction, plane.normal);
	// Ray is parallel to the plane, no intersection
	if (denom == 0)
	{
		// why using fabs(denom) < 0.0001??
		return (false);
	}
	t = -numer / denom; // Solve for t
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
