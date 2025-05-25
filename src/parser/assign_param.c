/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:30:39 by xhuang            #+#    #+#             */
/*   Updated: 2025/05/25 19:12:36 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	assign_color(char *color, t_color *c, t_gc_object **gc_list)
{
	char	**tokens;

	tokens = gc_split(color, ',', gc_list);
	if (!tokens)
	{
		print_error("Failed to parse color", NULL);
		return (false);
	}
	// Check if there are enough tokens
	if (array_size(tokens) != 3)
		return (print_error("Color must have 3 components", NULL), false);
	c.r = ft_atoi(tokens[0]);
	c.g = ft_atoi(tokens[1]);
	c.b = ft_atoi(tokens[2]);
	if (valid_color(c) == false)
	{
		print_error("Color out of range [0, 255]", NULL);
		return (false);
	}
	return (true);
}

bool	assign_vector(char *coordinates, t_vec3 *v, t_gc_object **gc_list)
{
	char	**tokens;

	tokens = gc_split(coordinates, ',', gc_list);
	if (!tokens)
	{
		print_error("Failed to parse vector", NULL);
		return (false);
	}
	// Check if there are enough tokens
	if (array_size(tokens) != 3)
		return (print_error("Vector must have 3 components", NULL), false);
	v.x = ft_atod(tokens[0]);
	v.y = ft_atod(tokens[1]);
	v.z = ft_atod(tokens[2]);
	return (true);
}

bool	assign_normal(char *normal, t_vec3 *v, t_gc_object **gc_list)
{
	if (!assign_vector(normal, v, gc_list))
	{
		print_error("Failed to parse normal vector", NULL);
		return (false);
	}
	if (!valid_normal(v))
	{
		print_error("Normal vector out of range [-1.0, 1.0]", NULL);
		return (false);
	}
	return (true);
}

bool	assign_positive_num(char *num, double value, t_gc_object **gc_list)
{
	value = ft_atod(num);
	if (value <= 0)
	{
		print_error("Value out of range (0, +inf)", NULL);
		return (false);
	}
	return (true);
}
