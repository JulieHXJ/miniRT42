/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:23:00 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/12 12:23:23 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_vec3(const char *name, t_vec3 v)
{
	printf("%s: (%.2f, %.2f, %.2f)\n", name, v.x, v.y, v.z);
}

void	print_color(const char *name, t_color c)
{
	printf("%s: (%d, %d, %d)\n", name, c.r, c.g, c.b);
}

void	print_camera(t_camera *cam)
{
	printf("== Camera ==\n");
	print_vec3("Origin", cam->origin);
	print_vec3("Direction", cam->direction);
	printf("FOV: %.2f\n", cam->fov);
	printf("Viewport: %d x %d\n", cam->viewpoint_width, cam->viewpoint_height);
	print_vec3("Screen Up", cam->screen_up);
	print_vec3("Screen Right", cam->screen_right);
}

void	print_ambient(t_amb_light *amb)
{
	printf("== Ambient Light ==\n");
	printf("Ratio: %.2f\n", amb->ratio);
	print_color("Color", amb->color);
}

void	print_light(t_light *light)
{
	if (!light)
	{
		printf("== Light ==\nNone\n");
		return ;
	}
	printf("== Light ==\n");
	print_vec3("Position", light->position);
	printf("Ratio: %.2f\n", light->ratio);
	print_color("Color", light->color);
}

void	print_sphere(t_sphere *sp)
{
	printf("  - Sphere\n");
	print_vec3("Center", sp->center);
	printf("Diameter: %.2f\n", sp->diam);
	print_color("Color", sp->color);
	printf("Specular: %.2f | Reflective: %.2f\n", sp->specular, sp->reflective);
}

void	print_plane(t_plane *pl)
{
	printf("  - Plane\n");
	print_vec3("Point", pl->point);
	print_vec3("Normal", pl->normal);
	print_color("Color", pl->color);
	printf("Specular: %.2f | Reflective: %.2f\n", pl->specular, pl->reflective);
}
void	print_cylinder(t_cylinder *cy)
{
	printf("  - Cylinder\n");
	print_vec3("Center", cy->center);
	print_vec3("Direction", cy->direction);
	printf("Diameter: %.2f | Height: %.2f\n", cy->diam, cy->height);
	print_color("Color", cy->color);
	printf("Specular: %.2f | Reflective: %.2f\n", cy->specular, cy->reflective);
}
void	print_object(t_object *obj)
{
	int	count;

	count = 1;
	while (obj)
	{
		printf("== Object #%d ==\n", count++);
		if (obj->type == SPHERE)
			print_sphere(&obj->data.sphere);
		else if (obj->type == PLANE)
			print_plane(&obj->data.plane);
		else if (obj->type == CYLINDER)
			print_cylinder(&obj->data.cylinder);
		else
			printf("  - Unknown object type\n");
		obj = obj->next;
	}
}
