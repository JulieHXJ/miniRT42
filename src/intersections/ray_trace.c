/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:16:44 by junjun            #+#    #+#             */
/*   Updated: 2025/07/01 14:59:54 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Calculate a point along a ray at distance t
 * @note P(t) = Origin + t × Direction
 */
t_vec3	ray_point_at(t_ray ray, float t)
{
	return (vec_add(ray.origin, vec_scale(ray.direction, t)));
}

/**
 * @brief Generate a ray from the camera to each pixel (x, y) on viewport
 * @note step length u and v 
 */
t_ray	ray_to_vp(t_scene *scene, float x, float y)
{
	t_ray		ray;
	t_viewport	*vp;
	t_vec3		pixel_position;
	t_vec3		pixel_x;
	t_vec3		pixel_y;

	vp = &scene->camera.viewport;
	pixel_x = vec_scale(vp->right, (x + 0.5) * vp->view_width / WIN_WIDTH);
	pixel_y = vec_scale(vp->up, -(y + 0.5) * vp->view_height / WIN_HEIGHT);
	pixel_position = vec_add(vec_add(vp->up_left_corner, pixel_x), pixel_y);
	ray.origin = scene->camera.origin;
	ray.direction = vec_normal(vec_sub(pixel_position, ray.origin));
	return (ray);
}

bool	hit_object(t_object *obj, t_ray ray, t_hit *hit)
{
	if (obj->type == SPHERE)
	{
		if (hit_sphere(ray, (*obj).u_data.sphere, hit))
		{
			hit->object = obj;
			return (true);
		}
	}
	else if (obj->type == PLANE)
	{
		if (hit_plane(ray, (*obj).u_data.plane, hit))
		{
			hit->object = obj;
			return (true);
		}
	}
	else if (obj->type == CYLINDER)
	{
		if (hit_cylinder(ray, (*obj).u_data.cylinder, hit))
		{
			hit->object = obj;
			return (true);
		}
	}
	return (false);
}

/**
 * @brief check if the ray hits any object in the scene
 * @return true if any object was hit, false otherwise
 * @note the interscetion record is stored in the hit struct
 */
bool	if_hit(t_scene *scene, t_ray ray, t_hit *hit)
{
	t_object	*obj;
	t_hit		hit_record;
	bool		result;

	result = false;
	hit->t = INFINITY;
	obj = scene->obj;
	while (obj)
	{
		hit_record.t = INFINITY;
		if (hit_object(obj, ray, &hit_record) && hit_record.t < hit->t)
		{
			*hit = hit_record;
			result = true;
		}
		obj = obj->next;
	}
	return (result);
}

/**
 * @brief Checks if the point of an infinite cylinder lies within the
 * height boundaries of the finite cylinder.
 * 
 * @param point The point in question that belongs to the infinite cylinder.
 * @param cylinder The actual finite cylinder.
 */
bool	check_height(t_vec3 point, t_cylinder cylinder)
{
	t_vec3	axis;
	t_vec3	from_bottom;
	float	proj;

	axis = vec_normal(vec_sub(cylinder.top_center, cylinder.bottom_center));
	from_bottom = vec_sub(point, cylinder.bottom_center);
	proj = vec_dot(from_bottom, axis);
	return (proj >= 0.0 && proj <= cylinder.height);
}
