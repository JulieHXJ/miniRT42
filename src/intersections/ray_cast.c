/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:16:44 by junjun            #+#    #+#             */
/*   Updated: 2025/05/11 13:58:20 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



int cast_ray()
{
	t_object *obj;
	
	while (obj)
	{
		if (obj->type == SPHERE)
		{
			if (hit_sphere())
			{
				/* code */
			}
			
		}
		else if (obj->type == PLANE)
		{
			if (hit_plane())
			{
				/* code */
			}
			
		}
		else if (obj->type == CYLINDER)
		{
			if (hit_cylinder())
			{
				/* code */
			}
			
		}
		else if (condition)
		{
			/* code */
		}
		obj = obj->next;
		
		
	}
	return();
}
