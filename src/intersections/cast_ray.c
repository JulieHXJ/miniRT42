/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:16:44 by junjun            #+#    #+#             */
/*   Updated: 2025/06/13 11:09:41 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void set_viewport(t_viewport *vp, t_camera *camera)
{
    t_vec3 world_up;
    
    world_up = new_vector(0, 1, 0);
    // Choose a proper world_up that isn't parallel to the camera direction
    if (fabs(vec_dot(camera->direction, world_up)) > 0.999)
        world_up = new_vector(0, 0, 1);
    

    vp->fov = camera->fov * M_PI / 180.0;
    vp->aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
    vp->distance = 1.0;
    vp->view_height = 2.0 * tan(vp->fov / 2.0);
    vp->view_width = vp->aspect_ratio * vp->view_height;
    // Compute screen axes
    vp->normal = camera->direction;
    vp->right = vec_normalize(vec_cross(world_up, vp->normal)); // right-hand rule
    vp->up = vec_normalize(vec_cross(vp->normal, vp->right)); // corrected up
    
    
    // Calculate the top-left corner of the viewport
	t_vec3	screen_center = vec_add(camera->origin, vec_scale(camera->direction, vp->distance));
	t_vec3 half_width = vec_scale(vp->right, vp->view_width / 2.0);
	t_vec3 half_height = vec_scale(vp->up, vp->view_height / 2.0);
	vp->up_left_corner = vec_sub(vec_add(screen_center, half_height), half_width);

}


t_ray	create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vec_normalize(direction);
	return (ray);
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
 * @brief Generate a ray from the camera through the pixel at (x, y)
 * 
 */
t_ray	shoot_ray(t_scene *scene, double x, double y)
{
	t_ray		ray;
	t_viewport	*vp;
	double		pixel_x;
	double		pixel_y;

	vp = &scene->camera.viewport;
	// Calculate steps
	pixel_x = (x + 0.5) / WIN_WIDTH * vp->view_width - vp->view_width / 2.0;
	pixel_y = (y + 0.5) / WIN_HEIGHT * vp->view_height - vp->view_height / 2.0;

	vp->pixel_delta_x = vec_scale(vp->right, vp->view_width / WIN_WIDTH);
	vp->pixel_delta_y = vec_scale(vp->up, -vp->view_height / WIN_HEIGHT); // 负方向！
	
	// Create ray from camera origin through viewport point
	ray.origin = scene->camera.origin;
	ray.direction = vec_add(vp->up_left_corner, vec_add(vec_scale(vp->right, u), vec_scale(vp->up, -v)));
	ray.direction = vec_normalize(ray.direction); // Normalize the direction vector
	return (ray);
}



/**
 * @brief Cast a ray through the scene and check for intersections with objects
 * @return true if any object was hit, false otherwise
 *
 */
bool	if_hit(t_scene *scene, t_ray ray, t_hit *hit)
{
	t_object	*obj;
	bool		hits;

	hit->t = INFINITY; // Initialize hit distance to infinity
	hit->object = NULL;
	obj = scene->obj; // Start with the first object in the scene
	hits = false;
	while (obj)
	{
		if (obj->type == SPHERE)
		{
			if (hit_sphere(ray, obj->data.sphere, hit))
			{
				printf("HIT sphere at distance t = %.6f\n", hit->t);
				hits = true;
				hit->object = obj; // Store the object that was hit
			}
		}
		else if (obj->type == PLANE)
		{
			if (hit_plane(ray, obj->data.plane, hit))
			{
				printf("HIT plane at distance t = %.6f\n", hit->t);
				hits = true;
				hit->object = obj;
			}
		}
		else if (obj->type == CYLINDER)
		{
			if (hit_cylinder(ray, obj->data.cylinder, hit))
			{
				printf("HIT cylinder at distance t = %.6f\n", hit->t);
				hits = true;
				hit->object = obj;
			}
		}
		obj = obj->next;
	}
	return (hits);
}




