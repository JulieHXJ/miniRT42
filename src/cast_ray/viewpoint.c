/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewpoint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:29:28 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/12 18:37:15 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void set_viewpoint(t_viewpoint *vp, t_camera *camera)
{
    t_vec3 world_up;
    
    // Choose a proper world_up that isn't parallel to the camera direction
    world_up = new_vector(0, 1, 0); // Default up vector
    if (fabs(vec_dot(camera->direction, world_up)) > 0.999)
        world_up = new_vector(0, 0, 1);
    

    vp->fov = camera->fov * M_PI / 180.0;
    vp->aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
    vp->distance = 1.0;
    vp->view_height = 2.0 * tan(vp->fov / 2.0);
    vp->view_width = vp->aspect_ratio * vp->view_height;
    vp->normal = camera->direction;
    // Compute screen axes
    vp->right = vec_normalize(vec_cross(world_up, vp->normal)); // right-hand rule
    vp->up = vec_normalize(vec_cross(vp->normal, vp->right)); // corrected up
    
    
    // Calculate the top-left corner of the viewport
    vp->up_left_corner = vec_sub(camera->origin, vec_scale(camera->direction, 1.0));//todo

}



t_ray	create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vec_normalize(direction); // Ensure direction is normalized
	return (ray);
}