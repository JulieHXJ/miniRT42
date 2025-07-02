/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:38:15 by junjun            #+#    #+#             */
/*   Updated: 2025/07/02 13:13:36 by xhuang           ###   ########.fr       */
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





#endif