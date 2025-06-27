/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 22:42:17 by junjun            #+#    #+#             */
/*   Updated: 2025/06/27 13:40:45 by xhuang           ###   ########.fr       */
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
	double				t;
	t_vec3				point;
	t_vec3				normal;
	t_object			*object; //color, specular, reflective included

}						t_hit;

t_vec3					ray_point_at(t_ray ray, double t);
#endif