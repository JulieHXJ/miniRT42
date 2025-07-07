/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:43:51 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/07 15:56:32 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vector.h"
# include "../bonus/inc/texture.h"

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	LIGHT,
	CONE,
}	t_obj_type;

/**
 * @note rgb range: [0, 255]
 */
typedef struct s_sphere
{
	t_vec3	center;
	float	diam;
}			t_sphere;

/**
 * @note normal range: [-1.0, 1.0]
 * @note rgb range: [0, 255]
 */
typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
}			t_plane;

/**
 * @note normal range: [-1.0, 1.0]
 * @note rgb range: [0, 255]
 */
typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	direction;
	float	radius;
	float	height;
	t_vec3	top_center;
	t_vec3	bottom_center;
}			t_cylinder;

typedef struct s_cone
{
	t_vec3	apex;
	t_vec3	dir;
	float	height;
	float	diam;
}			t_cone;

typedef struct s_object
{
	int				id;
	t_obj_type		type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_cone		cone;
	} u_data;
	t_color			color;
	t_texture		tex;
	struct s_object	*next;
}					t_object;

void	get_cylinder_ends(t_cylinder *c);
void	add_object(t_scene **scene, t_object **new_obj);

#endif