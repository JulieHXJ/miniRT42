/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:16:44 by junjun            #+#    #+#             */
/*   Updated: 2025/06/17 19:04:42 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Set up the viewport based on the camera parameters
 * @note The viewport is the scene that the camera can see.
 * Rays will be shoot through each pixel of the viewport.
 */
void	set_viewport(t_viewport *vp, t_camera *camera)
{
	t_vec3	world_up;
	t_vec3	screen_center;
	t_vec3	half_width;
	t_vec3	half_height;

	world_up = new_vector(0, 1, 0);
	// Choose a proper world_up that isn't parallel to the camera direction
	if (fabs(vec_dot(camera->direction, world_up)) > 0.999)
		world_up = new_vector(0, 0, 1);
	vp->fov = camera->fov * M_PI / 180.0;
	vp->aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	vp->distance = 1.0;
	vp->view_height = 2.0 * tan(vp->fov / 2.0);
	vp->view_width = vp->aspect_ratio * vp->view_height;
	vp->normal = camera->direction;
	vp->right = vec_normalize(vec_cross(world_up, vp->normal));
	vp->up = vec_normalize(vec_cross(vp->normal, vp->right));
	// Calculate the top-left corner of the viewport
	screen_center = vec_add(camera->origin, vec_scale(camera->direction,
				vp->distance));
	half_width = vec_scale(vp->right, vp->view_width / 2.0);
	half_height = vec_scale(vp->up, vp->view_height / 2.0);
	vp->up_left_corner = vec_sub(vec_add(screen_center, half_height),
			half_width);
}

/**
 * @brief Calculate a point along a ray at distance t
 * @note P(t) = Origin + t × Direction
 */
t_vec3	ray_point_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(ray.direction, t)));
}

/**
 * @brief Generate a ray from the camera through the pixel at (x, y) on viewport
 *
 */
t_ray	ray_to_vp(t_scene *scene, double x, double y)
{
	t_ray		ray;
	t_viewport	*vp;
	t_vec3		pixel_position;
	t_vec3		pixel_x;
	t_vec3		pixel_y;

	vp = &scene->camera.viewport;
	// Calculate step length
	pixel_x = vec_scale(vp->right, (x + 0.5) * vp->view_width / WIN_WIDTH);
	pixel_y = vec_scale(vp->up, -(y + 0.5) * vp->view_height / WIN_HEIGHT);
	// Calculate the pixel position from up left
	pixel_position = vec_add(vec_add(vp->up_left_corner, pixel_x), pixel_y);
	// Create ray from camera origin through viewport point
	ray.origin = scene->camera.origin;
	ray.direction = vec_normalize(vec_sub(pixel_position, ray.origin));
	return (ray);
}

static bool	hit_object(t_object *obj, t_ray ray, t_hit *hit)
{
	if (obj->type == SPHERE)
	{
		if (hit_sphere(ray, obj->data.sphere, hit))
		{
			hit->object = obj;
			return (true);
		}
	}
	else if (obj->type == PLANE)
	{
		if (hit_plane(ray, obj->data.plane, hit))
		{
			hit->object = obj;
			return (true);
		}
	}
	else if (obj->type == CYLINDER)
	{
		if (hit_cylinder(ray, obj->data.cylinder, hit))
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
	t_hit	hit_record;
	bool		hit_obj;

	hit_obj = false;
	hit->t = INFINITY;
	obj = scene->obj;
	while (obj)
	{
		hit_record.t = INFINITY; // Reset hit record for each object
		if (hit_object(obj, ray, &hit_record) && hit_record.t < hit->t)
		{
			*hit = hit_record;
			hit_obj = true;
		}
		obj = obj->next;
	}
	return (hit_obj);
}
