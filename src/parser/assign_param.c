/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:30:39 by xhuang            #+#    #+#             */
/*   Updated: 2025/07/04 14:37:46 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	assign_color(char *color, t_color *c, t_gc_object **gc_list)
{
	char	**tokens;

	tokens = gc_split(color, ',', gc_list);
	if (!tokens)
		return (print_error("Failed to parse color", NULL), false);
	if (array_size(tokens) != 3)
		return (print_error("Color must have 3 components", NULL), false);
	*c = (t_color){ft_atoi(tokens[0]), ft_atoi(tokens[1]), ft_atoi(tokens[2])};
	if (valid_color(*c) == false)
		return (print_error("Color out of range [0, 255]", NULL), false);
	return (true);
}

bool	assign_vector(char *coordinates, t_vec3 *v, t_gc_object **gc_list)
{
	char	**tokens;

	tokens = gc_split(coordinates, ',', gc_list);
	if (!tokens)
		return (print_error("Failed to parse vector", NULL), false);
	if (array_size(tokens) != 3)
		return (print_error("Vector must have 3 components", NULL), false);
	*v = new_vector(ft_atod(tokens[0]), ft_atod(tokens[1]), ft_atod(tokens[2]));
	return (true);
}

bool	assign_normal(char *normal, t_vec3 *v, t_gc_object **gc_list)
{
	if (!assign_vector(normal, v, gc_list))
		return (print_error("Failed to parse normal vector", NULL), false);
	if (!valid_normal(*v))
		return (print_error("Normal vector out of range [-1.0, 1.0]", NULL),
			false);
	*v = vec_normal(*v);
	return (true);
}

bool	assign_positive_num(char *num, float *value)
{
	*value = ft_atod(num);
	if (*value <= 0)
		return (print_error("Value out of range (0, +inf)", NULL), false);
	return (true);
}
