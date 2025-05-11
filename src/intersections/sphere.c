/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:33:01 by junjun            #+#    #+#             */
/*   Updated: 2025/05/11 17:48:55 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Check if a ray intersects with a sphere
 */
int hit_sphere(t_ray ray, t_sphere sphere, t_hit *hit)
{
	
	t_vec3 oc;//from center to origin
	double a, b, c, discriminant, t, t0, t1;
	
	// a = dot(D, D)
	// b = 2 * dot(D, O - C)
	// c = dot(O - C, O - C) - r²
	// t = (-b ± sqrt(b² - 4ac)) / (2a)

	// If Δ < 0 → no intersection
	// If Δ == 0 → tangential hit (1 point)
	// If Δ > 0 → 2 intersections (we pick the closest t > 1)

}
