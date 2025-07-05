/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/07/04 14:37:04 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Connects the new object to the linked list of objects in the scene.
 * @note This function adds the new object to the head of the list.
 */
void	add_object(t_scene **scene, t_object **new_obj)
{
	if (!scene || !new_obj || !(*new_obj))
		return ;
	(*new_obj)->next = (*scene)->obj;
	(*scene)->obj = *new_obj;
}

/**
 * @brief Assigns the center position, diameter and color
 */
static bool	create_sphere(int id, t_scene **scene, char **arr, t_gc_object **gc)
{
	t_object	*new_obj;

	if (array_size(arr) < 4)
		return (print_error("Sphere requires 3 basic parameters", *gc), false);
	new_obj = gc_alloc(sizeof(t_object), gc);
	if (!new_obj)
		return (print_error("Memory allocation failed for sphere", *gc), false);
	new_obj->type = SPHERE;
	new_obj->id = id;
	if (!assign_vector(arr[1], &new_obj->u_data.sphere.center, gc))
		return (print_error("Sphere center parse failed", *gc), false);
	if (!assign_positive_num(arr[2], &new_obj->u_data.sphere.diam))
		return (print_error("Negative number as sphere diameter", *gc), false);
	if (!assign_color(arr[3], &new_obj->color, gc))
		return (print_error("Sphere color parse failed", *gc), false);
	add_object(scene, &new_obj);
	return (true);
}

static bool	create_plane(int id, t_scene **scene, char **arr, t_gc_object **gc)
{
	t_object	*new_obj;

	if (array_size(arr) < 4)
		return (print_error("Plane requires 3 basic parameters", *gc), false);
	new_obj = gc_alloc(sizeof(t_object), gc);
	if (!new_obj)
		return (print_error("Memory allocation failed for plane", *gc), false);
	new_obj->id = id;
	new_obj->type = PLANE;
	if (!assign_vector(arr[1], &new_obj->u_data.plane.point, gc))
		return (print_error("Plane point parse failed", *gc), false);
	if (!assign_normal(arr[2], &new_obj->u_data.plane.normal, gc))
		return (print_error("Plane normal parse failed", *gc), false);
	if (!assign_color(arr[3], &new_obj->color, gc))
		return (print_error("Plane color parse failed", *gc), false);
	add_object(scene, &new_obj);
	return (true);
}

static bool	create_cylinder(int id, t_scene **scn, char **arr, t_gc_object **gc)
{
	t_object	*new_obj;
	float		diameter;

	if (array_size(arr) < 6)
		return (print_error("Cylinder requires 5 basic parameters", *gc),
			false);
	new_obj = gc_alloc(sizeof(t_object), gc);
	if (!new_obj)
		return (print_error("allocation failed for cylinder", *gc), false);
	new_obj->type = CYLINDER;
	new_obj->id = id;
	if (!assign_vector(arr[1], &new_obj->u_data.cylinder.center, gc))
		return (print_error("Cylinder center parse failed", *gc), false);
	if (!assign_normal(arr[2], &new_obj->u_data.cylinder.direction, gc))
		return (print_error("Cylinder direction parse failed", *gc), false);
	if (!assign_positive_num(arr[3], &diameter) || !assign_positive_num(arr[4],
			&new_obj->u_data.cylinder.height))
		return (print_error("Negative number detected", *gc), false);
	new_obj->u_data.cylinder.radius = diameter / 2.0;
	if (!assign_color(arr[5], &new_obj->color, gc))
		return (print_error("Cylinder color parse failed", *gc), false);
	get_cylinder_ends(&new_obj->u_data.cylinder);
	return (add_object(scn, &new_obj), true);
}

bool	create_objects(char *line, t_scene **scene, t_gc_object **gc_list)
{
	static int	i = 0;
	char		**tokens;
	char		*trimmed;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		return (print_error("Strtrim failed for objects", *gc_list), false);
	tokens = gc_split(trimmed, ' ', gc_list);
	free(trimmed);
	if (!tokens || !tokens[0])
		return (print_error("Split failed for objects", *gc_list), false);
	if (!ft_strcmp(tokens[0], "pl"))
		return (create_plane(i++, scene, tokens, gc_list));
	else if (!ft_strcmp(tokens[0], "sp"))
		return (create_sphere(i++, scene, tokens, gc_list));
	else if (!ft_strcmp(tokens[0], "cy"))
		return (create_cylinder(i++, scene, tokens, gc_list));
	else if (!ft_strcmp(tokens[0], "co"))
		return (create_cone(i++, scene, tokens, gc_list));
	print_error("Unknown object identifier", *gc_list);
	return (false);
}
