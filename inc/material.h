/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:38:15 by junjun            #+#    #+#             */
/*   Updated: 2025/07/07 12:34:49 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "vector.h"
# include <pthread.h>

typedef struct s_material
{
	float specular;         // Specular reflection coefficient
	float reflective;       // Reflective coefficient
	float refractive_index; // Refractive index for transparency
	float roughness;        // Surface roughness for diffuse reflection
	float transparency;     // Transparency coefficient
}	t_material;

void	assign_material(char **tokens, t_material *material);

#endif