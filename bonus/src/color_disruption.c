/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_disruption.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:10:44 by xhuang            #+#    #+#             */
/*   Updated: 2025/07/07 12:56:30 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define SIZE_SPHERE 10
#define SIZE_PLANE 0.2
#define SIZE_CYLINDER 10
#define SIZE_CONE 15

static void	get_sphere_uv(t_hit hit, t_sphere sphere, int *i, int *j)
{
	t_vec3	p;
	t_uv	uv;

	p = vec_normal(vec_sub(hit.point, sphere.center));
	uv.u = 0.5 + atan2(p.z, p.x) / (2 * M_PI);
	uv.v = 0.5 - asin(p.y) / M_PI;
	*i = floor(uv.u * SIZE_SPHERE);
	*j = floor(uv.v * SIZE_SPHERE);
}

static void	get_plane_uv(t_hit hit, t_plane plane, int *i, int *j)
{
	t_vec3	u_axis;
	t_vec3	v_axis;
	t_vec3	local;
	t_uv	uv;

	u_axis = vec_normal(vec_cross((t_vec3){0, 1, 0}, plane.normal));
	if (vec_length(u_axis) < 1e-6)
		u_axis = vec_normal((t_vec3){1, 0, 0});
	v_axis = vec_normal(vec_cross(plane.normal, u_axis));
	local = vec_sub(hit.point, plane.point);
	uv.u = vec_dot(local, u_axis);
	uv.v = vec_dot(local, v_axis);
	*i = floor(uv.u * SIZE_PLANE);
	*j = floor(uv.v * SIZE_PLANE);
}

static void	get_cylinder_uv(t_hit hit, t_cylinder cyl, int *i, int *j)
{
	t_vec3	cp;
	float	height_proj;
	t_vec3	radial;
	float	theta;
	t_uv	uv;

	cp = vec_sub(hit.point, cyl.bottom_center);
	height_proj = vec_dot(cp, vec_normal(cyl.direction));
	radial = vec_sub(cp, vec_scale(vec_normal(cyl.direction), height_proj));
	theta = atan2(radial.z, radial.x);
	uv.u = (theta + M_PI) / (2 * M_PI);
	uv.v = height_proj / cyl.height;
	*i = floor(uv.u * SIZE_CYLINDER);
	*j = floor(uv.v * SIZE_CYLINDER);
}

static void	get_cone_uv(t_hit hit, t_cone cone, int *i, int *j)
{
	t_vec3	v;
	float	height_on_axis;
	t_vec3	radial;
	t_uv	uv;

	v = vec_sub(hit.point, cone.apex);
	height_on_axis = vec_dot(v, cone.dir);
	radial = vec_sub(v, vec_scale(cone.dir, height_on_axis));
	if (height_on_axis < 0)
		height_on_axis = 0;
	if (height_on_axis > cone.height)
		height_on_axis = cone.height;
	radial = vec_sub(v, vec_scale(cone.dir, height_on_axis));
	uv.u = atan2(radial.z, radial.x) / (2.0f * M_PI);
	if (uv.u < 0)
		uv.u += 1.0f;
	uv.v = height_on_axis / cone.height;
	*i = floor(uv.u * SIZE_CONE);
	*j = floor(uv.v * SIZE_CONE);
}

t_color	color_disruption(t_hit hit)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (hit.object->type == SPHERE)
		get_sphere_uv(hit, hit.object->u_data.sphere, &i, &j);
	else if (hit.object->type == PLANE)
		get_plane_uv(hit, hit.object->u_data.plane, &i, &j);
	else if (hit.object->type == CYLINDER)
		get_cylinder_uv(hit, hit.object->u_data.cylinder, &i, &j);
	else if (hit.object->type == CONE)
		get_cone_uv(hit, hit.object->u_data.cone, &i, &j);
	if ((i + j) % 2 == 0)
		return (hit.object->color);
	return ((t_color){0, 0, 0});
}
