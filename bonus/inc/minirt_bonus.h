/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:46:12 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/04 15:11:50 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <stdbool.h>

# include "../../inc/env.h"
# include "../../inc/gc.h"
# include "../../inc/objects.h"
# include "../../inc/intersect.h"

bool	create_cone(int id, t_scene **scn, char **arr, t_gc_object **gc);
bool	hit_cone(t_ray ray, t_cone cone, t_hit *hit);

#endif