/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:10:44 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/22 16:13:57 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool in_shadow(t_scene *scene, t_light *light, t_vec3 point)
{
    
}

t_color calculate_lighting(t_scene *scene, t_hit *hit)
{

	// t_vec3	light_dir = vec_normalize(vec_sub(scene->light->position, hit->point));
	// double	diffuse = fmax(vec_dot(hit->normal, light_dir), 0.0);
	// return color_scale(hit->color, diffuse);
}
