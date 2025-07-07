/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:46:12 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/07 15:49:03 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <stdbool.h>

# include "../../inc/env.h"
# include "../../inc/gc.h"
# include "../../inc/objects.h"
# include "../../inc/intersect.h"
# include "texture.h"

void	add_light(t_scene *scene, t_light *light);
bool	create_cone(int id, t_scene **scn, char **arr, t_gc_object **gc);
bool	hit_cone(t_ray ray, t_cone cone, t_hit *hit);
t_color	color_disruption(t_hit hit);
t_color	texture_object(t_hit *hit);
void	assign_textures(t_scene scene);

#endif