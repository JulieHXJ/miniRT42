/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 22:42:17 by junjun            #+#    #+#             */
/*   Updated: 2025/06/25 15:06:05 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "vector.h"
# include <stdbool.h>

// Forward declaration of t_object
typedef struct s_object	t_object;

typedef struct s_viewport
{
	double				fov;
	double				aspect_ratio;
	double				view_width;
	double				view_height;
	t_vec3				up;
	t_vec3				right;
	t_vec3				normal;
	t_vec3				up_left_corner;

}						t_viewport;

typedef struct s_ray
{
	t_vec3				origin;
	t_vec3				direction;
}						t_ray;

// we call the visible interscet point a "hit"
typedef struct s_hit
{
	double t;         // Distance from camera to hit point
	t_vec3 point;     // closest hit point
	t_vec3 normal;    // Surface normal at intersection
	t_object *object; // Pointer to the hit object
	// t_color	color;			// -------> Why since there already is a pointer to the object?
}			t_hit;


t_vec3					ray_point_at(t_ray ray, double t);
#endif