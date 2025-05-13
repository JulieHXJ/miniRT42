/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/05/13 17:43:30 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	connect_nodes(t_scene **scene, t_object **new_obj)
{
	t_object	*previous;

	(*new_obj)->next = NULL;
	(*new_obj)->previous = NULL;
	if (!(*scene)->obj)
		(*scene)->obj = *new_obj;
	else
	{
		previous = (*scene)->obj;
		while (previous->next)
			previous = previous->next;
		previous->next = *new_obj;
		(*new_obj)->previous = previous;
	}
}

t_vec3	assign_center(char *coordinates)
{
	char	**tokens;
	t_vec3	center;

	tokens = ft_split(coordinates, ',');
	center.x = ft_atod(tokens[0]);
	center.y = ft_atod(tokens[1]);
	center.z = ft_atod(tokens[2]);
	free_array(&tokens);
	return (center);
}

t_color	assign_color(char *color)
{
	char	**tokens;
	t_color	color_vec;

	tokens = ft_split(color, ',');
	color_vec.r = ft_atoi(tokens[0]);
	color_vec.g = ft_atoi(tokens[1]);
	color_vec.b = ft_atoi(tokens[2]);
	if (valid_color(color_vec) == false)
	{
		print_error("Color out of range [0, 255]", NULL);
		free_array(&tokens);
		return (NULL);
	}
	free_array(&tokens);
	return (color_vec);
}
/**
 * @brief Assigns the center point vector, diameter,
	and check color range from the split line
 */
static bool	create_sphere(t_scene **scene, char **arr, t_gc_object **gc_list)
{
	t_object	*new_obj;

	new_obj = gc_alloc(sizeof(t_object), gc_list);
	if (!new_obj)
		return (print_error("Memory allocation failed for sphere", gc_list),
			false);
	new_obj->type = SPHERE;
	// assign center point
	new_obj->data.sphere.center = assign_center(arr[1]);
	if (ft_atod(arr[2]) <= 0)
		return (print_error("Sphere diameter must be positive", gc_list),
			false);
	new_obj->data.sphere.diam = ft_atod(arr[2]);
	// assign color
	new_obj->data.sphere.color = assign_color(arr[3]);
	new_obj->data.sphere.specular = 0.0;   // No specular by default
	new_obj->data.sphere.reflective = 0.0; // No reflection by default
	new_obj->content = NULL;
	connect_nodes(scene, &new_obj);
	return (true);
}

static bool	create_plane(t_scene **scene, char **arr, t_gc_object **gc_list)
{
	t_object	*new_obj;

	new_obj = gc_alloc(sizeof(t_object), gc_list);
	new_obj->type = PLANE;
	center_point_assign(&new_obj, arr[1]);
	normal_vector_range_check(&new_obj, arr[2], gc_list);
	rgb_range_check(&new_obj, arr[3], gc_list);
	connect_nodes(scene, &new_obj);
}

static bool	create_cylinder(t_scene **scene, char **arr, t_gc_object **gc_list)
{
	t_object	*new_obj;
	double		diam;
	double		height;

	new_obj = gc_alloc(sizeof(t_object), gc_list);
	new_obj->type = CYLINDER;
	center_point_assign(&new_obj, arr[1]);
	normal_vector_range_check(&new_obj, arr[2], gc_list);
	diam = ft_atod(arr[3]);
	if (diam < 0.0)
		print_error("Cylinder diameter out of range [0, inf)", gc_list);
	new_obj->u_type.cylinder.diam = diam;
	height = ft_atod(arr[4]);
	if (height < 0.0)
		print_error("Cylinder height out of range [0, inf)", gc_list);
	new_obj->u_type.cylinder.height = height;
	rgb_range_check(&new_obj, arr[5], gc_list);
	connect_nodes(scene, &new_obj);
}

bool	create_objects(char *line, t_scene **scene, t_gc_object **gc_list)
{
	char	**tokens;
	char	*trimmed;
	bool	flag;

	trimmed = ft_strtrim(line, "\n");
	tokens = ft_split(trimmed, ' ');
	free(trimmed);
	if (!tokens || !tokens[0])
		return (print_error("Memory allocation failed for objects", gc_list),
			false);
	flag = true;
	if (!ft_strcmp(tokens[0], "pl"))
		flag = create_plane(scene, tokens, gc_list);
	else if (!ft_strcmp(tokens[0], "sp"))
		flag = create_sphere(scene, tokens, gc_list);
	else if (!ft_strcmp(tokens[0], "cy"))
		flag = create_cylinder(scene, tokens, gc_list);
	else
		print_error("Unknown object identifier", tokens[0]);
	free_array(&tokens);
	return (flag);
}
