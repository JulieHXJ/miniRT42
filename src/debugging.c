/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:23:00 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/24 15:51:30 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_vec3(const char *name, t_vec3 v)
{
	printf("%s: (%.2f, %.2f, %.2f)\n", name, v.x, v.y, v.z);
}

static void	print_color(const char *name, t_color c)
{
	printf("%s: (%d, %d, %d)\n", name, c.r, c.g, c.b);
}

static void	print_sphere(t_object obj)
{
	t_sphere	sp;

	sp = obj.u_data.sphere;
	printf("  - Sphere\n");
	printf("id: %d\n", obj.id);
	print_vec3("Center", sp.center);
	printf("Diameter: %.2f\n", sp.diam);
	print_color("Color", obj.color);
	// printf("Specular: %.2f | Reflective: %.2f\n", sp.specular, sp.reflective);
}

static void	print_plane(t_object obj)
{
	t_plane	pl;

	pl = obj.u_data.plane;
	printf("  - Plane\n");
	printf("id: %d\n", obj.id);
	print_vec3("Point", pl.point);
	print_vec3("Normal", pl.normal);
	print_color("Color", obj.color);
	// printf("Specular: %.2f | Reflective: %.2f\n", pl.specular, pl.reflective);
}

static void	print_cylinder(t_object obj)
{
	t_cylinder	cy;

	cy = obj.u_data.cylinder;
	printf("  - Cylinder\n");
	printf("id: %d\n", obj.id);
	print_vec3("Center", cy.center);
	print_vec3("Direction", cy.direction);
	printf("Radius: %.2f | Height: %.2f\n", cy.radius, cy.height);
	print_color("Color", obj.color);
	// printf("Specular: %.2f | Reflective: %.2f\n", cy.specular, cy.reflective);
}

void	print_camera(t_camera *cam)
{
	printf("== Camera ==\n");
	print_vec3("Origin", cam->origin);
	print_vec3("Direction", cam->direction);
	printf("FOV: %.2f\n", cam->fov);
	// printf("Viewport: %d x %d\n", cam->viewport_width, cam->viewport_height);
	// print_vec3("Screen Up", cam->screen_up);
	// print_vec3("Screen Right", cam->screen_right);
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

void	print_object(t_object *obj)
{
	int	count;

	count = 1;
	while (obj)
	{
		printf("== Object #%d ==\n", count++);
		if (obj->type == SPHERE)
			print_sphere(*obj);
		else if (obj->type == PLANE)
			print_plane(*obj);
		else if (obj->type == CYLINDER)
			print_cylinder(*obj);
		else
			printf("  - Unknown object type\n");
		obj = obj->next;
	}
}
