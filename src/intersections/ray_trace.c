/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:16:44 by junjun            #+#    #+#             */
/*   Updated: 2025/06/24 16:34:54 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Calculate a point along a ray at distance t
 * @note P(t) = Origin + t × Direction
 */
t_vec3	ray_point_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(ray.direction, t)));
}

/**
 * @brief Generate a ray from the camera to each pixel (x, y) on viewport
 * @note step length u and v 
 */
t_ray	ray_to_vp(t_scene *scene, double x, double y)
{
	t_ray		ray;
	t_viewport	*vp;
	t_vec3		pixel_position;
	t_vec3		pixel_x;
	t_vec3		pixel_y;
	
	vp = &scene->camera.viewport;
	
	// double u;
	// double v;
	// // Normalize pixel coordinates (0.5 prevents aliasing effects)
	// u = (x + 0.5) / (double)scene->img->width;
	// v = (y + 0.5) / (double)scene->img->height;
	// pixel_position = vec_add(vp->up_left_corner, vec_scale(vp->right, u * vp->view_width));
	// pixel_position = vec_sub(pixel_position , vec_scale(vp->up, v * vp->view_height));
	
	pixel_x = vec_scale(vp->right, (x + 0.5) * vp->view_width / WIN_WIDTH);
	pixel_y = vec_scale(vp->up, -(y + 0.5) * vp->view_height / WIN_HEIGHT);
	// Calculate the pixel position from up left
	pixel_position = vec_add(vec_add(vp->up_left_corner, pixel_x), pixel_y);
	
	
	// Create ray from camera origin through viewport point
	ray.origin = scene->camera.origin;
	ray.direction = vec_normal(vec_sub(pixel_position, ray.origin));
	return (ray);
}

static bool	hit_object(t_object *obj, t_ray ray, t_hit *hit)
{
	if (obj->type == SPHERE)
	{
		if (hit_sphere(ray, *obj, hit))
		{
			hit->object = obj;
			return (true);
		}
	}
	else if (obj->type == PLANE)
	{
		if (hit_plane(ray, *obj, hit))
		{
			hit->object = obj;
			return (true);
		}
	}
	else if (obj->type == CYLINDER)
	{
		if (hit_cylinder(ray, *obj, hit))
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
 *
 */
bool	if_hit(t_scene *scene, t_ray ray, t_hit *hit)
{
	t_object	*obj;
	t_hit		hit_record;
	bool		hit_obj;

	hit_obj = false;
	hit->t = INFINITY;
	obj = scene->obj;
	while (obj)
	{
		hit_record.t = INFINITY;
		if (hit_object(obj, ray, &hit_record) && hit_record.t < hit->t)
		{
			*hit = hit_record;
			hit_obj = true;
		}
		obj = obj->next;
	}
	return (hit_obj);
}

bool	check_height(t_vec3 point, t_cylinder cylinder)
{
	t_vec3	axis;
	t_vec3	from_bottom;
	double	proj;

	axis = vec_normal(vec_sub(cylinder.top_center, cylinder.bottom_center));
	from_bottom = vec_sub(point, cylinder.bottom_center);
	proj = vec_dot(from_bottom, axis);
	return (proj >= 0.0 && proj <= cylinder.height);
}
