/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/06/25 18:54:47 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Connects the new object to the linked list of objects in the scene.
 * @note This function adds the new object to the head of the list.
 */
static void	connect_nodes(t_scene **scene, t_object **new_obj)
{
	if (!scene || !new_obj || !(*new_obj))
		return ;
	(*new_obj)->next = (*scene)->obj;
	(*new_obj)->previous = NULL;
	if ((*scene)->obj)
		(*scene)->obj->previous = *new_obj;
	(*scene)->obj = *new_obj;
}

/**
 * @brief Assigns the center position, diameter and color
 */
static bool	create_sphere(t_scene **scene, char **arr, t_gc_object **gc_list)
{
	t_object	*new_obj;

	// check number of tokens
	if (array_size(arr) < 4)
		return (print_error("Sphere requires 3 basic parameters", *gc_list), false);

	new_obj = gc_alloc(sizeof(t_object), gc_list);
	if (!new_obj)
		return (print_error("Memory allocation failed for sphere", *gc_list),
			false);
	new_obj->type = SPHERE;
	if (!assign_vector(arr[1], &new_obj->u_data.sphere.center, gc_list))
		return (print_error("Sphere center parse failed", *gc_list), false);
	if (!assign_positive_num(arr[2], &new_obj->u_data.sphere.diam))
		return (print_error("Negative number as sphere diameter", *gc_list),
			false);
	if (!assign_color(arr[3], &new_obj->color, gc_list))
		return (print_error("Sphere color parse failed", *gc_list), false);
	if (arr[4])
		assign_material(*arr, &new_obj->material);//pass the whole array to assign_material
	
	connect_nodes(scene, &new_obj);
	return (true);
}

static bool	create_plane(t_scene **scene, char **arr, t_gc_object **gc_list)
{
	t_object	*new_obj;

	// check number of tokens
	if (array_size(arr) < 4)
		return (print_error("Plane requires 3 basic parameters", *gc_list), false);
	new_obj = gc_alloc(sizeof(t_object), gc_list);
	if (!new_obj)
		return (print_error("Memory allocation failed for plane", *gc_list),
			false);
	new_obj->type = PLANE;
	if (!assign_vector(arr[1], &new_obj->u_data.plane.point, gc_list))
		return (print_error("Plane point parse failed", *gc_list), false);
	if (!assign_normal(arr[2], &new_obj->u_data.plane.normal, gc_list))
		return (print_error("Plane normal parse failed", *gc_list), false);
	if (!assign_color(arr[3], &new_obj->color, gc_list))
		return (print_error("Plane color parse failed", *gc_list), false);
	if (arr[4])
		assign_material(*arr, &new_obj->material);
	connect_nodes(scene, &new_obj);
	return (true);
}

static bool	create_cylinder(t_scene **scene, char **arr, t_gc_object **gc_list)
{
	t_object	*new_obj;
	double		diameter;

	if (array_size(arr) < 6)
		return (print_error("Cylinder requires 5 basic parameters", *gc_list), false);
	new_obj = gc_alloc(sizeof(t_object), gc_list);
	if (!new_obj)
		return (print_error("Memory allocation failed for cylinder", *gc_list),
			false);
	new_obj->type = CYLINDER;
	if (!assign_vector(arr[1], &new_obj->u_data.cylinder.center, gc_list))
		return (print_error("Cylinder center parse failed", *gc_list), false);
	if (!assign_normal(arr[2], &new_obj->u_data.cylinder.direction, gc_list))
		return (print_error("Cylinder direction parse failed", *gc_list),
			false);
	if (!assign_positive_num(arr[3], &diameter) || !assign_positive_num(arr[4],
			&new_obj->u_data.cylinder.height))
		return (print_error("Negative number detected", *gc_list), false);
	new_obj->u_data.cylinder.radius = diameter / 2.0;
	if (!assign_color(arr[5], &new_obj->color, gc_list))
		return (print_error("Cylinder color parse failed", *gc_list), false);
	get_cylinder_ends(&new_obj->u_data.cylinder);
	if (arr[4])
		assign_material(*arr, &new_obj->material);
	connect_nodes(scene, &new_obj);
	return (true);
}

bool	create_objects(char *line, t_scene **scene, t_gc_object **gc_list)
{
	char	**tokens;
	char	*trimmed;
	bool	flag;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		return (print_error("Strtrim failed for objects", *gc_list), false);
	tokens = gc_split(trimmed, ' ', gc_list);
	free(trimmed);
	if (!tokens || !tokens[0])
		return (print_error("Split failed for objects", *gc_list), false);
	flag = true;
	if (!ft_strcmp(tokens[0], "pl"))
		flag = create_plane(scene, tokens, gc_list);
	else if (!ft_strcmp(tokens[0], "sp"))
		flag = create_sphere(scene, tokens, gc_list);
	else if (!ft_strcmp(tokens[0], "cy"))
		flag = create_cylinder(scene, tokens, gc_list);
	else
	{
		// flag = create_bonus_object(scene, tokens, gc_list);
		print_error("Unknown object identifier", *gc_list);
		flag = false;
	}
	return (flag);
}
