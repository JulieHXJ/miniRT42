/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 22:42:17 by junjun            #+#    #+#             */
/*   Updated: 2025/05/28 16:04:48 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "vector.h"
# include "minirt.h"

typedef struct s_object	t_object;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}			t_ray;

typedef struct s_hit
{
	double		t;          // Distance from camera to hit point
	t_vec3		point;      // Intersection point
	t_vec3		normal;     // Surface normal at intersection
	t_object	*obj;
	t_vec3		color;
	double		specular;      // For bonus specular lighting
	double		reflective;    // For bonus reflections

}				t_hit;

t_ray	create_ray(t_vec3 origin, t_vec3 direction);

#endif
