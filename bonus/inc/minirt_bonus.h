/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:46:12 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/03 14:05:21 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

// # include "../../inc/vector.h"
# include "../../inc/minirt.h"

typedef struct s_cone
{
	t_vec3	vertex_pos;
	t_vec3	orient;
	float	height;
	float	diameter;
}			t_cone;

typedef struct s_b_object
{
	t_object	base;
	t_cone		*cone;
}				t_b_object;


bool	create_cone(int id, t_scene **scn, char **arr, t_gc_object *gc);

#endif