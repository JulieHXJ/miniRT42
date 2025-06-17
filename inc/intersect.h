/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 22:42:17 by junjun            #+#    #+#             */
/*   Updated: 2025/06/13 10:51:44 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "vector.h"
# include <stdbool.h>


// Forward declaration of t_object
typedef struct s_object t_object;

typedef struct s_viewport
{
    double fov;
    double aspect_ratio;
	double distance; // Distance from camera to viewport
    int view_width;  // Width of the viewport
    int view_height; // Height of the viewport
    t_vec3 up;    // for rotating camera up and down
	t_vec3 right; // for rotating camera left and right
	t_vec3 normal;
	t_vec3 up_left_corner;

}				t_viewport;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}			t_ray;

// we call the visible interscet point a "hit"
typedef struct s_hit
{
	double t;         // Distance from camera to hit point
	t_vec3 point;     // closest hit point
	t_vec3 normal;    // Surface normal at intersection
	t_object *object; // Pointer to the hit object

	t_color	color;
	double specular;   // For bonus specular lighting
	double reflective; // For bonus reflections

}			t_hit;


t_vec3 ray_point_at(t_ray ray, double t);
t_ray create_ray(t_vec3 origin, t_vec3 direction);
#endif