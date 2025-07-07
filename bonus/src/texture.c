/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:41:34 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/07 12:33:43 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	sphere_uv(t_vec3 point, float *u, float *v)
{
	float	theta;
	float	phi;

	theta = acos(-point.y);
	phi = atan2(-point.z, point.x) + M_PI;
	*u = phi / (2.0 * M_PI);
	*v = theta / M_PI;
}

static t_color	sample_texture(t_texture *tex)
{
	uint32_t		x;
	uint32_t		y;
	uint8_t			*pixel;
	mlx_texture_t	*png;

	x = (uint32_t)(tex->uv.u * (tex->png->width - 1));
	y = (uint32_t)(tex->uv.v * (tex->png->height - 1));
	png = tex->png;
	pixel = &png->pixels[(y * png->width + x) * png->bytes_per_pixel];
	return ((t_color){.r = pixel[0], .g = pixel[1], .b = pixel[2]});
}

t_color	texture_object(t_hit *hit)
{
	t_object	*obj;
	t_sphere	sphere;
	t_vec3		p;

	obj = hit->object;
	sphere = obj->u_data.sphere;
	if (!obj->tex.png)
		return ((t_color){255, 0, 255});
	obj->tex.uv.u = 0;
	obj->tex.uv.v = 0;
	if (obj->type == SPHERE)
	{
		p = vec_scale(vec_sub(hit->point, sphere.center), 2.0f / sphere.diam);
		sphere_uv(p, &obj->tex.uv.u, &obj->tex.uv.v);
	}
	obj->tex.uv.u = fmodf(fmodf(obj->tex.uv.u, 1.0f) + 1.0f, 1.0f);
	obj->tex.uv.v = fmodf(fmodf(obj->tex.uv.v, 1.0f) + 1.0f, 1.0f);
	return (sample_texture(&obj->tex));
}
