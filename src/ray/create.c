/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:58:23 by junjun            #+#    #+#             */
/*   Updated: 2025/05/11 13:58:36 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/**
 * @brief Create a new ray with origin and direction
 */
t_ray creat_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray ray;
    
    ray.origin = origin;
    ray.direction = vec_normalize(direction);
    return (ray);
}