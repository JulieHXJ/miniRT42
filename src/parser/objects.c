/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/05/07 11:58:16 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	create_cylinder(t_scene **scene, char **arr, t_gc_object **gc_list)
{
	t_object	*new_obj;
	t_object	*previous;

	new_obj = gc_alloc(sizeof(t_object), gc_list);
	new_obj->type = CYLINDER;
	center_point_assign(&new_obj, arr[1]);
	normal_vector_range_check(&new_obj, arr[2], gc_list);
	new_obj->u_type.cylinder.diam = ft_atod(arr[3]);
	new_obj->u_type.cylinder.height = ft_atod(arr[4]);
	rgb_range_check(&new_obj, arr[5], gc_list);
	new_obj->next = NULL;
	new_obj->previous = NULL;
	if (!(*scene)->obj)
		(*scene)->obj = new_obj;
	else
	{
		previous = (*scene)->obj;
		while (previous->next)
			previous = previous->next;
		previous->next = new_obj;
		new_obj->previous = previous;
	}
}

static void	create_sphere(t_scene **scene, char **arr, t_gc_object **gc_list)
{
	t_object	*new_obj;
	t_object	*previous;

	new_obj = gc_alloc(sizeof(t_object), gc_list);
	new_obj->type = SPHERE;
	center_point_assign(&new_obj, arr[1]);
	new_obj->u_type.sphere.diam = ft_atod(arr[2]);
	rgb_range_check(&new_obj, arr[3], gc_list);
	new_obj->next = NULL;
	new_obj->previous = NULL;
	if (!(*scene)->obj)
		(*scene)->obj = new_obj;
	else
	{
		previous = (*scene)->obj;
		while (previous->next)
			previous = previous->next;
		previous->next = new_obj;
		new_obj->previous = previous;
	}
}

static void	create_plane(t_scene **scene, char **arr, t_gc_object **gc_list)
{
	t_object	*new_obj;
	t_object	*previous;

	new_obj = gc_alloc(sizeof(t_object), gc_list);
	new_obj->type = PLANE;
	center_point_assign(&new_obj, arr[1]);
	normal_vector_range_check(&new_obj, arr[2], gc_list);
	rgb_range_check(&new_obj, arr[3], gc_list);
	new_obj->next = NULL;
	new_obj->previous = NULL;
	if (!(*scene)->obj)
		(*scene)->obj = new_obj;
	else
	{
		previous = (*scene)->obj;
		while (previous->next)
			previous = previous->next;
		previous->next = new_obj;
		new_obj->previous = previous;
	}
}

void	create_objects(char *line, t_scene **scene, t_gc_object **gc_list)
{
	char		**arr;
	char		*trimmed;

	trimmed = ft_strtrim(line, "\n");
	arr = ft_split(trimmed, ' ');
	if (arr[0][0] == 'p')
		create_plane(scene, arr, gc_list);
	else if (!ft_strcmp(arr[0], "sp"))
		create_sphere(scene, arr, gc_list);
	else
		create_cylinder(scene, arr, gc_list);
	free_array(&arr);
	free(trimmed);
}
