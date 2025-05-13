/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:16:31 by dchrysov          #+#    #+#             */
/*   Updated: 2025/05/13 15:32:49 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

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
 * 
 * @param scene Scene to print
 */
void print_scene(t_scene *scene)
{
    t_object *obj;
    t_light *light;
    
    // Print camera
    printf("Camera:\n");
    printf("  Position: (%.2f, %.2f, %.2f)\n", 
           scene->camera.position.x, 
           scene->camera.position.y, 
           scene->camera.position.z);
    printf("  Direction: (%.2f, %.2f, %.2f)\n", 
           scene->camera.direction.x, 
           scene->camera.direction.y, 
           scene->camera.direction.z);
    printf("  FOV: %.2f\n", scene->camera.fov);
    
    // Print ambient light
    printf("Ambient Light:\n");
    printf("  Intensity: %.2f\n", scene->amb_light.intensity);
    printf("  Color: (%d, %d, %d)\n", 
           scene->amb_light.color.r, 
           scene->amb_light.color.g, 
           scene->amb_light.color.b);
    
    // Print lights
    printf("Lights (%d):\n", scene->light_num);
    light = scene->light;
    while (light)
    {
        printf("  Position: (%.2f, %.2f, %.2f)\n", 
               light->position.x, 
               light->position.y, 
               light->position.z);
        printf("  Brightness: %.2f\n", light->brightness);
        printf("  Color: (%d, %d, %d)\n", 
               light->color.r, 
               light->color.g, 
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
            printf("  Sphere:\n");
            printf("    Center: (%.2f, %.2f, %.2f)\n", 
                   obj->data.sphere.center.x, 
                   obj->data.sphere.center.y, 
                   obj->data.sphere.center.z);
            printf("    Diameter: %.2f\n", obj->data.sphere.diam);
            printf("    Color: (%d, %d, %d)\n", 
                   obj->data.sphere.color.r, 
                   obj->data.sphere.color.g, 
                   obj->data.sphere.color.b);
        }
        else if (obj->type == PLANE)
        {
            printf("  Plane:\n");
            printf("    Point: (%.2f, %.2f, %.2f)\n", 
                   obj->data.plane.point.x, 
                   obj->data.plane.point.y, 
                   obj->data.plane.point.z);
            printf("    Normal: (%.2f, %.2f, %.2f)\n", 
                   obj->data.plane.normal.x, 
                   obj->data.plane.normal.y, 
                   obj->data.plane.normal.z);
            printf("    Color: (%d, %d, %d)\n", 
                   obj->data.plane.color.r, 
                   obj->data.plane.color.g, 
                   obj->data.plane.color.b);
        }
        else if (obj->type == CYLINDER)
        {
            printf("  Cylinder:\n");
            printf("    Center: (%.2f, %.2f, %.2f)\n", 
                   obj->data.cylinder.center.x, 
                   obj->data.cylinder.center.y, 
                   obj->data.cylinder.center.z);
            printf("    Direction: (%.2f, %.2f, %.2f)\n", 
                   obj->data.cylinder.direction.x, 
                   obj->data.cylinder.direction.y, 
                   obj->data.cylinder.direction.z);
            printf("    Diameter: %.2f\n", obj->data.cylinder.diam);
            printf("    Height: %.2f\n", obj->data.cylinder.height);
            printf("    Color: (%d, %d, %d)\n", 
                   obj->data.cylinder.color.r, 
                   obj->data.cylinder.color.g, 
                   obj->data.cylinder.color.b);
        }
        obj = obj->next;
    }
}