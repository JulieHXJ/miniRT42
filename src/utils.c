/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:16:31 by dchrysov          #+#    #+#             */
/*   Updated: 2025/05/26 14:48:43 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

size_t	array_size(char **arr)
{
	size_t	size;

	size = 0;
	while (*arr)
	{
		size++;
		arr++;
	}
	return (size);
}

void	free_array(char ***arr)
{
	size_t	i;
	size_t	size;

	if (!arr || !*arr)
		return ;
	size = array_size(*arr);
	i = -1;
	while (++i < size)
		free((*arr)[i]);
	free(*arr);
	*arr = NULL;
}

void	print_error(char *msg, t_gc_object *gc_list)
{
	printf("%sError%s: %s\n", RED, RST, msg);
	if (gc_list)
		gc_free(gc_list);
	exit(1);
}

/**
 * @brief Convert string to double
 * @param str String to convert (format: [-+]?[0-9]*\.?[0-9]+)
 * @return Double value
 */
double	ft_atod(const char *s)
{
	double	res;
	double	frac;
	double	div;
	int		sign;

	sign = 1;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	res = 0;
	while (*s >= '0' && *s <= '9')
		res = res * 10 + (*s++ - '0');
	frac = 0;
	div = 10;
	if (*s == '.')
	{
		s++;
		while (*s >= '0' && *s <= '9')
		{
			frac += (*s++ - '0') / div;
			div *= 10;
		}
	}
	return (sign * (res + frac));
}

/**
 * @brief Print the scene for debugging
 */
void	print_scene(t_scene *scene)
{
	t_object	*obj;
	t_light		*light;

	// Print camera
	printf("Camera:\n");
	printf("  Position: (%.2f, %.2f, %.2f)\n", scene->camera.position.x,
		scene->camera.position.y, scene->camera.position.z);
	printf("  Direction: (%.2f, %.2f, %.2f)\n", scene->camera.direction.x,
		scene->camera.direction.y, scene->camera.direction.z);
	printf("  FOV: %.2f\n", scene->camera.fov);
	// Print ambient light
	printf("Ambient Light:\n");
	printf("  Ratio: %.2f\n", scene->amb_light->ratio);
	printf("  Color: (%d, %d, %d)\n", scene->amb_light->color.r,
		scene->amb_light->color.g, scene->amb_light->color.b);
	// Print lights
	printf("Lights (%d):\n", scene->light_num);
	light = scene->light;
	while (light)
	{
		printf("  Position: (%.2f, %.2f, %.2f)\n", light->position.x,
			light->position.y, light->position.z);
		printf("  Brightness: %.2f\n", light->brightness);
		printf("  Color: (%d, %d, %d)\n", light->color.r, light->color.g,
			light->color.b);
		light = light->next;
	}
	// Print objects
	printf("Objects:\n");
	obj = scene->obj;
	while (obj)
	{
		if (obj->type == SPHERE)
		{
			printf("\tSphere:\n");
			printf("\t\tCenter: (%.2f, %.2f, %.2f)\n",
				obj->u_data.sphere.center.x, obj->u_data.sphere.center.y,
				obj->u_data.sphere.center.z);
			printf("\t\tDiameter: %.2f\n", obj->u_data.sphere.diam);
			printf("\t\tColor: (%d, %d, %d)\n", obj->u_data.sphere.color.r,
				obj->u_data.sphere.color.g, obj->u_data.sphere.color.b);
		}
		else if (obj->type == PLANE)
		{
			printf("\tPlane:\n");
			printf("\t\tPoint: (%.2f, %.2f, %.2f)\n", obj->u_data.plane.point.x,
				obj->u_data.plane.point.y, obj->u_data.plane.point.z);
			printf("\t\tNormal: (%.2f, %.2f, %.2f)\n", obj->u_data.plane.normal.x,
				obj->u_data.plane.normal.y, obj->u_data.plane.normal.z);
			printf("\t\tColor: (%d, %d, %d)\n", obj->u_data.plane.color.r,
				obj->u_data.plane.color.g, obj->u_data.plane.color.b);
		}
		else if (obj->type == CYLINDER)
		{
			printf("\tCylinder:\n");
			printf("\t\tCenter: (%.2f, %.2f, %.2f)\n",
				obj->u_data.cylinder.center.x, obj->u_data.cylinder.center.y,
				obj->u_data.cylinder.center.z);
			printf("\t\tDirection: (%.2f, %.2f, %.2f)\n",
				obj->u_data.cylinder.direction.x, obj->u_data.cylinder.direction.y,
				obj->u_data.cylinder.direction.z);
			printf("\t\tDiameter: %.2f\n", obj->u_data.cylinder.diam);
			printf("\t\tHeight: %.2f\n", obj->u_data.cylinder.height);
			printf("\t\tColor: (%d, %d, %d)\n", obj->u_data.cylinder.color.r,
				obj->u_data.cylinder.color.g, obj->u_data.cylinder.color.b);
		}
		obj = obj->next;
	}
}
