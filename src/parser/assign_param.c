/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:30:39 by xhuang            #+#    #+#             */
/*   Updated: 2025/05/26 15:11:55 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Assigns the rgb values to the object's color field.
 * 
 * @returns True for successful assignment, false otherwise.
 */
bool	assign_color(char *color, t_color *c, t_gc_object **gc_list)
{
	char	**tokens;

	tokens = split(color, ',');							// You dont have to gc_split() cause 'tokens' is a local variable, we free it before exiting the function.
	if (!tokens)
		return (print_error("Failed to split color", *gc_list),
			free(tokens), false);
	if (array_size(tokens) != 3)
		return (print_error("Color must have 3 components", *gc_list),
			free(tokens), false);
	c->r = ft_atoi(tokens[0]);
	c->g = ft_atoi(tokens[1]);
	c->b = ft_atoi(tokens[2]);
	if (valid_color(*c) == false)
		return (print_error("Color out of range [0, 255]", gc_list),
			free(tokens), false);
	return (free(tokens), true);
}

/**
 * @brief Assigns the coordinates to the object's vector field.
 * 
 * @returns True for successful assignment, false otherwise.
 */
bool	assign_vector(char *coord, t_vec3 *vec, t_gc_object **gc_list)
{
	char	**tokens;

	tokens = split(coord, ',');							// You dont have to gc_split() cause 'tokens' is a local variable, we free it before exiting the function.
	if (!tokens)
		return (print_error("Failed to parse vector", *gc_list), false);
	if (array_size(tokens) != 3)
		return (print_error("Vector must have 3 components", *gc_list),
			free(tokens), false);
	vec->x = ft_atod(tokens[0]);
	vec->y = ft_atod(tokens[1]);
	vec->z = ft_atod(tokens[2]);
	return (free(tokens), true);
}

/**
 * @note I removed the print_error() functions cause they would exit
 * before returning the result to the caller function.
 */
bool	assign_normal(char *normal, t_vec3 *v, t_gc_object **gc_list)
{
	if (!assign_vector(normal, v, gc_list))
		return (false);
	if (!valid_normal(*v, gc_list))
		return (false);
	return (true);
}

bool	assign_positive_num(char *num, double value, t_gc_object *gc_list)
{
	value = ft_atod(num);
	if (value <= 0)
		return (false);
	return (true);
}
