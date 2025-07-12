/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:37:22 by junjun            #+#    #+#             */
/*   Updated: 2025/07/11 19:07:46 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Calculates the potential intersection between the ray and an infinite
 * cylinder.
 * @param x_perp The component of the ray origin, perpendicular to
 * the cylinder's axis.
 * @param d_perp The component of the ray direction, perpendicular to
 * the cylinder's axis.
 * @returns The distance where the ray intersects the infinite cylinder.
 */
static float	get_t_side(t_vec3 x, t_vec3 ray_dir, t_cylinder cylinder)
{
	t_vec3	d_perp;
	t_vec3	x_perp;
	float	a;
	float	b;
	float	c;

	d_perp = vec_sub(ray_dir, vec_scale(cylinder.direction, vec_dot(ray_dir,
					cylinder.direction)));
	x_perp = vec_sub(x, vec_scale(cylinder.direction, vec_dot(x,
					cylinder.direction)));
	a = vec_dot(d_perp, d_perp);
	b = 2.0 * vec_dot(d_perp, x_perp);
	c = vec_dot(x_perp, x_perp) - pow(cylinder.radius, 2);
	return (solve_quadratic(a, b, c));
}

static void	update_hit(t_hit *hit, float t, t_vec3 point, t_vec3 normal)
{
	hit->t = t;
	hit->point = point;
	hit->normal = vec_normal(normal);
}

static bool	check_sides(t_ray ray, t_cylinder cylinder, t_hit *hit)
{
	float	t;
	t_vec3	point;
	t_vec3	normal;
	t_vec3	axis_to_point;
	float	projection_length;

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
	update_hit(hit, t, point, normal);
	return (true);
}

static bool	check_cap(t_ray ray, t_cylinder cylinder, t_vec3 center,
		float *t_out)
{
	t_vec3	point;
	float	denom;
	float	t;

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

/**
 * @brief Checks if the ray hits the cylinder and if so updates the hit struct.
 */
bool	hit_cylinder(t_ray ray, t_cylinder cylinder, t_hit *hit)
{
	t_hit	hit_side;
	float t_cap;
	bool has_hit = false;

	hit_side.t = hit->t;
	if (check_sides(ray, cylinder, &hit_side) && hit_side.t < hit->t)
	{
		*hit = hit_side;
		has_hit = true;
	}
	if (check_cap(ray, cylinder, cylinder.bottom_center, &t_cap)
		&& t_cap < hit->t && t_cap > 0)
	{
		update_hit(hit, t_cap, ray_point_at(ray, t_cap),
			vec_scale(cylinder.direction, -1));
		has_hit = true;
	}
	if (check_cap(ray, cylinder, cylinder.top_center, &t_cap) && t_cap < hit->t
		&& t_cap > 0)
	{
		update_hit(hit, t_cap, ray_point_at(ray, t_cap), cylinder.direction);
		has_hit = true;
	}
	return (has_hit);
}
