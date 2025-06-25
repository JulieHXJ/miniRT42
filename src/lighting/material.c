/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:04:12 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/25 18:10:28 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// diffuse reflection color calculation regarding roughness
t_color diffuse_color()
{
    
}

// phong reflection model
t_color specular_color()


// reflection
t_color reflect_color(t_color base_color, )
{
    
}
// if (obj->material.reflective > 0)
// {
// 	vec3 reflect_dir = reflect(ray.direction, normal);
// 	t_ray reflect_ray = { hit_point + normal * EPSILON, reflect_dir };
// 	t_color reflected_color = trace_ray(reflect_ray, depth + 1);
// 	final_color += reflected_color * obj->material.reflective;
// }


//refraction
t_color refract_color(t_color base_col, )
// if (obj->material.transparency > 0)
// {
// 	vec3 refract_dir = refract(ray.direction, normal, obj->material.refractive_index);
// 	t_ray refract_ray = { hit_point - normal * EPSILON, refract_dir };
// 	t_color refracted_color = trace_ray(refract_ray, depth + 1);
// 	final_color += refracted_color * obj->material.transparency;
// }
