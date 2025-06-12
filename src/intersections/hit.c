/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:43:31 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/12 18:31:18 by xhuang           ###   ########.fr       */
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

