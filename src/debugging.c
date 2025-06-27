/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:23:00 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/27 14:03:19 by xhuang           ###   ########.fr       */
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

void	print_scene_info(t_scene *scene)
{
	printf("------ SCENE INFO ------\n");

	// Camera
	printf("\n[Camera]\n");
	print_vec3(scene->camera.origin, "Origin");
	print_vec3(scene->camera.direction, "Direction");
	printf("FOV: %.2f\n", scene->camera.fov);
	printf("Camera Count: %d\n", scene->camera.cam_num);

	// Ambient Light
	printf("\n[Ambient Light]\n");
	printf("Ratio: %.2f\n", scene->amb_light.ratio);
	print_color(scene->amb_light.color, "Color");
	printf("Ambient Count: %d\n", scene->amb_light.amb_num);

	// Light
	if (scene->light)
	{
		printf("\n[Light]\n");
		print_vec3(scene->light->position, "Position");
		printf("Ratio: %.2f\n", scene->light->ratio);
		print_color(scene->light->color, "Color");
	}
	else
		printf("\n[Light] None\n");

	// Objects
	t_object *obj = scene->obj;
	int i = 0;
	while (obj)
	{
		printf("\n[Object #%d]\n", ++i);
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
		obj = obj->next;
	}
	printf("\n------ END SCENE INFO ------\n");
}

