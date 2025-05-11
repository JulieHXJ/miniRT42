/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/05/11 14:05:04 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	create_cylinder(t_scene **scene, char **tokens)
{
	t_object	*new_obj;
	t_object	*last;

	new_obj = malloc(sizeof(t_object));
	if (!new_obj)
		return (print_error("Allocating memory for cylinder", NULL));
	new_obj->type = CYLINDER;
	center_point_assign(&new_obj, tokens[1]);
	normal_vector_range_check(&new_obj, CYLINDER, tokens[2]);
	new_obj->u_type.cylinder.diam = ft_atod(tokens[3]);
	new_obj->u_type.cylinder.height = ft_atod(tokens[4]);
	rgb_range_check(&new_obj, tokens[5]);
	new_obj->next = NULL;
	new_obj->previous = NULL;
	if (!(*scene)->obj)
		(*scene)->obj = new_obj;
	else
	{
		last = (*scene)->obj;
		while (last->next)
			last = last->next;
		last->next = new_obj;
		new_obj->previous = last;
	}
}

static void	create_sphere(t_scene **scene, char **tokens)
{
	t_object	*new_obj;
	t_object	*last;

	new_obj = malloc(sizeof(t_object));
	if (!new_obj)
		return (print_error("Allocating memory for sphere", NULL));
	new_obj->type = SPHERE;
	center_point_assign(&new_obj, tokens[1]);
	new_obj->u_type.sphere.diam = ft_atod(tokens[2]);
	rgb_range_check(&new_obj, tokens[3]);
	new_obj->next = NULL;
	new_obj->previous = NULL;
	if (!(*scene)->obj)
		(*scene)->obj = new_obj;
	else
	{
		last = (*scene)->obj;
		while (last->next)
			last = last->next;
		last->next = new_obj;
		new_obj->previous = last;
	}
}

static void	create_plane(t_scene **scene, char **tokens)
{
	t_object	*new_obj;
	t_object	*last;

	new_obj = malloc(sizeof(t_object));
	if (!new_obj)
		return (print_error("Allocating memory for plane", NULL));
	new_obj->type = PLANE;
	center_point_assign(&new_obj, tokens[1]);
	normal_vector_range_check(&new_obj, PLANE, tokens[2]);
	rgb_range_check(&new_obj, tokens[3]);
	new_obj->next = NULL;
	new_obj->previous = NULL;
	if (!(*scene)->obj)
		(*scene)->obj = new_obj;
	else
	{
		last = (*scene)->obj;
		while (last->next)
			last = last->next;
		last->next = new_obj;
		new_obj->previous = last;
	}
}


void	create_objects(char *line, t_scene **scene)
{
	char		**tokens;
	char		*trimmed;

	trimmed = ft_strtrim(line, "\n");
	tokens = ft_split(trimmed, ' ');
	if (!tokens || !tokens[0])
	{
		return (print_error("Invalid object line", line));
	}
	
	if (!ft_strcmp(tokens[0], "pl"))
		create_plane(scene, tokens);
	else if (!ft_strcmp(tokens[0], "sp"))
		create_sphere(scene, tokens);
	else if (!ft_strcmp(tokens[0], "cy"))
		create_cylinder(scene, tokens);
	else
		print_error("Unknown object identifier", tokens[0]);
	
	free_array(&tokens);
	free(trimmed);
}
