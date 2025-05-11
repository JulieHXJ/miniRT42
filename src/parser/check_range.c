/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/05/06 17:37:14 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	rgb_range_check(t_object **obj, char *rgb)		// wrong prototype ??
{
	char	**tokens;
	int		int_rgb[3];

	tokens = ft_split(rgb, ',');
	int_rgb[0] = ft_atoi(tokens[0]);
	int_rgb[1] = ft_atoi(tokens[1]);
	int_rgb[2] = ft_atoi(tokens[2]);
	if (int_rgb[0] < 0 || int_rgb[0] > 255 || int_rgb[1] < 0 || int_rgb[1] > 255
		|| int_rgb[2] < 0 || int_rgb[2] > 255)
		return (print_error("RGB out of range [0, 255]", NULL));
	(*obj)->rgb[0] = int_rgb[0];
	(*obj)->rgb[1] = int_rgb[1];
	(*obj)->rgb[2] = int_rgb[2];
	free_array(&tokens);
}

void	normal_vector_range_check(t_object **obj, t_obj_type type, char *vec)
{
	char	**tokens;
	int		d_normal[3];

	tokens = ft_split(vec, ',');
	d_normal[0] = ft_atod(tokens[0]);
	d_normal[1] = ft_atod(tokens[1]);
	d_normal[2] = ft_atod(tokens[2]);
	if (d_normal[0] < -1.0 || d_normal[0] > 1.0 || d_normal[1] < -1.0
		|| d_normal[1] > 1.0 || d_normal[2] < -1.0 || d_normal[2] > 1.0)
		return (print_error("Normal vector out of range [-1.0, 1.0]", NULL));
	if (type == PLANE)
	{
		(*obj)->u_type.plane.normal[0] = d_normal[0];
		(*obj)->u_type.plane.normal[1] = d_normal[1];
		(*obj)->u_type.plane.normal[2] = d_normal[2];
	}
	else
	{
		(*obj)->u_type.cylinder.normal[0] = d_normal[0];
		(*obj)->u_type.cylinder.normal[1] = d_normal[1];
		(*obj)->u_type.cylinder.normal[2] = d_normal[2];
	}
	free_array(&tokens);
}

void	center_point_assign(t_object **obj, char *point)
{
	char	**tokens;

	tokens = ft_split(point, ',');
	(*obj)->center[0] = ft_atod(tokens[0]);
	(*obj)->center[1] = ft_atod(tokens[1]);
	(*obj)->center[2] = ft_atod(tokens[2]);
	free_array(&tokens);
}
