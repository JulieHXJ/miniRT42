/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:41:34 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/04 15:11:41 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	sphere_uv(t_vec3 point, float *u, float *v)
{
	float theta = acos(-point.y);
	float phi = atan2(-point.z, point.x) + M_PI;
	*u = phi / (2.0 * M_PI);   // Range [0,1]
	*v = theta / M_PI;         // Range [0,1]
}

static t_color	sample_texture(t_texture *tex)
{
	uint32_t	x = (uint32_t)(tex->uv.u * (tex->png->width - 1));
	uint32_t	y = (uint32_t)(tex->uv.v * (tex->png->height - 1));
	uint8_t		*pixel;

	pixel = &tex->png->pixels[(y * tex->png->width + x) * tex->png->bytes_per_pixel];

	return (t_color){
		.r = pixel[0],
		.g = pixel[1],
		.b = pixel[2]
	};
}

t_color	texture_object(t_hit *hit)
{
	t_sphere	sphere;
	t_vec3		p;

	sphere = hit->object->u_data.sphere;
	if (!hit->object->tex.png)
		return ((t_color){255, 0, 255});
	hit->object->tex.uv.u = 0;
	hit->object->tex.uv.v = 0;
	if (hit->object->type == SPHERE) {
		p = vec_scale(vec_sub(hit->point, sphere.center), 2.0f / sphere.diam);
		sphere_uv(p, &hit->object->tex.uv.u, &hit->object->tex.uv.v);
	}
	hit->object->tex.uv.u = fmodf(fmodf(hit->object->tex.uv.u, 1.0f) + 1.0f, 1.0f);
	hit->object->tex.uv.v = fmodf(fmodf(hit->object->tex.uv.v, 1.0f) + 1.0f, 1.0f);
	return (sample_texture(&hit->object->tex));
}
