/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:41:34 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/04 15:11:41 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt_bonus.h"
#include "minirt.h"

bool	create_cone(int id, t_scene **scn, char **arr, t_gc_object **gc)
{
	t_object	*new_obj;

	if (array_size(arr) < 6)
		return (print_error("Cone requires 6 basic parameters", *gc),
			false);
	new_obj = gc_alloc(sizeof(t_object), gc);
	if (!new_obj)
		return (print_error("Allocation failed for cone", *gc), false);
	new_obj->type = CONE;
	new_obj->id = id;
	if (!assign_vector(arr[1], &new_obj->u_data.cone.apex, gc))
		return (print_error("Cylinder apex parse failed", *gc), false);
	if (!assign_normal(arr[2], &new_obj->u_data.cone.orient, gc))
		return (print_error("Cone orientation parse failed", *gc), false);
	if (!assign_positive_num(arr[3], &new_obj->u_data.cone.diam)
		|| !assign_positive_num(arr[4], &new_obj->u_data.cone.height))
		return (print_error("Negative number detected", *gc), false);
	if (!assign_color(arr[5], &new_obj->color, gc))
		return (print_error("Cone color parse failed", *gc), false);
	return (add_object(scn, &new_obj), true);
}

static bool	hit_cone_base(t_ray ray, t_cone cone, t_hit *hit)
{
	t_vec3	base_center;
	float	denom;
	float	t;
	t_vec3	p;

	base_center = vec_add(cone.apex, vec_scale(cone.orient, cone.height));
	denom = vec_dot(ray.direction, cone.orient);
	if (fabsf(denom) < 1e-6f)
		return (false);
	t = vec_dot(vec_sub(base_center, ray.origin), cone.orient) / denom;
	if (t <= 0.0f)
		return (false);
	p = vec_add(ray.origin, vec_scale(ray.direction, t));
	if (vec_length(vec_sub(p, base_center)) > cone.diam / 2.0f)
		return (false);
	hit->t = t;
	hit->point = p;
	if (denom > 0)
		hit->normal = vec_scale(cone.orient, -1);
	else
		hit->normal = vec_scale(cone.orient, 1);
	return (true);
}

static void	cone_side_calc(t_ray ray, t_cone cone, float *a, float *b, float *c)
{
	float	k;
	float	dv;
	t_vec3	co;
	t_vec3	a_proj;
	t_vec3	b_proj;

	k = cone.diam / (2.0f * cone.height);
	dv = vec_dot(ray.direction, cone.orient);
	co = vec_sub(ray.origin, cone.apex);
	a_proj = vec_sub(ray.direction, vec_scale(cone.orient, dv));
	b_proj = vec_sub(co, vec_scale(cone.orient, vec_dot(co, cone.orient)));
	*a = vec_dot(a_proj, a_proj) - powf(k, 2.0f) * powf(dv, 2.0f);
	*b = 2.0f * (vec_dot(a_proj, b_proj) - powf(k, 2.0f)
			* dv * vec_dot(co, cone.orient));
	*c = vec_dot(b_proj, b_proj) - powf(k, 2.0f)
		* pow(vec_dot(co, cone.orient), 2.0f);
}

bool	hit_cone(t_ray ray, t_cone cone, t_hit *hit)
{
	float	a;
	float	b;
	float	c;
	float	t;
	t_vec3	ap;

	cone_side_calc(ray, cone, &a, &b, &c);
	t = solve_quadratic(a, b, c);
	if (t <= 0.0f)
		return (hit_cone_base(ray, cone, hit));
	ap = vec_sub(vec_add(ray.origin, vec_scale(ray.direction, t)), cone.apex);
	if (vec_dot(ap, cone.orient) < 0.0f
		|| vec_dot(ap, cone.orient) > cone.height)
		return (hit_cone_base(ray, cone, hit));
	hit->t = t;
	hit->point = vec_add(ray.origin, vec_scale(ray.direction, t));
	hit->normal = vec_normal(vec_sub(ap, vec_scale(cone.orient, vec_dot(ap,
						cone.orient) * (1 + powf(cone.diam
							/ (2.0f * cone.height), 2.0f)))));
	return (true);
}
