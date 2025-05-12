/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:22:02 by junjun            #+#    #+#             */
/*   Updated: 2025/05/11 19:00:53 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/**
 * @brief dot product, calculate angle between vectors, used for reflection and lighting
 * @note a · b = ax * bx + ay * by + az * bz
 */
double vec_dot(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/**
 * @brief cross product, calculating normal of two vectors
 */
t_vec3 vec_cross(t_vec3 a, t_vec3 b)
{
    return (new_vector(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x));
}

double vec_length(t_vec3 v)
{
	//|v| = sqrt(v · v)
    return (sqrt(vec_dot(v, v)));
}

/**
 * @brief
 */
t_vec3 vec_normalize(t_vec3 v)
{
    double len;
    
    len = vec_length(v);
	//v / |v|
    if (len > 0)
        return (vec_scale(v, 1.0 / len));
    return (v);
}

t_vec3 vec3_reflect(t_vec3 v, t_vec3 normal)
{
    // R = v - 2(v·n)n
    return (vec_sub(v, vec_scale(normal, 2.0 * vec_dot(v, normal))));
}