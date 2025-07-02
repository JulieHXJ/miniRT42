/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:23:00 by xhuang            #+#    #+#             */
/*   Updated: 2025/07/02 13:12:34 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

static void	print_vec3(t_vec3 v, char *label)
{
	printf("%s: (%.2f, %.2f, %.2f)\n", label, v.x, v.y, v.z);
}

static void	print_color(t_color c, char *label)
{
	printf("%s: (%d, %d, %d)\n", label, c.r, c.g, c.b);
}

static void	print_camera(t_camera *camera)
{
	printf("\n[Camera]\n");
	printf("Camera Origin: ");
	print_vec3(camera->origin, "Origin");
	printf("Camera Direction: ");
	print_vec3(camera->direction, "Direction");
	printf("FOV: %.2f\n", camera->fov);
	printf("Camera Count: %d\n", camera->cam_num);
}

static void	print_object(t_object *obj)
{
	if (obj->type == SPHERE)
	{
		printf("Type: Sphere\n");
		print_vec3(obj->u_data.sphere.center, "Center");
		printf("Diameter: %.2f\n", obj->u_data.sphere.diam);
	}
	else if (obj->type == PLANE)
	{
		printf("Type: Plane\n");
		print_vec3(obj->u_data.plane.point, "Point");
		print_vec3(obj->u_data.plane.normal, "Normal");
	}
	else if (obj->type == CYLINDER)
	{
		printf("Type: Cylinder\n");
		print_vec3(obj->u_data.cylinder.center, "Center");
		print_vec3(obj->u_data.cylinder.direction, "Direction");
		printf("Radius: %.2f\n", obj->u_data.cylinder.radius);
		printf("Height: %.2f\n", obj->u_data.cylinder.height);
	}
	print_color(obj->color, "Color");
}

void	print_scene_info(t_scene *scene)
{
	t_object	*obj;
	int			i;

	print_camera(&scene->camera);
	printf("\n[Ambient Light]\n");
	printf("Ratio: %.2f\n", scene->amb_light.ratio);
	print_color(scene->amb_light.color, "Color");
	printf("Ambient Count: %d\n", scene->amb_light.amb_num);
	if (scene->light)
	{
		printf("\n[Light]\n");
		print_vec3(scene->light->position, "Position");
		printf("Ratio: %.2f\n", scene->light->ratio);
		print_color(scene->light->color, "Color");
	}
	else
		printf("\n[Light] None\n");
	obj = scene->obj;
	i = 0;
	while (obj)
	{
		printf("\n[Object #%d]\n", ++i);
		print_object(obj);
		obj = obj->next;
	}
}
