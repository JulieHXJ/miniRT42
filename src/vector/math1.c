/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:20:00 by junjun            #+#    #+#             */
/*   Updated: 2025/06/22 18:44:00 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	new_vector(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	return (new_vector(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	return (new_vector(a.x - b.x, a.y - b.y, a.z - b.z));
}

/**
 * @brief for vector zooming in and out
 */
t_vec3	vec_scale(t_vec3 v, double s)
{
	return (new_vector(v.x * s, v.y * s, v.z * s));
}
