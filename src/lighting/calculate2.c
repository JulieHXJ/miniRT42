/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:26:36 by dchrysov          #+#    #+#             */
/*   Updated: 2025/06/23 17:28:42 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	ambient_pixel(t_scene scene)
{
	t_color	result;

	result.r = scene.amb_light.color.r * scene.amb_light.ratio;
	result.g = scene.amb_light.color.g * scene.amb_light.ratio;
	result.b = scene.amb_light.color.b * scene.amb_light.ratio;
	return (result);
}
